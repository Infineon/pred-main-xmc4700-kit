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

apt-get update && \
  apt-get install --yes curl unzip jq less dos2unix apt-utils build-essential && \
  rm -rf /var/lib/apt/lists/*
  
distr=$(uname -s | tr '[:upper:]' '[:lower:]')_$([ $(uname -m) == "x86_64" ] && echo amd64 || echo 'unknown arch')
curl -sL $(curl -s https://api.github.com/repos/mikefarah/yq/releases/latest | grep browser_download_url | grep $distr | cut -d: -f 2,3 | tr -d \") -o /usr/local/bin/yq
chmod +x /usr/local/bin/yq

# Install AWS CLI
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o awscliv2.zip \
    && unzip awscliv2.zip \
    && ./aws/install

rm -rf awscliv2.zip
mv aws ~/aws

# Install Node.js
curl -sL https://deb.nodesource.com/setup_lts.x | bash - \
    && apt-get install -y nodejs

# Install cdk as Node.js global packages
npm install -g aws-cdk

apt-get update && \
  apt-get install -y maven

apt-get update && \
  apt-get install -y default-jre && \
  apt install -y default-jdk

# Install Python 3.8
apt-get update && \
  apt-get install --yes python3 python3-pip python3-distutils python3-testresources && \
  rm -rf /var/lib/apt/lists/*

# Install python scripts dependencies
python3 -m pip install -r ./tools/pyscripts/requirements.txt
