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

"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.httpRequest = exports.invokeFunction = exports.startExecution = void 0;
/* istanbul ignore file */
const https = require("https");
// eslint-disable-next-line import/no-extraneous-dependencies
const AWS = require("aws-sdk");
const FRAMEWORK_HANDLER_TIMEOUT = 900000; // 15 minutes
// In order to honor the overall maximum timeout set for the target process,
// the default 2 minutes from AWS SDK has to be overriden:
// https://docs.aws.amazon.com/AWSJavaScriptSDK/latest/AWS/Config.html#httpOptions-property
const awsSdkConfig = {
    httpOptions: { timeout: FRAMEWORK_HANDLER_TIMEOUT },
};
async function defaultHttpRequest(options, responseBody) {
    return new Promise((resolve, reject) => {
        try {
            const request = https.request(options, resolve);
            request.on('error', reject);
            request.write(responseBody);
            request.end();
        }
        catch (e) {
            reject(e);
        }
    });
}
let sfn;
let lambda;
async function defaultStartExecution(req) {
    if (!sfn) {
        sfn = new AWS.StepFunctions(awsSdkConfig);
    }
    return sfn.startExecution(req).promise();
}
async function defaultInvokeFunction(req) {
    if (!lambda) {
        lambda = new AWS.Lambda(awsSdkConfig);
    }
    return lambda.invoke(req).promise();
}
exports.startExecution = defaultStartExecution;
exports.invokeFunction = defaultInvokeFunction;
exports.httpRequest = defaultHttpRequest;
