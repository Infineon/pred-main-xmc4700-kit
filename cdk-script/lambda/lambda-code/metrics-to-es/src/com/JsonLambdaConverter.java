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

package com;

import com.amazonaws.auth.AWS4Signer;
import com.amazonaws.auth.AWSCredentialsProvider;
import com.amazonaws.auth.DefaultAWSCredentialsProviderChain;
import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestHandler;
import org.apache.http.HttpHost;
import org.apache.http.HttpRequestInterceptor;
import org.elasticsearch.action.index.IndexRequest;
import org.elasticsearch.action.index.IndexResponse;
import org.elasticsearch.client.RequestOptions;
import org.elasticsearch.client.RestClient;
import org.elasticsearch.client.RestHighLevelClient;
import org.elasticsearch.common.xcontent.XContentType;
import org.json.JSONObject;

import java.io.IOException;
import java.time.ZonedDateTime;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.logging.Logger;

public class JsonLambdaConverter implements RequestHandler<Map<String, Object>, String> {

    private static final AWSCredentialsProvider credentialsProvider = new DefaultAWSCredentialsProviderChain();

    private String sendDoc(String doc) throws IOException {
        RestHighLevelClient esClient = esClient();
        JSONObject dataAsJson = new JSONObject(doc);
        HashMap<String, Object> dataAsMap = new HashMap<String, Object>(dataAsJson.toMap());
        // Form the indexing request, send it, and print the response
        IndexRequest request = new IndexRequest("infineon-sensors", "_doc").source(dataAsMap, XContentType.JSON);
        IndexResponse response = esClient.index(request, RequestOptions.DEFAULT);
        request.isPipelineResolved(true);
        esClient.close();
        return response.toString();
    }

    // Adds the interceptor to the ES REST client
    private RestHighLevelClient esClient() {
        AWS4Signer signer = new AWS4Signer();
        signer.setServiceName("es");
        signer.setRegionName(System.getenv("AWS_REGION"));
        HttpRequestInterceptor interceptor = new AWSRequestSigningApacheInterceptor("es", signer, credentialsProvider);
        String aesEndpoint = System.getenv("AWS_DOMAIN");
        Logger.getGlobal().info(aesEndpoint);

        return new RestHighLevelClient(RestClient.builder(HttpHost.create(aesEndpoint))
                .setHttpClientConfigCallback(hacb -> hacb.addInterceptorLast(interceptor)));
    }

    private String convertInputJson(JSONObject inputJsonString, String deviceName) {
        JSONObject commonJsonStructure = Utils.buildCommonJsonStructure();
        inputJsonString.keySet().forEach(k -> {
            commonJsonStructure.remove(k);
            commonJsonStructure.put(k, inputJsonString.get(k));
        });
        JSONObject finalJson = Utils.changeFinalJson(commonJsonStructure);
        finalJson.put("thingName", deviceName);
        finalJson.put("approximateArrivalTime", ZonedDateTime.now().toString().replace("[UTC]", ""));
        return finalJson.toString();
    }

    @Override
    public String handleRequest(Map<String, Object> input, Context context) {
        String deviceName = (String) input.get("n");
        JSONObject data = new JSONObject((LinkedHashMap) input.get("pl"));
        context.getLogger().log("in " + input);

        String out = convertInputJson(data, deviceName);
        context.getLogger().log("out " + out);

        try {
            String resp = sendDoc(out);
            context.getLogger().log("resp " + resp);

        } catch (IOException e) {
            e.printStackTrace();
        }
        context.getLogger().log(out);
        return out;
    }
}
