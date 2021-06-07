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

import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestHandler;
import com.amazonaws.services.lambda.runtime.events.KinesisAnalyticsInputPreprocessingResponse;
import com.amazonaws.services.lambda.runtime.events.KinesisAnalyticsStreamsInputPreprocessingEvent;
import org.json.JSONObject;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.sql.Date;
import java.util.ArrayList;
import java.util.logging.Logger;

public class JsonLambdaConverter implements RequestHandler<KinesisAnalyticsStreamsInputPreprocessingEvent, KinesisAnalyticsInputPreprocessingResponse> {

    @Override
    public KinesisAnalyticsInputPreprocessingResponse handleRequest(KinesisAnalyticsStreamsInputPreprocessingEvent event, Context context) {
        KinesisAnalyticsInputPreprocessingResponse response = new KinesisAnalyticsInputPreprocessingResponse(new ArrayList<>());

        event.getRecords().forEach(record -> {
            Long approximateArrivalTimestamp = record.getKinesisStreamRecordMetadata().approximateArrivalTimestamp;
            String inputJson = new String(record.getData().array(), StandardCharsets.UTF_8);
            context.getLogger().log("input data" + inputJson);
            String outputJson = convertInputJson(inputJson, approximateArrivalTimestamp);
            context.getLogger().log("json data " + outputJson);
            ByteBuffer wrap = ByteBuffer.wrap(outputJson.getBytes(StandardCharsets.UTF_8));
            KinesisAnalyticsInputPreprocessingResponse.Record result = new KinesisAnalyticsInputPreprocessingResponse
                    .Record(record.getRecordId(), KinesisAnalyticsInputPreprocessingResponse.Result.Ok, wrap);
            response.records.add(result);
        });
        return response;
    }

    public String convertInputJson(String inputJsonString, Long approximateArrivalTimestamp) {
        Logger.getGlobal().info(inputJsonString);
        JSONObject inputJsontmp = new JSONObject(inputJsonString);
        JSONObject inputJson = inputJsontmp.getJSONObject("pl");
        JSONObject commonJsonStructure = Utils.buildCommonJsonStructure();
        inputJson.keySet().forEach(k -> {
            commonJsonStructure.remove(k);
            commonJsonStructure.put(k, inputJson.get(k));
        });
        JSONObject finalJson = Utils.changeFinalJson(commonJsonStructure);
        finalJson.put("approximateArrivalTime", new Date(approximateArrivalTimestamp));
        return finalJson.toString();
    }
}
