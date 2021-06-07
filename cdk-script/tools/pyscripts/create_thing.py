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

import boto3
from kibana_thing import KibanaThing
import os

CERT_BEGIN="-----BEGIN CERTIFICATE-----"
CERT_END="-----END CERTIFICATE-----"
policyname = "infn-device-policy"

thing_name = input("Enter thing name: ")

if not thing_name:
    print("Error: thing name should be provided")
    exit()

print("Please, enter device certificate's text (starts with '-----BEGIN CERTIFICATE-----' and ends with '-----END CERTIFICATE-----'): ")

cert = ""
while True:
    lines = input()
    if CERT_BEGIN in lines:
        cert = lines
    else:
        cert = cert + "\n" + lines

    if CERT_END in lines or not lines:
        break

if not cert:
    print("Error: certificate text should be provided")
    exit()

if not CERT_END in cert or not CERT_BEGIN in cert:
    print("Error: incorrect certificate content. Should include '{}' and '{}'".format(CERT_BEGIN, CERT_END))
    exit()

aws_session = boto3.session.Session()
region = aws_session.region_name
account = boto3.client('sts').get_caller_identity().get('Account')

def create_thing(thing_name):
    print("Started creating {}".format(thing_name))

    try:
        thing = c_iot.describe_thing(thingName=thing_name)
        if thing['thingName'] == thing_name:
            print("ERROR: thing already exists. Please delete it with: 'make deregister-device'")
            exit()
    except Exception as e:
        if e.response['Error']['Code'] != 'ResourceNotFoundException':
            print("ERROR creating thing: {}".format(e))
            exit()

    try:
        c_iot.create_thing(thingName=thing_name)
    except Exception as e:
        print("ERROR creating thing: {}".format(e))
        exit()

    policyexists = False
    try:
        response = c_iot.get_policy(policyName=policyname)
        if response['policyName'] == policyname:
            policyexists = True
    except Exception as e:
        if e.response['Error']['Code'] != 'ResourceNotFoundException':
            print("ERROR creating policy: {}".format(e))
            exit()

    if not policyexists:
        policy_doc = "{\"Version\":\"2012-10-17\",\"Statement\":[{\"Effect\":\"Allow\",\"Action\":[\"iot:Publish\"],\"Resource\":[\"arn:aws:iot:"+region+":"+account+":topic\/$aws\/rules\/redirect_metrics\/infn\/dev\/${iot:Connection.Thing.ThingName}\"]},{\"Effect\":\"Allow\",\"Action\":[\"iot:Connect\"],\"Resource\":[\"arn:aws:iot:"+region+":"+account+":client\/${iot:Connection.Thing.ThingName}\"]}]}"
        try:
            c_iot.create_policy(
                policyName=policyname,
                policyDocument=policy_doc
            )
            print("Created policy {}".format(policyname))
        except Exception as e:
            print("ERROR creating policy: {}".format(e))
            exit()


    cert_arn = None
    try:
        response = c_iot.register_certificate_without_ca(
            certificatePem=cert,
            status='ACTIVE'
        )
        cert_arn = response['certificateArn']
        print("Registered certificate {}".format(cert_arn))

    except Exception as e:
        if e.response['Error']['Code'] == 'ResourceAlreadyExistsException':
            try:
                response = c_iot.list_principal_things(
                    principal=e.response['resourceArn']
                )
                print("ERROR registering certificate. It is attached to things: {}".format(', '.join(response['things'])))

                c_iot.delete_thing(thingName=thing_name)
            except Exception as e:
                print("ERROR registering certificate: {}".format(e))
        else:
            print("ERROR registering certificate: {}".format(e))

        exit()

    try:
        c_iot.attach_policy(
            policyName=policyname,
            target=cert_arn
        )
        print("Attached policy {} to certificate {}".format(policyname, cert_arn))

        c_iot.attach_thing_principal(
            thingName=thing_name,
            principal=cert_arn
        )
        print("Attached certificate {} to thing".format(cert_arn))
    except Exception as e:
        print("ERROR registering thing: {}".format(e))
        exit()

c_iot = boto3.client('iot')
c_iot_data = boto3.client('iot-data')
create_thing(thing_name)

kibana = KibanaThing()
kibana.create_query_if_needed(thing_name)

text_file = open(os.path.dirname(os.path.abspath(__file__))+'/../../../patch/credentials/thing_name.txt', "w")
text_file.write(thing_name)
text_file.close()