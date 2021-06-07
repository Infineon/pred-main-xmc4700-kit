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
 
package com;

import org.json.JSONArray;
import org.json.JSONObject;

class Utils {

    private static final String DPS368Temperature_1 = "DPS368Temperature_1"; //"TemperatureColdOutlet";
    private static final String DPS368Temperature_2 = "DPS368Temperature_2"; //"TemperatureHotOutlet";
    private static final String DPS368Pressure_1 = "DPS368Pressure_1"; //"PressureColdOutlet";
    private static final String DPS368Pressure_2 = "DPS368Pressure_2"; //"PressureHotOutlet";
    private static final String DPS368Temperature_3 = "DPS368Temperature_3"; //"TemperatureCompressor";
    private static final String DPS368Pressure_3 = "DPS368Pressure_3"; //"PressureCompressor";
    private static final String DPS368Temperature_4 = "DPS368Temperature_4";  // < Temperature, dps310/368
    private static final String DPS368Pressure_4 = "DPS368Pressure_4";       // < Air pressure, dps310/368
    private static final String DPS368Temperature_5 = "DPS368Temperature_5";// < Temperature, dps310/368
    private static final String DPS368Pressure_5 = "DPS368Pressure_5";      // < Air pressure, dps310/368
    private static final String TLI4971Current_1 = "TLI4971Current_1"; //"CurrentCompressor";
    private static final String TLI4971Current_2 = "TLI4971Current_2"; //"CurrentFanTop";
    private static final String TLI4971Current_3 = "TLI4971Current_3"; //"CurrentFanBottom";
    private static final String TLE4997LinearHall_1 = "TLE4997LinearHall_1"; //"Hall";
    private static final String IM69dMic_1 = "IM69dMic_1"; //"Mic";
    private static final String TLI4964Hall_1 = "TLE4964Hall_1";            // < Hall Magnetic field value, tle4964
    private static final String TLE49613kHall_1 = "TLE49613kHall_1";            // < Hall Magnetic field value, tle49613
    private static final String TLI4966gDoubleHall_Speed_1 = "TLI4966gDoubleHall_Speed_1";   // < Double Hall Speed, tli4966
    private static final String TLI4966gDoubleHall_Dir_1 = "TLI4966gDoubleHall_Dir_1";   // < Double Hall Speed, tli4966
    private static final String TLE4913Hall_1 = "TLE4913Hall_1";   // < Double Hall Speed, tli4966
    private static final String TLE49611kHall_1 = "TLE49611kHall_1";   // <  Hall Magnetic field value, tle4961

    private static final String TLI493dMagnetic_X_1 = "TLI493dMagnetic_X_1";     // < Magnetic 3D, tli493d
    private static final String TLI493dMagnetic_Y_1 = "TLI493dMagnetic_Y_1";     // < Magnetic 3D, tli493d
    private static final String TLI493dMagnetic_Z_1 = "TLI493dMagnetic_Z_1";     // < Magnetic 3D, tli493d

    public static JSONObject buildCommonJsonStructure() {
        JSONObject json = new JSONObject();
        json.put(DPS368Temperature_2, createValueMetrics());
        json.put(DPS368Temperature_1, createValueMetrics());
        json.put(TLI4971Current_2, createValueMetrics());
        json.put(TLI4971Current_3, createValueMetrics());
        json.put(DPS368Pressure_3, createValueMetrics());
        json.put(TLI4971Current_1, createValueMetrics());
        json.put(DPS368Temperature_3, createValueMetrics());
        json.put(DPS368Pressure_2, createValueMetrics());
        json.put(DPS368Pressure_1, createValueMetrics());
        json.put(DPS368Temperature_4, createValueMetrics());
        json.put(DPS368Pressure_4, createValueMetrics());
        json.put(DPS368Temperature_5, createValueMetrics());
        json.put(DPS368Pressure_5, createValueMetrics());
        json.put(TLI4964Hall_1, createValueMetrics());
        json.put(TLE49613kHall_1, createValueMetrics());
        json.put(TLI4966gDoubleHall_Speed_1, createValueMetrics());
        json.put(TLI4966gDoubleHall_Dir_1, createValueMetrics());
        json.put(TLE4913Hall_1, createValueMetrics());
        json.put(TLE49611kHall_1, createValueMetrics());
        json.put(TLI493dMagnetic_X_1, createValueMetrics());
        json.put(TLI493dMagnetic_Y_1, createValueMetrics());
        json.put(TLI493dMagnetic_Z_1, createValueMetrics());
        json.put(IM69dMic_1, new JSONObject().put("stat", createMetrics()).put("fft", createFreq2()).put("on", JSONObject.NULL));
        json.put(TLE4997LinearHall_1, new JSONObject().put("stat", createMetrics()).put("fft", createFreq2()).put("on", JSONObject.NULL));
        return json;
    }

    private static JSONArray createFreq2() {
        JSONArray array = new JSONArray();
        int i = 0;
        while (i < 128) {
            array.put(i, JSONObject.NULL);
            i++;
        }
        return array;
    }

    private static JSONObject createValueMetrics() {
        JSONObject jsonObject = new JSONObject()
                .put("max", JSONObject.NULL)
                .put("min", JSONObject.NULL)
                .put("mean", JSONObject.NULL)
                .put("rms", JSONObject.NULL)
                .put("std", JSONObject.NULL)
                .put("var", JSONObject.NULL);
        jsonObject.put("on", JSONObject.NULL);
        return jsonObject;
    }

    private static JSONArray createMetrics() {
        return new JSONArray()
                .put(0, JSONObject.NULL)
                .put(1, JSONObject.NULL)
                .put(2, JSONObject.NULL)
                .put(3, JSONObject.NULL)
                .put(4, JSONObject.NULL)
                .put(5, JSONObject.NULL);
    }

    static JSONObject changeFinalJson(JSONObject inputJson) {
        JSONObject finalJson = new JSONObject();

        fillMetrics(inputJson, finalJson, DPS368Temperature_2, "dps368_temp_2_");
        fillMetrics(inputJson, finalJson, DPS368Temperature_1, "dps368_temp_1_");
        fillMetrics(inputJson, finalJson, TLI4971Current_2, "tli4971_current_2_");
        fillMetrics(inputJson, finalJson, TLI4971Current_3, "tli4971_current_3_");
        fillMetrics(inputJson, finalJson, DPS368Pressure_3, "dps368_pressure_3_");
        fillMetrics(inputJson, finalJson, TLI4971Current_1, "tli4971_current_1_");
        fillMetrics(inputJson, finalJson, DPS368Temperature_3, "dps368_temp_3_");
        fillMetrics(inputJson, finalJson, DPS368Pressure_2, "dps368_pressure_2_");
        fillMetrics(inputJson, finalJson, DPS368Pressure_1, "dps368_pressure_1_");
        fillMetrics(inputJson, finalJson, IM69dMic_1, "im69d_mic_1_");
        fillMetrics(inputJson, finalJson, TLE4997LinearHall_1, "tle4997e_hall_");
        fillMetrics(inputJson, finalJson, DPS368Temperature_4, "dps368_temp_4_");
        fillMetrics(inputJson, finalJson, DPS368Pressure_4, " dps368_air_pressure_4_");
        fillMetrics(inputJson, finalJson, DPS368Temperature_5, "dps368_temp_5_");
        fillMetrics(inputJson, finalJson, DPS368Pressure_5, "dps368_pressure_5_");
        fillMetrics(inputJson, finalJson, TLI4964Hall_1, "tle4964_hall_1_");
        fillMetrics(inputJson, finalJson, TLE49613kHall_1, "tle4961k_hall_3_");
        fillMetrics(inputJson, finalJson, TLI4966gDoubleHall_Speed_1, "tli4966g_double_hall_speed_1_");
        fillMetrics(inputJson, finalJson, TLI4966gDoubleHall_Dir_1, "tli4966g_double_hall_dir_1_");
        fillMetrics(inputJson, finalJson, TLI493dMagnetic_X_1, "tli493d_magnetic_x_1_");
        fillMetrics(inputJson, finalJson, TLI493dMagnetic_Y_1, "tli493d_magnetic_y_1_");
        fillMetrics(inputJson, finalJson, TLI493dMagnetic_Z_1, "tli493d_magnetic_z_1_");
        fillMetrics(inputJson, finalJson, TLE49611kHall_1, "tle4961khall_1");
        fillMetrics(inputJson, finalJson, TLE4913Hall_1, "tle4913hall_1");

        fillFreqMetrics(inputJson, finalJson, IM69dMic_1, "im69d_mic_1_freq_");
        fillFreqMetrics(inputJson, finalJson, TLE4997LinearHall_1, "tle4997e_hall_freq_");
        return finalJson;
    }

    private static void fillFreqMetrics(JSONObject inputJson, JSONObject finalJson, String field, String newField) {
        JSONObject metrics = (JSONObject) inputJson.get(field);
        metrics.keySet().forEach(k -> {
            if (k.equalsIgnoreCase("fft")) {
                JSONArray fft = (JSONArray) metrics.get(k);
                for (int i = 0; i < 128; i++) {
                    finalJson.put(newField + i, fft.get(i));
                }
            }
        });
    }

    private static void fillMetrics(JSONObject inputJson, JSONObject finalJson, String field, String newField) {
        JSONObject metrics = (JSONObject) inputJson.get(field);
        metrics.keySet().forEach(k -> {
            if (k.equalsIgnoreCase("stat")) {
                JSONArray stat = (JSONArray) metrics.get(k);
                finalJson.put(newField + "max", stat.get(1));
                finalJson.put(newField + "min", stat.get(0));
                finalJson.put(newField + "mean", stat.get(2));
                finalJson.put(newField + "rms", stat.get(3));
                finalJson.put(newField + "std", stat.get(4));
                finalJson.put(newField + "var", stat.get(5));
            } else if (!k.equalsIgnoreCase("fft")) {
                finalJson.put(newField + k, metrics.get(k));
            }
        });
    }
}
