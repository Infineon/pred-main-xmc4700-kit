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
import requests
import json
from requests_aws4auth import AWS4Auth
import os

class KibanaThing:
    def __init__(self):
        self.client_cl = boto3.client('cloudformation')

        self.board_name = os.getenv("KIBANA_DASHBOARD_NAME", "InfineonBoard Detailed")
        credentials = boto3.Session().get_credentials()

        aws_session = boto3.session.Session()
        region = aws_session.region_name

        self.es_client = boto3.client("es")
        self.awsauth = AWS4Auth(credentials.access_key, credentials.secret_key, region, "es", session_token=credentials.token)
        self.kibana_url = self.get_kibana_url()
        if not self.kibana_url:
            print('Error: kibana url is unknown')
            exit()

    def get_kibana_url(self):
        response = self.client_cl.describe_stacks(
            StackName='InfineonKitRealtime' #todo
        )
        kibana_url=""
        i = 0
        while i < len(response['Stacks'][0]['Outputs']):

            if response['Stacks'][0]['Outputs'][i]['OutputKey'] == 'KibanaUrl':
                kibana_url = response['Stacks'][0]['Outputs'][i]['OutputValue']
            i += 1
        return kibana_url

    def create_query_if_needed(self, thing_name):

        new_url = self.kibana_url + '/api/saved_objects/_find?type=query&search_fields=title&search=' + thing_name
        try:

            resp1 = requests.get(new_url, auth=self.awsauth)

            json_byte = resp1.content
            data = json.loads(json_byte)

            if data["total"] < 1:
                return self.create_query(thing_name)

            i = 0
            while i < len(data["saved_objects"]):
                if data["saved_objects"][i]["attributes"]["title"] == thing_name:
                    print("Thing already registered in kibana dashboard")
                    return
                i += 1

            self.create_query(thing_name)

        except requests.exceptions.ConnectionError as e:
            print('Connection refused'.format(e))


    def create_query(self, thing_name):
        save_url = self.kibana_url +'/api/saved_objects/query/'
        try:
            js = {
                "attributes": {
                    "title": thing_name,
                    'query': {'query': 'PARTITION_KEY:{} OR thingName:{}'.format(thing_name, thing_name),
                              'language': 'kuery'}
                }
            }
            requests.post(save_url, auth=self.awsauth, json=js, headers={'kbn-xsrf': 'true'})
            print("Successfully added thing to kibana dashboard")

        except requests.exceptions.ConnectionError as e:
            print('Connection refused'.format(e))

    def delete_query_if_needed(self, thing_name):

        new_url = self.kibana_url + '/api/saved_objects/_find?type=query&search_fields=title&search=' + thing_name
        try:

            resp1 = requests.get(new_url, auth=self.awsauth)

            json_byte = resp1.content
            data = json.loads(json_byte)

            if data["total"] < 1:
                return

            i = 0
            while i < len(data["saved_objects"]):
                if data["saved_objects"][i]["attributes"]["title"] == thing_name and data["saved_objects"][i]["attributes"]["query"]["query"] == 'PARTITION_KEY:{} OR thingName:{}'.format(thing_name, thing_name):
                    self.delete_query(data["saved_objects"][i]["id"])
                    return
                i += 1

        except requests.exceptions.ConnectionError as e:
            print('Connection refused'.format(e))


    def delete_query(self, id):
        delete_url = self.kibana_url +'/api/saved_objects/query/'+id
        try:
            requests.delete(delete_url, auth=self.awsauth, headers={'kbn-xsrf': 'true'})
            print("Successfully deleted thing from kibana dashboard")

        except requests.exceptions.ConnectionError as e:
            print('Connection refused'.format(e))