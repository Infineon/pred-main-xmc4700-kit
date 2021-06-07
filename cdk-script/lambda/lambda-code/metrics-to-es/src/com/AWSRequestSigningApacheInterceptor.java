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

import com.amazonaws.DefaultRequest;
import com.amazonaws.auth.AWSCredentialsProvider;
import com.amazonaws.auth.Signer;
import com.amazonaws.http.HttpMethodName;
import org.apache.http.*;
import org.apache.http.client.utils.URIBuilder;
import org.apache.http.entity.BasicHttpEntity;
import org.apache.http.message.BasicHeader;
import org.apache.http.protocol.HttpContext;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import static org.apache.http.protocol.HttpCoreContext.HTTP_TARGET_HOST;

public class AWSRequestSigningApacheInterceptor implements HttpRequestInterceptor {
    private final String service;

    private final Signer signer;
    private final AWSCredentialsProvider awsCredentialsProvider;

    /**
     * @param service                service that we're connecting to
     * @param signer                 particular signer implementation
     * @param awsCredentialsProvider source of AWS credentials for signing
     */
    public AWSRequestSigningApacheInterceptor(final String service,
                                              final Signer signer,
                                              final AWSCredentialsProvider awsCredentialsProvider) {
        this.service = service;
        this.signer = signer;
        this.awsCredentialsProvider = awsCredentialsProvider;
    }

    @Override
    public void process(final HttpRequest request, final HttpContext context) throws IOException {
        URIBuilder uriBuilder;
        try {
            uriBuilder = new URIBuilder(request.getRequestLine().getUri());
        } catch (URISyntaxException e) {
            throw new IOException("Invalid URI", e);
        }

        // Copy Apache HttpRequest to AWS DefaultRequest
        DefaultRequest<?> signableRequest = new DefaultRequest<>(service);

        HttpHost host = (HttpHost) context.getAttribute(HTTP_TARGET_HOST);
        if (host != null) {
            signableRequest.setEndpoint(URI.create(host.toURI()));
        }
        final HttpMethodName httpMethod = HttpMethodName.fromValue(request.getRequestLine().getMethod());
        signableRequest.setHttpMethod(httpMethod);
        try {
            signableRequest.setResourcePath(uriBuilder.build().getRawPath());
        } catch (URISyntaxException e) {
            throw new IOException("Invalid URI", e);
        }

        if (request instanceof HttpEntityEnclosingRequest) {
            HttpEntityEnclosingRequest httpEntityEnclosingRequest =
                    (HttpEntityEnclosingRequest) request;
            if (httpEntityEnclosingRequest.getEntity() == null) {
                signableRequest.setContent(new ByteArrayInputStream(new byte[0]));
            } else {
                signableRequest.setContent(httpEntityEnclosingRequest.getEntity().getContent());
            }
        }
        signableRequest.setParameters(nvpToMapParams(uriBuilder.getQueryParams()));
        signableRequest.setHeaders(headerArrayToMap(request.getAllHeaders()));

        // Sign it
        signer.sign(signableRequest, awsCredentialsProvider.getCredentials());

        // Now copy everything back
        request.setHeaders(mapToHeaderArray(signableRequest.getHeaders()));
        if (request instanceof HttpEntityEnclosingRequest) {
            HttpEntityEnclosingRequest httpEntityEnclosingRequest =
                    (HttpEntityEnclosingRequest) request;
            if (httpEntityEnclosingRequest.getEntity() != null) {
                BasicHttpEntity basicHttpEntity = new BasicHttpEntity();
                basicHttpEntity.setContent(signableRequest.getContent());
                httpEntityEnclosingRequest.setEntity(basicHttpEntity);
            }
        }
    }

    /**
     * @param params list of HTTP query params as NameValuePairs
     * @return a multimap of HTTP query params
     */
    private static Map<String, List<String>> nvpToMapParams(final List<NameValuePair> params) {
        Map<String, List<String>> parameterMap = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
        for (NameValuePair nvp : params) {
            List<String> argsList = parameterMap.computeIfAbsent(nvp.getName(), k -> new ArrayList<>());
            argsList.add(nvp.getValue());
        }
        return parameterMap;
    }

    /**
     * @param headers modeled Header objects
     * @return a Map of header entries
     */
    private static Map<String, String> headerArrayToMap(final Header[] headers) {
        Map<String, String> headersMap = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
        for (Header header : headers) {
            if (!skipHeader(header)) {
                headersMap.put(header.getName(), header.getValue());
            }
        }
        return headersMap;
    }

    /**
     * @param header header line to check
     * @return true if the given header should be excluded when signing
     */
    private static boolean skipHeader(final Header header) {
        return ("content-length".equalsIgnoreCase(header.getName())
                && "0".equals(header.getValue())) // Strip Content-Length: 0
                || "host".equalsIgnoreCase(header.getName()); // Host comes from endpoint
    }

    /**
     * @param mapHeaders Map of header entries
     * @return modeled Header objects
     */
    private static Header[] mapToHeaderArray(final Map<String, String> mapHeaders) {
        Header[] headers = new Header[mapHeaders.size()];
        int i = 0;
        for (Map.Entry<String, String> headerEntry : mapHeaders.entrySet()) {
            headers[i++] = new BasicHeader(headerEntry.getKey(), headerEntry.getValue());
        }
        return headers;
    }
}
