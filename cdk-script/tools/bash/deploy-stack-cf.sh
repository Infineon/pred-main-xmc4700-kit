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

# progress bar function
show_progress() {
    local w=$(expr $(tput cols) / 3) p=$1;  shift
    # create a string of spaces, then change them to dots (#)
    printf -v dots "%*s" "$(( $p*$w/100 ))" ""; dots=${dots// /#};
    # print those dots on a fixed-width space plus the percentage etc.
    printf "\r\e[K[%-*s] %3d %% %s" "$w" "$dots" "$p" "$*";
}

# shellcheck disable=SC2046
CURRENT_DIR=$(dirname $(readlink -f $0))

ACCOUNT_ID=$(aws sts get-caller-identity --query Account --output text)
AWS_DEFAULT_REGION=$(aws configure get region)

#create bucket for uploading lambda code
BUCKET_NAME="cf-deploy-${ACCOUNT_ID}-${AWS_DEFAULT_REGION}"

aws s3api create-bucket --bucket "$BUCKET_NAME"

aws s3api wait bucket-exists --bucket "$BUCKET_NAME"

echo -e "\n=== Upload packages to AWS s3 ==="
timestamp=$(date +%s)

aws cloudformation package --template-file $CURRENT_DIR/../../cf/RealTimeStack.yaml --s3-bucket "$BUCKET_NAME" \
 --s3-prefix "$timestamp" --output-template-file $CURRENT_DIR/../../cf/RealTimeStack-packaged.yaml > /dev/null 2>&1

echo -e "\n=== Deploy stack to AWS ===\nIt will take about 30 minutes, so please be patient."

aws cloudformation deploy --template-file $CURRENT_DIR/../../cf/RealTimeStack-packaged.yaml \
 --s3-bucket "$BUCKET_NAME" \
 --capabilities CAPABILITY_NAMED_IAM \
 --stack-name InfineonKitRealtime > /dev/null 2>&1 &

RESOURCES_COUNT=$(yq eval '.Resources | length' $CURRENT_DIR/../../cf/RealTimeStack.yaml)
echo -e "\nCount of resources to be deployed: "$RESOURCES_COUNT

STARTTIME=$(date +%s)

# spinner  
sp="/-\|"

# disable cursor
tput civis -- invisible

# ~ minute delay before checking deploy status
wait_time=0
printf "Waiting for deploy status  "
while [ "$wait_time" -lt 600 ]; do
  # sleep 0.1 sec for fast spinner drawing
  sleep .1
  (( wait_time++ ))
  # show progress and spinner
  printf "\b${sp:i++%${#sp}:1}"
done 
printf "\b DONE\n"

while true
do
  CURTIME=$(date +%s)
  ELAPSEDTIME=$(($CURTIME - $STARTTIME))

  STATUS=$(aws cloudformation describe-stacks --stack-name InfineonKitRealtime | jq -r '.Stacks[0].StackStatus')
  
  RESOURCES_STATUS=$(aws cloudformation describe-stack-resources --stack-name InfineonKitRealtime)
  RESOURCES_IN_PROCESS=$(jq '.StackResources[] | select(.ResourceStatus | endswith("IN_PROCESS")) | length' <(echo "$RESOURCES_STATUS") | wc -l)
  RESOURCES_COMPLETE=$(jq '.StackResources[] | select(.ResourceStatus | endswith("COMPLETE")) | length' <(echo "$RESOURCES_STATUS") | wc -l)
  RESOURCES_FAILED=$(jq '.StackResources[] | select(.ResourceStatus | endswith("FAILED")) | length' <(echo "$RESOURCES_STATUS") | wc -l)  
 
  DONE_COUNT=$(( $RESOURCES_COMPLETE + $RESOURCES_FAILED ))
  PERCENTAGE=$(( ($DONE_COUNT*100) / $RESOURCES_COUNT ))

  # show progress
  show_progress "$PERCENTAGE" "  Complete: $RESOURCES_COMPLETE resources;  Failed: $RESOURCES_FAILED resources.    "  

  if [ "$STATUS" == "CREATE_COMPLETE" ] || [ "$STATUS" = "UPDATE_COMPLETE" ]; then
    echo -e "\nStack was successfully deployed"
    break
  fi

  # if there's no any updates from stack for 10 mins, then fail
  if [ -z "$STATUS" ] && [ "$ELAPSEDTIME" -gt 600 ]; then
    echo -e "\nFailed to deploy stack. Timeout 10min occurred"
    # enable cursor back
    tput cnorm -- normal
    exit 1
  fi

  if [[ "$STATUS" != *IN_PROGRESS ]]; then
    REASON=$(aws cloudformation describe-stacks --stack-name InfineonKitRealtime | jq -r '.Stacks[0].StackStatusReason')
    echo -e "\nFailed to deploy stack. ${REASON}"
    # enable cursor back
    tput cnorm -- normal
    exit 1
  fi
  
  # 5 sec delay before new request
  request_time=0
  while [ "$request_time" -lt 50 ]; do
    # sleep 0.1 sec for fast spinner drawing
    sleep .1
    (( request_time++ ))
    # show spinner while waiting
    printf "\b${sp:i++%${#sp}:1}"
  done  
  (( request_time=0 ))  

done

# enable cursor back
tput cnorm -- normal

$CURRENT_DIR/start-application.sh

echo -e "\n=== AWS stack information ==="
$CURRENT_DIR/describe-stack.sh
