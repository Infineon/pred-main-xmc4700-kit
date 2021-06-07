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

import glob
import os

def main():
    page_offset = 2048
    current_offset = 0
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    f_out = open("patch.bin", "wb")

    # find endpoint file
    for find_file in glob.glob("../credentials/endpoint.txt"):
        #print(find_file)
        pass
    f_endpoint = open(find_file, "rb")
    lines = f_endpoint.read()
    endpoint = bytearray()
    endpoint.extend(lines)
    endpoint.append(0)
    f_out.seek(current_offset)
    f_out.write(endpoint)
    f_endpoint.close()

    # find thing_name file
    current_offset += page_offset
    for find_file in glob.glob("../credentials/thing_name.txt"):
        #print(find_file)
        pass
    f_thing_name = open(find_file, "rb")
    lines = f_thing_name.read()
    thing_name = bytearray()
    thing_name.extend(lines)
    thing_name.append(0)
    f_out.seek(current_offset)
    f_out.write(thing_name)
    f_thing_name.close()

    # find wifi_ssid file
    current_offset += page_offset
    for find_file in glob.glob("../credentials/wifi_ssid.txt"):
        #print(find_file)
        pass
    f_wifi_ssid = open(find_file, "rb")
    lines = f_wifi_ssid.read()
    wifi_ssid = bytearray()
    wifi_ssid.extend(lines)
    wifi_ssid.append(0)
    f_out.seek(current_offset)
    f_out.write(wifi_ssid)
    f_wifi_ssid.close()

    # find wifi_pass file
    current_offset += page_offset
    for find_file in glob.glob("../credentials/wifi_pass.txt"):
        #print(find_file)
        pass
    f_wifi_pass = open(find_file, "rb")
    lines = f_wifi_pass.read()
    wifi_pass = bytearray()
    wifi_pass.extend(lines)
    wifi_pass.append(0)
    f_out.seek(current_offset)
    f_out.write(wifi_pass)
    f_wifi_pass.close()


    f_out.close()

if __name__ == "__main__":
    main()