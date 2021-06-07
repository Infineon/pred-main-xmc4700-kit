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


# shellcheck disable=SC2046

APP_NAME=$(aws cloudformation describe-stacks --stack-name InfineonKitRealtime | jq -r '.Stacks[0].Outputs[] | select(.OutputKey == "AnalyticsApp").OutputValue')

if [ -z "$APP_NAME" ]; then
  echo "unknown application"
  exit
fi

APP_STATUS=$(aws kinesisanalytics describe-application --application-name "${APP_NAME}" | jq -r '.ApplicationDetail.ApplicationStatus')

if [ "$APP_STATUS" == "RUNNING" ]; then
  echo "Application is already running"
  exit
fi

APP_ID=$(aws kinesisanalytics describe-application --application-name "${APP_NAME}" | jq -r '.ApplicationDetail.InputDescriptions[0].InputId')

if [ -z "$APP_ID" ]; then
  echo "id for the application is unknown"
  exit
fi

aws kinesisanalytics start-application --application-name "${APP_NAME}" --input-configurations Id="${APP_ID}",InputStartingPositionConfiguration={InputStartingPosition="NOW"}

