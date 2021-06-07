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

import sys
from kibana_thing import KibanaThing
sys.path.append('../')

import boto3

thing_name = input("Enter thing name: ")

if not thing_name:
    print("Error: thing name should be provided")
    exit()

if thing_name=="":
    exit("Thing name should be provided")

def delete_thing(thing_name):
    print("Started clearing thing {} ...".format(thing_name))

    try:
        r_principals = c_iot.list_thing_principals(thingName=thing_name)
    except Exception as e:
        print("ERROR getting thing: {}".format(e))
        r_principals = {'principals': []}
        exit()

    try:
        for arn in r_principals['principals']:
            cert_id = arn.split('/')[1]
            print("arn: {} cert_id: {}".format(arn, cert_id))

            c_iot.detach_thing_principal(thingName=thing_name, principal=arn)
            print("Detached thing {} from certificate: {}".format(thing_name, arn))

            c_iot.update_certificate(certificateId=cert_id, newStatus='INACTIVE')
            print("Inactivate certificate {}".format(arn))

            r_policies = c_iot.list_principal_policies(principal=arn)

            for pol in r_policies['policies']:
                pol_name = pol['policyName']
                print("Policy name to detach: {}".format(pol_name))
                c_iot.detach_policy(policyName=pol_name, target=arn)

            c_iot.delete_certificate(certificateId=cert_id, forceDelete=True)
            print("Deleted certificate {}".format(arn))

        c_iot.delete_thing(thingName=thing_name)
        print("Deleted thing {}".format(thing_name))
    except Exception as e:
        print("ERROR deleting thing: {}".format(thing_name))
        exit()


c_iot = boto3.client('iot')
c_iot_data = boto3.client('iot-data')

delete_thing(thing_name)
kibana = KibanaThing()
kibana.delete_query_if_needed(thing_name)