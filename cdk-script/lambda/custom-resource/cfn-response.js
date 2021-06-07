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
exports.Retry = exports.safeHandler = exports.includeStackTraces = exports.submitResponse = exports.MISSING_PHYSICAL_ID_MARKER = exports.CREATE_FAILED_PHYSICAL_ID_MARKER = void 0;
/* eslint-disable max-len */
/* eslint-disable no-console */
const url = require("url");
const outbound_1 = require("./outbound");
const util_1 = require("./util");
exports.CREATE_FAILED_PHYSICAL_ID_MARKER = 'AWSCDK::CustomResourceProviderFramework::CREATE_FAILED';
exports.MISSING_PHYSICAL_ID_MARKER = 'AWSCDK::CustomResourceProviderFramework::MISSING_PHYSICAL_ID';
async function submitResponse(status, event, options = {}) {
    const json = {
        Status: status,
        Reason: options.reason || status,
        StackId: event.StackId,
        RequestId: event.RequestId,
        PhysicalResourceId: event.PhysicalResourceId || exports.MISSING_PHYSICAL_ID_MARKER,
        LogicalResourceId: event.LogicalResourceId,
        NoEcho: options.noEcho,
        Data: event.Data,
    };
    util_1.log('submit response to cloudformation', json);
    const responseBody = JSON.stringify(json);
    const parsedUrl = url.parse(event.ResponseURL);
    await outbound_1.httpRequest({
        hostname: parsedUrl.hostname,
        path: parsedUrl.path,
        method: 'PUT',
        headers: {
            'content-type': '',
            'content-length': responseBody.length,
        },
    }, responseBody);
}
exports.submitResponse = submitResponse;
exports.includeStackTraces = true; // for unit tests
function safeHandler(block) {
    return async (event) => {
        // ignore DELETE event when the physical resource ID is the marker that
        // indicates that this DELETE is a subsequent DELETE to a failed CREATE
        // operation.
        if (event.RequestType === 'Delete' && event.PhysicalResourceId === exports.CREATE_FAILED_PHYSICAL_ID_MARKER) {
            util_1.log('ignoring DELETE event caused by a failed CREATE event');
            await submitResponse('SUCCESS', event);
            return;
        }
        try {
            await block(event);
        }
        catch (e) {
            // tell waiter state machine to retry
            if (e instanceof Retry) {
                util_1.log('retry requested by handler');
                throw e;
            }
            if (!event.PhysicalResourceId) {
                // special case: if CREATE fails, which usually implies, we usually don't
                // have a physical resource id. in this case, the subsequent DELETE
                // operation does not have any meaning, and will likely fail as well. to
                // address this, we use a marker so the provider framework can simply
                // ignore the subsequent DELETE.
                if (event.RequestType === 'Create') {
                    util_1.log('CREATE failed, responding with a marker physical resource id so that the subsequent DELETE will be ignored');
                    event.PhysicalResourceId = exports.CREATE_FAILED_PHYSICAL_ID_MARKER;
                }
                else {
                    // otherwise, if PhysicalResourceId is not specified, something is
                    // terribly wrong because all other events should have an ID.
                    util_1.log(`ERROR: Malformed event. "PhysicalResourceId" is required: ${JSON.stringify(event)}`);
                }
            }
            // this is an actual error, fail the activity altogether and exist.
            await submitResponse('FAILED', event, {
                reason: exports.includeStackTraces ? e.stack : e.message,
            });
        }
    };
}
exports.safeHandler = safeHandler;
class Retry extends Error {
}
exports.Retry = Retry;
