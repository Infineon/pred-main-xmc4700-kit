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
CURRENT_DIR=$(dirname $(readlink -f $0))

echo "=== Build application code (java) ==="
$CURRENT_DIR/build-stack.sh

echo "=== Deploy CloudFormation CDK Bootstrap ==="
cdk bootstrap

echo "=== Deploy stack from AWS ==="
cdk deploy  --require-approval never

$CURRENT_DIR/start-application.sh

$CURRENT_DIR/describe-stack.sh
