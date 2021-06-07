/* 
 * Copyright (C) 2021 Infineon Technologies AG.
 *
 * Licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License
 * Agreement V1.0 (the "License"); you may not use this file except in
 * compliance with the License.
 *
 * For receiving a copy of the License, please refer to:
 *
 * https://github.com/Infineon/pred-main-xmc4700-kit/LICENSE.txt
 *
 * Licensee acknowledges that the Licensed Items are provided by Licensor free
 * of charge. Accordingly, without prejudice to Section 9 of the License, the
 * Licensed Items provided by Licensor under this Agreement are provided "AS IS"
 * without any warranty or liability of any kind and Licensor hereby expressly
 * disclaims any warranties or representations, whether express, implied,
 * statutory or otherwise, including but not limited to warranties of
 * workmanship, merchantability, fitness for a particular purpose, defects in
 * the Licensed Items, or non-infringement of third parties' intellectual
 * property rights.
 *
 */
 
package com.infineon;

import org.json.JSONObject;
import software.amazon.awscdk.core.*;
import software.amazon.awscdk.core.Stack;
import software.amazon.awscdk.customresources.Provider;
import software.amazon.awscdk.services.cognito.*;
import software.amazon.awscdk.services.elasticsearch.CfnDomain;
import software.amazon.awscdk.services.elasticsearch.CfnDomainProps;
import software.amazon.awscdk.services.iam.*;
import software.amazon.awscdk.services.iot.CfnTopicRule;
import software.amazon.awscdk.services.kinesis.Stream;
import software.amazon.awscdk.services.kinesis.StreamEncryption;
import software.amazon.awscdk.services.kinesisanalytics.CfnApplication;
import software.amazon.awscdk.services.kinesisanalytics.CfnApplicationOutput;
import software.amazon.awscdk.services.kinesisfirehose.CfnDeliveryStream;
import software.amazon.awscdk.services.lambda.*;
import software.amazon.awscdk.services.lambda.Runtime;
import software.amazon.awscdk.services.s3.Bucket;
import software.amazon.awscdk.services.s3.BucketEncryption;
import software.amazon.awscdk.services.logs.CfnLogGroup;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class InfineonKitStackRealtime extends Stack {

    private static String DOMAIN_NAME = "";
    private static final Number LOGS_RETENTION_DAYS = 90;

    public InfineonKitStackRealtime(App app, String id) {
        this(app, id, null);

    }

    public InfineonKitStackRealtime(final Construct scope, final String id, final StackProps props) {
        super(scope, id, props);
        DOMAIN_NAME = id.toLowerCase();

        //create s3 bucket for logs from kinesis data stream
        Bucket logs = createS3Bucket();

        //grant access to s3 bucket for data stream and lambda function
        IRole roleForDataStream = getRoleForLogsToS3BucketDeliveryStream(logs);
        logs.grantReadWrite(roleForDataStream);
        //create Kinesis Data Stream for device metrics
        Stream dataStream = createKinesisDataStream();
        CfnDeliveryStream firehoseStream = createFirehoseLogsToS3Stream(logs.getBucketArn(), roleForDataStream.getRoleArn());

        //create identity pool and user pool for aws cognito service (auth for kibana)
        Map.Entry<CfnUserPool, CfnUserPoolClient> userPoolAndClient = createUserPoolAndClient();
        CfnIdentityPool identityPool = createIdentityPool(userPoolAndClient);

        Role cognitoESRole = createCognitoESRole();
        CfnDomain domain = createElasticSearchDomain(cognitoESRole.getRoleArn(), userPoolAndClient.getKey(), identityPool);
        createIoTRules(dataStream, firehoseStream, domain.getAttrDomainEndpoint());
        Role auth = createKibanaRole(identityPool);
        domain.setAccessPolicies(createElasticSearchAccessPolicies(auth, cognitoESRole, domain.getDomainName()));
        //create metrics from kinesis data stream to ElasticSearch delivery stream
        createKinesisAnalytics(dataStream, domain.getAttrDomainEndpoint());
        createOutput(domain, userPoolAndClient);
        createEsIndexMapping(domain);
        createCustomResource(domain);
    }

    /**
     * receives a json message from the Kinesis Data Analytics, builds a full json message (some sensors may be absent)
     * fills json with data metrics and transforms json to a flat format (one-level)
     *
     * @return aws data transformation function
     */
    private Function createAnalyticsToCommonJsonLambda() {
        Role lambdaRole = Role.Builder.create(this, "AnalyticsToCommonJsonLambdaRole")
                .assumedBy(new ServicePrincipal("lambda.amazonaws.com"))
                .managedPolicies(Collections.singletonList(
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaBasicExecutionRole")))
                .build();

        String lambdaPath = "lambda/infn-analytics-to-json.jar";
        Function func = Function.Builder.create(this, "AnalyticsToCommonJsonLambda")
                .runtime(Runtime.JAVA_8)
                .role(lambdaRole)
                .timeout(Duration.minutes(1))
                .code(Code.fromAsset(lambdaPath))
                .handler("com.JsonLambdaConverter")
                .build();

        CfnLogGroup log = CfnLogGroup.Builder.create(this, "AnalyticsToCommonJsonLambdaLogGroup").
                logGroupName("/aws/lambda/" + func.getFunctionName())
                .retentionInDays(LOGS_RETENTION_DAYS).
                build();

        log.getNode().addDependency(func);
        return func;
    }

    /**
     * @param endpoint ElasticSearch domain endpoint
     * @return lambda function: delivers anomaly results data to ElasticSearch
     */
    private Function createLambdaAnomalyToEs(String endpoint) {
        Map<String, String> envVariables = new HashMap<>();
        envVariables.put("AWS_DOMAIN", "https://" + endpoint);

        Function func = Function.Builder.create(this, "AnomalyToEsNJ")
                .runtime(Runtime.NODEJS_12_X)
                .role(getRoleForLambdaAnalytics())
                .environment(envVariables)
                .timeout(Duration.minutes(1))
                .code(Code.fromAsset("lambda/analytics-to-es.zip"))
                .handler("index.handler")
                .build();

        CfnLogGroup log = CfnLogGroup.Builder.create(this, "AnalyticsToESLambdaLogGroup").
                logGroupName("/aws/lambda/" + func.getFunctionName())
                .retentionInDays(LOGS_RETENTION_DAYS).
                build();
        log.getNode().addDependency(log);
        return func;
    }

    /**
     * creates a Kinesis Data Analytics application (data stream as a source, Kinesis Data stream as an output)
     *
     * @param dataStream Input source for Kinesis Analytics (Kinesis Data stream with initial device metrics)
     * @param endpoint   ElasticSearch domain endpoint
     */
    private void createKinesisAnalytics(Stream dataStream, String endpoint) {
        //create output delivery stream
        IRole kinesisAnalyticsRole = createKinesisAnalyticsRole();
        Function function = createAnalyticsToCommonJsonLambda();

        //configure input data source for Kinesis analytics application (Kinesis Data stream)
        CfnApplication.InputProperty input = CfnApplication.InputProperty.builder()
                .inputProcessingConfiguration(CfnApplication.InputProcessingConfigurationProperty.builder()
                        .inputLambdaProcessor(CfnApplication.InputLambdaProcessorProperty.builder()
                                .resourceArn(function.getFunctionArn())
                                .roleArn(kinesisAnalyticsRole.getRoleArn())
                                .build())
                        .build())
                .kinesisStreamsInput(CfnApplication
                        .KinesisStreamsInputProperty.builder()
                        .roleArn(kinesisAnalyticsRole.getRoleArn())
                        .resourceArn(dataStream.getStreamArn())
                        .build())
                .inputSchema(AnomalyDetectionAppUtils.getInputSchema())
                .namePrefix("input_stream")
                .build();
        CfnApplication app = CfnApplication.Builder.create(this, DOMAIN_NAME + "analytics-app")
                .applicationCode(readFile())
                .inputs(Collections.singletonList(input))
                .applicationName(DOMAIN_NAME + "-analytics")
                .build();
        Function functionOutput = createLambdaAnomalyToEs(endpoint);

        CfnOutput.Builder.create(this, "AnalyticsApp")
                .description("Analytics app name")
                .value(app.getApplicationName()).build();

        //configure Kinesis Data Analytics Output
        createAnalyticsOutput(kinesisAnalyticsRole, app, functionOutput);
    }

    private IRole getRoleForLambdaAnalytics() {
        ManagedPolicy policy = ManagedPolicy.Builder
                .create(this, "analytics-es-role" + "-policy")
                .statements(getESPolicyStatements())
                .build();
        return Role.Builder.create(this, "analytics-es-role")
                .roleName(DOMAIN_NAME + "analytics-es-role")
                .managedPolicies(Arrays.asList(policy,
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaBasicExecutionRole"),
                        ManagedPolicy.fromAwsManagedPolicyName("AmazonKinesisAnalyticsFullAccess")))
                .assumedBy(new ServicePrincipal("lambda.amazonaws.com"))
                .build();
    }

    /**
     * @return IAM role for lambda function; grants access to Kinesis Data Stream, ElasticSearch, CloudWatch
     */
    private IRole getRoleForDeliveryLambda() {
        ManagedPolicy policy = ManagedPolicy.Builder
                .create(this, "metrics-to-es-role" + "-policy")
                .statements(getESPolicyStatements())
                .build();
        return Role.Builder.create(this, "analytics-es-lambda-role")
                .roleName("metrics-to-es-role")
                .managedPolicies(Arrays.asList(policy,
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaBasicExecutionRole")))
                .assumedBy(new ServicePrincipal("lambda.amazonaws.com"))
                .build();
    }

    private List<PolicyStatement> getESPolicyStatements() {
        List<String> actions = Arrays.asList("es:ESHttpGet", "es:ESHttpPost");
        return Arrays.asList(
                PolicyStatement.Builder.create()
                        .effect(Effect.ALLOW)
                        .actions(actions)
                        .resources(Collections.singletonList("*"))
                        .build());

    }

    /**
     * create CloudFormation output resource: link to userPool (so as to create users for Kibana) and link to Kibana
     *
     * @param domain            ElasticSearch domain endpoint
     * @param userPoolAndClient userPool and client
     */
    private void createOutput(CfnDomain domain, Map.Entry<CfnUserPool, CfnUserPoolClient> userPoolAndClient) {
        CfnOutput.Builder.create(this, "KibanaUrl")
                .description("Access Kibana via this URL.")
                .value("https://" + domain.getAttrDomainEndpoint() + "/_plugin/kibana/")
                .build();
    }

    /**
     * creates custom resource as lambda function, that imports a set of visualizations, dashboards and index patterns to Kibana
     *
     * @param domain ElasticSearch domain endpoint
     */
    private void createCustomResource(CfnDomain domain) {
        IRole savedObjectsImportRole = getKibanaSavedObjectsImportRole(domain);
        Map<String, Object> props = new HashMap<>();
        props.put("requests", new JSONObject()
                .put("method", "POST")
                .put("url", domain.getAttrDomainEndpoint())
                .put("tp", System.currentTimeMillis())
                .put("region", this.getRegion())
                .toMap());
        Function onEventFunction = Function.Builder.create(this, DOMAIN_NAME + "on-event")
                .functionName("infn-on-event-function")
                .code(Code.fromAsset("lambda/kibana-infn.zip"))
                .handler("lambda.lambda_handler")
                .tracing(Tracing.ACTIVE)
                .timeout(Duration.minutes(2))
                .runtime(Runtime.PYTHON_3_7)
                .role(savedObjectsImportRole)
                .build();
        Function isCompleteFunction = Function.Builder.create(this, DOMAIN_NAME + "is-complete")
                .functionName("infn-is-complete-function")
                .code(Code.fromAsset("lambda/kibana-infn.zip"))
                .handler("response.is_complete")
                .tracing(Tracing.ACTIVE)
                .runtime(Runtime.PYTHON_3_7)
                .role(savedObjectsImportRole)
                .build();
        Provider provider = Provider.Builder.create(this, DOMAIN_NAME + "provider")
                .onEventHandler(onEventFunction)
                .isCompleteHandler(isCompleteFunction)
                .build();
        CustomResource.Builder.create(this, DOMAIN_NAME + "custom")
                .properties(props)
                .pascalCaseProperties(false)
                .serviceToken(provider.getServiceToken())
                .build();
    }

    /**
     * @param domain ElasticSearch domain endpoint
     * @return IAM role for lambda function; grants access to ElasticSearch
     */
    private IRole getKibanaSavedObjectsImportRole(CfnDomain domain) {
        List<String> actions = Arrays.asList("es:ESHttpHead", "es:ESHttpPut", "es:ESHttpGet", "es:ESHttpPost");
        List<PolicyStatement> statements = Collections.singletonList(
                PolicyStatement.Builder.create()
                        .effect(Effect.ALLOW)
                        .actions(actions)
                        .resources(Arrays.asList(domain.getAttrArn(), domain.getAttrArn() + "/*"))
                        .build());
        return Role.Builder.create(this, DOMAIN_NAME + "http-kibana-role")
                .managedPolicies(Arrays.asList(
                        ManagedPolicy.Builder.create(this, DOMAIN_NAME + "cstm-http-policy")
                                .statements(statements)
                                .build(),
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaRole"),
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaBasicExecutionRole")))
                .assumedBy(new ServicePrincipal("lambda.amazonaws.com"))
                .build();
    }

    /**
     * creates custom resource as lambda function that creates ElasticSearch indices with field mappings
     *
     * @param domain ElasticSearch domain endpoint
     */
    private void createEsIndexMapping(CfnDomain domain) {
        IRole role = getRoleForCreateESIndices(domain);
        Map<String, Object> proprs = new HashMap<>();
        proprs.put("requests", new JSONObject()
                .put("method", "POST")
                .put("url", domain.getAttrDomainEndpoint())
                .put("tp", System.currentTimeMillis())
                .put("region", this.getRegion())
                .toMap());
        Function onEventFunction = Function.Builder.create(this, DOMAIN_NAME + "on-create-index")
                .functionName("on-create-es-index")
                .code(Code.fromAsset("lambda/create-index.zip"))
                .handler("create_index_request.lambda_handler")
                .tracing(Tracing.ACTIVE)
                .timeout(Duration.minutes(3))
                .runtime(Runtime.PYTHON_3_7)
                .role(role)
                .build();
        Function isCompleteFunction = Function.Builder.create(this, DOMAIN_NAME + "is-index-create-complete")
                .functionName("index-create-complete-function")
                .code(Code.fromAsset("lambda/create-index.zip"))
                .handler("create_index_response.is_complete")
                .tracing(Tracing.ACTIVE)
                .runtime(Runtime.PYTHON_3_7)
                .role(role)
                .build();
        Provider provider = Provider.Builder.create(this, DOMAIN_NAME + "es-provider-resource")
                .onEventHandler(onEventFunction)
                .isCompleteHandler(isCompleteFunction)
                .build();
        CustomResource.Builder.create(this, DOMAIN_NAME + "es-create-index-custom-resource")
                .properties(proprs)
                .pascalCaseProperties(false)
                .serviceToken(provider.getServiceToken())
                .build();
    }

    /**
     * @param domain ElasticSearch domain endpoint
     * @return IAM role for custom resource; grants access to ElasticSearch
     */
    private IRole getRoleForCreateESIndices(CfnDomain domain) {
        List<String> actions = Arrays.asList("es:ESHttpHead", "es:ESHttpPut", "es:ESHttpGet", "es:ESHttpPost");
        List<PolicyStatement> statements = Collections.singletonList(
                PolicyStatement.Builder.create()
                        .effect(Effect.ALLOW)
                        .actions(actions)
                        .resources(Arrays.asList(domain.getAttrArn(), domain.getAttrArn() + "/*"))
                        .build());
        return Role.Builder.create(this, DOMAIN_NAME + "http-es-role")
                .managedPolicies(Arrays.asList(
                        ManagedPolicy.Builder.create(this, DOMAIN_NAME + "es-http-policy")
                                .statements(statements)
                                .build(),
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaRole"),
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaBasicExecutionRole")))
                .assumedBy(new ServicePrincipal("lambda.amazonaws.com"))
                .build();
    }

    /**
     * configure Kinesis Analytics output destination: Kinesis Data stream
     *
     * @param role IAM role for Kinesis Analytics
     * @param app  Kinesis Analytics application
     */
    private void createAnalyticsOutput(IRole role, CfnApplication app, Function functionOutput) {
        CfnApplicationOutput.Builder.create(this, "anomaly-detection-output")
                .output(CfnApplicationOutput.OutputProperty.builder()
                        .destinationSchema(CfnApplicationOutput.DestinationSchemaProperty.builder()
                                .recordFormatType("JSON")
                                .build())
                        .lambdaOutput(CfnApplicationOutput.LambdaOutputProperty.builder()
                                .resourceArn(functionOutput.getFunctionArn())
                                .roleArn(role.getRoleArn())
                                .build())
                        .name("SCORE_STREAM")
                        .build())
                .applicationName(app.getApplicationName())
                .build().addDependsOn(app);
    }

    /**
     * read data from file (sql code for data analytics application)
     */
    private String readFile() {
        byte[] encoded = new byte[0];
        try {
            Path path = Paths.get("application/app-code");
            encoded = Files.readAllBytes(path);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new String(encoded, Charset.defaultCharset());
    }

    private IRole createKinesisAnalyticsRole() {
        return Role.Builder.create(this, "kinesis-analytics-role")
                .assumedBy(new ServicePrincipal("kinesisanalytics.amazonaws.com"))
                .managedPolicies(Arrays.asList(
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaRole"),
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaKinesisExecutionRole"),
                        ManagedPolicy.fromAwsManagedPolicyName("AmazonKinesisFullAccess")))
                .build();
    }

    private Bucket createS3Bucket() {
        Bucket bucket = Bucket.Builder.create(this, "infn-logs")
                .removalPolicy(RemovalPolicy.RETAIN)
                .encryption(BucketEncryption.S3_MANAGED)
                .build();

        CfnOutput.Builder.create(this, "deviceLogs")
                .description("Bucket with device telematics data")
                .value(bucket.getBucketName())
                .build();

        return bucket;
    }

    private CfnDeliveryStream.KinesisStreamSourceConfigurationProperty getKinesisStreamSource(String streamArn, String roleArn) {
        return CfnDeliveryStream
                .KinesisStreamSourceConfigurationProperty.builder()
                .kinesisStreamArn(streamArn)
                .roleArn(roleArn)
                .build();
    }

    private Stream createKinesisDataStream() {
        return Stream.Builder.create(this, DOMAIN_NAME + "Data-Stream")
                .streamName("metrics-data")
                .shardCount(1)
                .encryption(StreamEncryption.UNENCRYPTED)
                .build();
    }

    /**
     * @param roleForDeliveryLambda IAM role for lambda function (with access to ElasticSearch)
     * @param endpoint              ElasticSearch domain endpoint
     * @return lambda function that delivers metrics from IoT Rule action to ElasticSearch
     */
    private Function createLambdaMetricsToEs(IRole roleForDeliveryLambda, String endpoint) {
        String lambdaPath = "lambda/infn-metrics-to-es.jar";

        Map<String, String> envVariables = new HashMap<>();
        envVariables.put("AWS_DOMAIN", "https://" + endpoint);

        Function func = Function.Builder.create(this, "MetricsToEsFunction")
                .runtime(Runtime.JAVA_8)
                .environment(envVariables)
                .role(roleForDeliveryLambda)
                .timeout(Duration.minutes(2))
                .maxEventAge(Duration.minutes(1))
                .memorySize(200)
                .code(Code.fromAsset(lambdaPath))
                .handler("com.JsonLambdaConverter")
                .build();

        CfnLogGroup log = CfnLogGroup.Builder.create(this, "MetricsToEsLambdaLogGroup").
                logGroupName("/aws/lambda/" + func.getFunctionName())
                .retentionInDays(LOGS_RETENTION_DAYS).
                build();
        log.getNode().addDependency(func);
        return func;
    }

    /**
     * creates IoT rule (receives messages from MQTT topic "infn/dev/#", where + is a partition key - device name)
     * and sends messages to a Kinesis Data Stream
     *
     * @param dataStream destination for messages ("sensors-data" Kinesis Data Stream)
     */
    private void createIoTRules(Stream dataStream, CfnDeliveryStream firehoseStream, String domainEndpoint) {
        IRole iotRole = Role.Builder.create(this, "iot-rule")
                .assumedBy(new ServicePrincipal("iot.amazonaws.com"))
                .managedPolicies(Collections.singletonList(
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSIoTRuleActions")))
                .build();
        CfnTopicRule.ActionProperty action = CfnTopicRule.ActionProperty.builder()
                .kinesis(CfnTopicRule.KinesisActionProperty.builder()
                        .streamName(dataStream.getStreamName())
                        .partitionKey("${topic(3)}")
                        .roleArn(iotRole.getRoleArn())
                        .build())
                .build();

        CfnTopicRule.ActionProperty firehoseAction = CfnTopicRule.ActionProperty.builder()
                .firehose(CfnTopicRule.FirehoseActionProperty.builder()
                        .deliveryStreamName(firehoseStream.getDeliveryStreamName())
                        .separator("\n")
                        .roleArn(iotRole.getRoleArn())
                        .build())
                .build();

        Function lambda = createLambdaMetricsToEs(getRoleForDeliveryLambda(), domainEndpoint);
        CfnTopicRule.ActionProperty actionToFunction = CfnTopicRule.ActionProperty.builder()
                .lambda(CfnTopicRule.LambdaActionProperty.builder()
                        .functionArn(lambda.getFunctionArn())
                        .build())
                .build();

        List<CfnTopicRule.ActionProperty> actions = new ArrayList<>();
        actions.add(actionToFunction);
        actions.add(action);
        actions.add(firehoseAction);

        CfnTopicRule.TopicRulePayloadProperty rulePayloadToFunction = CfnTopicRule.TopicRulePayloadProperty.builder()
                .sql("SELECT * as pl, topic(3) as n FROM 'infn/dev/#'")
                .actions(actions)
                .awsIotSqlVersion("2016-03-23")
                .ruleDisabled(false)
                .build();
        CfnTopicRule rule = CfnTopicRule.Builder.create(this, "iot-lambda-topic-rule")
                .ruleName("redirect_metrics")
                .topicRulePayload(rulePayloadToFunction)
                .build();

        lambda.addPermission("id-permission-lambda", Permission.builder()
                .action("lambda:InvokeFunction")
                .scope(this)
                .principal(new ServicePrincipal("iot.amazonaws.com"))
                .sourceArn(rule.getAttrArn())
                .build());
    }

    private Role createKibanaRole(CfnIdentityPool identityPool) {
        List<String> authActions = Arrays.asList("cognito-sync:*", "cognito-identity:*", "es:ESHttpGet", "es:ESHttpPost");
        List<PolicyStatement> authStatements = Collections.singletonList(
                PolicyStatement.Builder.create()
                        .effect(Effect.ALLOW)
                        .actions(authActions)
                        .resources(Collections.singletonList("*"))
                        .build());
        Role authenticatedRole = Role.Builder.create(this, "auth-role")
                .assumedBy(getPrincipalForAuthRoleKibana(identityPool, true))
                .managedPolicies(Collections.singletonList(
                        ManagedPolicy.Builder.create(this, "CognitoDefaultAuthenticatedRole")
                                .statements(authStatements)
                                .build()))
                .build();

        List<String> unauthActions = Arrays.asList("cognito-sync:*", "cognito-identity:*");
        List<PolicyStatement> unauthStatements = Collections.singletonList(
                PolicyStatement.Builder.create()
                        .effect(Effect.ALLOW)
                        .actions(unauthActions)
                        .resources(Collections.singletonList("*"))
                        .build());
        Role unauthenticatedRole = Role.Builder.create(this, "unauth-role")
                .assumedBy(getPrincipalForAuthRoleKibana(identityPool, false))
                .managedPolicies(Collections.singletonList(
                        ManagedPolicy.Builder.create(this, "CognitoDefaultUnauthenticatedRole")
                                .statements(unauthStatements)
                                .build()))
                .build();

        Map<String, Object> roleMappings = new HashMap<>();
        roleMappings.put("unauthenticated", unauthenticatedRole.getRoleArn());
        roleMappings.put("authenticated", authenticatedRole.getRoleArn());
        CfnIdentityPoolRoleAttachment.Builder.create(this, "i-pool-role-attachment")
                .identityPoolId(identityPool.getRef())
                .roles(roleMappings)
                .build();
        return authenticatedRole;
    }

    private FederatedPrincipal getPrincipalForAuthRoleKibana(CfnIdentityPool identityPool, boolean auth) {
        Map<String, Object> conditions = new HashMap<>();
        conditions.put("StringEquals", new JSONObject()
                .put("cognito-identity.amazonaws.com:aud", identityPool.getRef())
                .toMap());
        conditions.put("ForAnyValue:StringLike", new JSONObject()
                .put("cognito-identity.amazonaws.com:amr", auth ? "authenticated" : "unauthenticated")
                .toMap());

        return new FederatedPrincipal("cognito-identity.amazonaws.com", conditions, "sts:AssumeRoleWithWebIdentity");
    }

    private Role createCognitoESRole() {
        List<String> actions = Arrays.asList("ec2:DescribeVpcs", "cognito-identity:ListIdentityPools", "cognito-idp:ListUserPools");
        List<IManagedPolicy> managedPolicies = Arrays.asList(
                ManagedPolicy.fromAwsManagedPolicyName("AmazonESCognitoAccess"),
                ManagedPolicy.Builder.create(this, DOMAIN_NAME + "es-cognito")
                        .statements(Collections.singletonList(PolicyStatement.Builder.create()
                                .effect(Effect.ALLOW)
                                .actions(actions)
                                .resources(Collections.singletonList("*"))
                                .build()))
                        .build());

        return Role.Builder.create(this, "ElasticSearchRole")
                .assumedBy(new ServicePrincipal("es.amazonaws.com"))
                .managedPolicies(managedPolicies)
                .build();
    }

    private CfnDomain createElasticSearchDomain(String roleArn, CfnUserPool userPool, CfnIdentityPool identityPool) {
        CfnDomain.CognitoOptionsProperty cognitoOptions = CfnDomain.CognitoOptionsProperty.builder()
                .enabled(true)
                .identityPoolId(identityPool.getRef())
                .userPoolId(userPool.getRef())
                .roleArn(roleArn)
                .build();

        return new CfnDomain(this, DOMAIN_NAME,
                CfnDomainProps.builder()
                        .domainName("infineon-" + getAccount())
                        .elasticsearchClusterConfig(createElasticSearchClusterConfig())
                        .elasticsearchVersion("7.7")
                        .cognitoOptions(cognitoOptions)
                        .nodeToNodeEncryptionOptions(CfnDomain.NodeToNodeEncryptionOptionsProperty.builder()
                                .enabled(true)
                                .build())
                        .domainEndpointOptions(CfnDomain.DomainEndpointOptionsProperty.builder()
                                .enforceHttps(true)
                                .build())
                        .ebsOptions(new CfnDomain.EBSOptionsProperty.Builder()
                                .ebsEnabled(true)
                                .volumeType("gp2")
                                .volumeSize(10)
                                .build())
                        .build());
    }

    private void configureUserPoolDomain(CfnUserPool userPool) {
        CfnUserPoolDomain.Builder.create(this, "user-pool-domain")
                .userPoolId(userPool.getRef())
                .domain(DOMAIN_NAME + "-" + getAccount())
                .build();
    }

    private PolicyDocument createElasticSearchAccessPolicies(Role authRole, Role cognitoESRole, String domainName) {
        String domain = "arn:aws:es:" + getRegion() + ":" + getAccount() + ":domain/" + domainName + "/*";
        PolicyStatement statement = new PolicyStatement(PolicyStatementProps.builder()
                .effect(Effect.ALLOW)
                .principals(Arrays.asList(authRole, cognitoESRole))
                .actions(Collections.singletonList("es:*"))
                .resources(Collections.singletonList(domain))
                .build());
        return new PolicyDocument(PolicyDocumentProps.builder()
                .statements(Collections.singletonList(statement))
                .build());
    }

    private Map.Entry<CfnUserPool, CfnUserPoolClient> createUserPoolAndClient() {
        CfnUserPool cfnUserPool = createUserPool();
        CfnUserPoolClient userPoolClient = CfnUserPoolClient.Builder.create(this, "user-pool-client")
                .userPoolId(cfnUserPool.getRef())
                .explicitAuthFlows(Arrays.asList("ALLOW_REFRESH_TOKEN_AUTH", "ALLOW_USER_PASSWORD_AUTH", "ALLOW_USER_SRP_AUTH"))
                .build();
        configureUserPoolDomain(cfnUserPool);
        return new HashMap.SimpleEntry<>(cfnUserPool, userPoolClient);
    }

    private CfnUserPool createUserPool() {
        CfnUserPool.PasswordPolicyProperty passwordPolicy = CfnUserPool.PasswordPolicyProperty.builder()
                .requireSymbols(false)
                .minimumLength(8)
                .temporaryPasswordValidityDays(7)
                .requireUppercase(false)
                .build();
        return CfnUserPool.Builder.create(this, "user-pool")
                .userPoolName(DOMAIN_NAME + "user-pool")
                .usernameAttributes(Collections.singletonList("email"))
                .accountRecoverySetting(CfnUserPool.AccountRecoverySettingProperty.builder()
                        .recoveryMechanisms(Collections.singletonList(
                                CfnUserPool.RecoveryOptionProperty.builder()
                                        .name("verified_email")
                                        .priority(1)
                                        .build()))
                        .build())
                .autoVerifiedAttributes(Collections.singletonList("email"))
                .policies(CfnUserPool.PoliciesProperty.builder()
                        .passwordPolicy(passwordPolicy)
                        .build())
                .build();
    }

    private CfnIdentityPool createIdentityPool(Map.Entry<CfnUserPool, CfnUserPoolClient> userPool) {
        List<Object> cognitoIdentityProviders = Collections.singletonList(CfnIdentityPool.CognitoIdentityProviderProperty.builder()
                .clientId(userPool.getValue().getRef())
                .providerName(userPool.getKey().getAttrProviderName())
                .build());
        return CfnIdentityPool.Builder.create(this, DOMAIN_NAME + "identity-pool")
                .identityPoolName(DOMAIN_NAME + "_identity_pool")
                .allowUnauthenticatedIdentities(false)
                .cognitoIdentityProviders(cognitoIdentityProviders)
                .build();
    }

    private CfnDomain.ElasticsearchClusterConfigProperty createElasticSearchClusterConfig() {
        return new CfnDomain.ElasticsearchClusterConfigProperty.Builder()
                .instanceCount(1)
                .instanceType("t2.medium.elasticsearch")
                .build();
    }

    /**
     * @param logs
     * @return IAM role for Kinesis Firehose Delivery Stream
     */
    private IRole getRoleForLogsToS3BucketDeliveryStream(Bucket logs) {
        //allow stream to put logs in s3 bucket
        PolicyStatement statement = PolicyStatement.Builder.create()
                .actions(Collections.singletonList("s3:*"))
                .effect(Effect.ALLOW)
                .resources(Collections.singletonList(logs.getBucketArn()))
                .build();
        ManagedPolicy policy = ManagedPolicy.Builder.create(this, DOMAIN_NAME + "logs-s3-role" + "-policy")
                .statements(Collections.singletonList(statement))
                .build();
        return Role.Builder.create(this, DOMAIN_NAME + "logs-s3-role")
                .roleName(DOMAIN_NAME + "logs-s3-role")
                .managedPolicies(Arrays.asList(policy,
                        ManagedPolicy.fromAwsManagedPolicyName("service-role/AWSLambdaKinesisExecutionRole")
                ))
                .assumedBy(new ServicePrincipal("firehose.amazonaws.com"))
                .build();
    }

    /**
     * Creates Kinesis Firehose Delivery Stream (from Kinesis Data Stream to S3 bucket)
     *
     * @param bucketArn     destination S3 bucket
     * @param roleArn       IAM role for delivery stream
     */
    private CfnDeliveryStream createFirehoseLogsToS3Stream(String bucketArn, String roleArn) {
        String streamName = DOMAIN_NAME + "_logss3-delivery-stream";
        // create source data transformation lambda (to extended json)

        CfnDeliveryStream.ExtendedS3DestinationConfigurationProperty s3DestinationConfiguration = CfnDeliveryStream
                .ExtendedS3DestinationConfigurationProperty.builder()
                .bucketArn(bucketArn)
                .cloudWatchLoggingOptions(getCloudWatchOptions("/kinesisfirehose/" + streamName, streamName))
                .bufferingHints(CfnDeliveryStream.BufferingHintsProperty.builder()
                        .intervalInSeconds(300)
                        .sizeInMBs(5)
                        .build())
                .compressionFormat("ZIP")
                .roleArn(roleArn)
                .build();
        return CfnDeliveryStream.Builder.create(this, streamName)
                .deliveryStreamName(streamName)
                .extendedS3DestinationConfiguration(s3DestinationConfiguration)
                .build();
    }

    private CfnDeliveryStream.CloudWatchLoggingOptionsProperty getCloudWatchOptions(String logGroup, String name) {
        return CfnDeliveryStream.CloudWatchLoggingOptionsProperty.builder()
                .logGroupName(logGroup)
                .logStreamName(name)
                .enabled(true)
                .build();
    }

}
