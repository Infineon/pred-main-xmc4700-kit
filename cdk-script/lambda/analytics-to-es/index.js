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

let AWS = require('aws-sdk');
let path = require('path');
let region = process.env.AWS_REGION;
let domain = process.env.AWS_DOMAIN;

/* == Globals == */
let esDomain = {
    region: region,
    endpoint: domain,
    index: 'infineon-as',
    doctype: '_doc'
};
let endpoint = new AWS.Endpoint(esDomain.endpoint);
let creds = new AWS.EnvironmentCredentials('AWS');

exports.handler = async (event, context) => {
    let success = 0;
    let failure = 0;
    const output = event.records.map((record) => {

        const recordData = Buffer.from(record.data, 'base64').toString();
        console.log("decoded", recordData)

        let result
        try {
            result = JSON.parse(recordData);
        } catch (err) {
            console.log("can't parse json", err, "delete record", recordData)
            failure++;
            return {
                recordId: record.recordId,
                result: 'Ok',
            };
        }

        try {
            result['approximateArrivalTime'] = new Date().toISOString();
            let doc = JSON.stringify(result);
            postToES(doc);

            success++;
            return {
                recordId: record.recordId,
                result: 'Ok',
            };
        } catch (err) {
            console.log("error inserting data to es", err)
            failure++;
            return {
                recordId: record.recordId,
                result: 'DeliveryFailed',
            };
        }
    });
    console.log(`Successful delivered records ${success}, Failed delivered records ${failure}.`);
    return { records: output };
};

/*
 * Post the given document to Elasticsearch
 */
function postToES(doc) {
    let req = new AWS.HttpRequest(endpoint);
    req.method = 'POST';
    req.path = path.join('/', esDomain.index, esDomain.doctype);
    req.region = esDomain.region;
    req.headers['presigned-expires'] = false;
    req.headers['Host'] = endpoint.host;
    req.headers['Content-Type'] = ['application/json'];
    req.body = doc;

    let signer = new AWS.Signers.V4(req , 'es');  // es: service code
    signer.addAuthorization(creds, new Date());

    let send = new AWS.NodeHttpClient();
    send.handleRequest(req, null, function(httpResp) {
        let respBody = '';
        console.log(respBody);
        httpResp.on('data', function (chunk) {
            respBody += chunk;
        });
        httpResp.on('end', function (chunk) {
            console.log(doc);
            console.log('send time: %o %o',  new Date().getTime(), respBody);
            req.shouldKeepAlive = false;
        });
    }, function(err) {
        console.log('Error: ' + err);
        try {
            creds = new AWS.EnvironmentCredentials('AWS');
        } catch (e) {
            console.log('can\'t refresh signature creds: ' + e);
        }

    });
}
