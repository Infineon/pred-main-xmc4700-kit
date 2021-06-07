#!/bin/bash
#
# Copyright (C) 2021 Infineon Technologies AG.
#
# Licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License
# Agreement V1.0 (the "License"); you may not use this file except in compliance
# with the License.

# For receiving a copy of the License, please refer to:
#
# https://github.com/Infineon/pred-main-xmc4700-kit/LICENSE.txt
#
# Licensee acknowledges that the Licensed Items are provided by Licensor free of
# charge. Accordingly, without prejudice to Section 9 of the License, the
# Licensed Items provided by Licensor under this Agreement are provided "AS IS"
# without any warranty or liability of any kind and Licensor hereby expressly
# disclaims any warranties or representations, whether express, implied,
# statutory or otherwise, including but not limited to warranties of
# workmanship, merchantability, fitness for a particular purpose, defects in the
# Licensed Items, or non-infringement of third parties' intellectual property
# rights.
#

# shellcheck disable=SC2034
# shellcheck disable=SC2046
# shellcheck disable=SC2155

export PROV_IOT_ENDPOINT=$(aws iot describe-endpoint --endpoint-type iot:Data-ATS | jq -r '.endpointAddress')
export KIBANA_LINK=$(aws cloudformation describe-stacks --stack-name InfineonKitRealtime | jq -r '.Stacks[0].Outputs[] | select(.OutputKey == "KibanaUrl").OutputValue')
export DEVICE_LOGS=$(aws cloudformation describe-stacks --stack-name InfineonKitRealtime | jq -r '.Stacks[0].Outputs[] | select(.OutputKey == "deviceLogs").OutputValue')

echo "Access Kibana via this URL: ${KIBANA_LINK}" && echo $KIBANA_LINK > ./../patch/credentials/kibana.txt
echo "The URL was saved to "$(realpath ./../patch/credentials/kibana.txt)
echo "Bucket with device telematics data: ${DEVICE_LOGS}"
echo -e "\nIoT Endpoint : ${PROV_IOT_ENDPOINT}"
echo "The Endpoint was saved to "$(realpath ./../patch/credentials/endpoint.txt)