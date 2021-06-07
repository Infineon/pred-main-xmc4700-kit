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
 
 package com.infineon;

import software.amazon.awscdk.services.kinesisanalytics.CfnApplication;

import java.util.ArrayList;
import java.util.List;

class AnomalyDetectionAppUtils {

    static CfnApplication.InputSchemaProperty getInputSchema() {
        List<Object> columns = new ArrayList<>();
        columns.add(getColumn2("dps368_temp_1_on"));
        columns.add(getColumn2("dps368_temp_1_min"));
        columns.add(getColumn2("dps368_temp_1_max"));
        columns.add(getColumn2("dps368_temp_1_mean"));
        columns.add(getColumn2("dps368_temp_1_rms"));
        columns.add(getColumn2("dps368_temp_1_std"));
        columns.add(getColumn2("dps368_temp_1_var"));

        columns.add(getColumn2("dps368_temp_2_on"));
        columns.add(getColumn2("dps368_temp_2_min"));
        columns.add(getColumn2("dps368_temp_2_max"));
        columns.add(getColumn2("dps368_temp_2_mean"));
        columns.add(getColumn2("dps368_temp_2_rms"));
        columns.add(getColumn2("dps368_temp_2_std"));
        columns.add(getColumn2("dps368_temp_2_var"));

        columns.add(getColumn2("dps368_temp_3_on"));
        columns.add(getColumn2("dps368_temp_3_min"));
        columns.add(getColumn2("dps368_temp_3_max"));
        columns.add(getColumn2("dps368_temp_3_mean"));
        columns.add(getColumn2("dps368_temp_3_rms"));
        columns.add(getColumn2("dps368_temp_3_std"));
        columns.add(getColumn2("dps368_temp_3_var"));

        columns.add(getColumn2("dps368_pressure_1_on"));
        columns.add(getColumn2("dps368_pressure_1_min"));
        columns.add(getColumn2("dps368_pressure_1_max"));
        columns.add(getColumn2("dps368_pressure_1_mean"));
        columns.add(getColumn2("dps368_pressure_1_rms"));
        columns.add(getColumn2("dps368_pressure_1_std"));
        columns.add(getColumn2("dps368_pressure_1_var"));

        columns.add(getColumn2("dps368_pressure_2_on"));
        columns.add(getColumn2("dps368_pressure_2_min"));
        columns.add(getColumn2("dps368_pressure_2_max"));
        columns.add(getColumn2("dps368_pressure_2_mean"));
        columns.add(getColumn2("dps368_pressure_2_rms"));
        columns.add(getColumn2("dps368_pressure_2_std"));
        columns.add(getColumn2("dps368_pressure_2_var"));

        columns.add(getColumn2("dps368_pressure_3_on"));
        columns.add(getColumn2("dps368_pressure_3_min"));
        columns.add(getColumn2("dps368_pressure_3_max"));
        columns.add(getColumn2("dps368_pressure_3_mean"));
        columns.add(getColumn2("dps368_pressure_3_rms"));
        columns.add(getColumn2("dps368_pressure_3_std"));
        columns.add(getColumn2("dps368_pressure_3_var"));

        columns.add(getColumn2("tli4971_current_1_on"));
        columns.add(getColumn2("tli4971_current_1_min"));
        columns.add(getColumn2("tli4971_current_1_max"));
        columns.add(getColumn2("tli4971_current_1_mean"));
        columns.add(getColumn2("tli4971_current_1_rms"));
        columns.add(getColumn2("tli4971_current_1_std"));
        columns.add(getColumn2("tli4971_current_1_var"));

        columns.add(getColumn2("tli4971_current_2_on"));
        columns.add(getColumn2("tli4971_current_2_min"));
        columns.add(getColumn2("tli4971_current_2_max"));
        columns.add(getColumn2("tli4971_current_2_mean"));
        columns.add(getColumn2("tli4971_current_2_rms"));
        columns.add(getColumn2("tli4971_current_2_std"));
        columns.add(getColumn2("tli4971_current_2_var"));

        columns.add(getColumn2("tli4971_current_3_on"));
        columns.add(getColumn2("tli4971_current_3_min"));
        columns.add(getColumn2("tli4971_current_3_max"));
        columns.add(getColumn2("tli4971_current_3_mean"));
        columns.add(getColumn2("tli4971_current_3_rms"));
        columns.add(getColumn2("tli4971_current_3_std"));
        columns.add(getColumn2("tli4971_current_3_var"));

        columns.add(getColumn2("tle4997e_hall_on"));
        columns.add(getColumn2("tle4997e_hall_min"));
        columns.add(getColumn2("tle4997e_hall_max"));
        columns.add(getColumn2("tle4997e_hall_mean"));
        columns.add(getColumn2("tle4997e_hall_rms"));
        columns.add(getColumn2("tle4997e_hall_std"));
        columns.add(getColumn2("tle4997e_hall_var"));
        addSpectrumDataColumns(columns, "tle4997e_hall_freq_");

        columns.add(getColumn2("im69d_mic_1_on"));
        columns.add(getColumn2("im69d_mic_1_min"));
        columns.add(getColumn2("im69d_mic_1_max"));
        columns.add(getColumn2("im69d_mic_1_mean"));
        columns.add(getColumn2("im69d_mic_1_rms"));
        columns.add(getColumn2("im69d_mic_1_std"));
        columns.add(getColumn2("im69d_mic_1_var"));
        addSpectrumDataColumns(columns, "im69d_mic_1_freq_");

        columns.add(getColumn2("dps368_temp_4_on"));
        columns.add(getColumn2("dps368_temp_4_min"));
        columns.add(getColumn2("dps368_temp_4_max"));
        columns.add(getColumn2("dps368_temp_4_mean"));
        columns.add(getColumn2("dps368_temp_4_rms"));
        columns.add(getColumn2("dps368_temp_4_std"));
        columns.add(getColumn2("dps368_temp_4_var"));

        columns.add(getColumn2("dps368_air_pressure_4_on"));
        columns.add(getColumn2("dps368_air_pressure_4_min"));
        columns.add(getColumn2("dps368_air_pressure_4_max"));
        columns.add(getColumn2("dps368_air_pressure_4_mean"));
        columns.add(getColumn2("dps368_air_pressure_4_rms"));
        columns.add(getColumn2("dps368_air_pressure_4_std"));
        columns.add(getColumn2("dps368_air_pressure_4_var"));

        columns.add(getColumn2("tli4906hall_1_on"));
        columns.add(getColumn2("tli4906hall_1_min"));
        columns.add(getColumn2("tli4906hall_1_max"));
        columns.add(getColumn2("tli4906hall_1_mean"));
        columns.add(getColumn2("tli4906hall_1_rms"));
        columns.add(getColumn2("tli4906hall_1_std"));
        columns.add(getColumn2("tli4906hall_1_var"));

        columns.add(getColumn2("tle4913hall_1_on"));
        columns.add(getColumn2("tle4913hall_1_min"));
        columns.add(getColumn2("tle4913hall_1_max"));
        columns.add(getColumn2("tle4913hall_1_mean"));
        columns.add(getColumn2("tle4913hall_1_rms"));
        columns.add(getColumn2("tle4913hall_1_std"));
        columns.add(getColumn2("tle4913hall_1_var"));

        columns.add(getColumn2("dps368_temp_5_on"));
        columns.add(getColumn2("dps368_temp_5_min"));
        columns.add(getColumn2("dps368_temp_5_max"));
        columns.add(getColumn2("dps368_temp_5_mean"));
        columns.add(getColumn2("dps368_temp_5_rms"));
        columns.add(getColumn2("dps368_temp_5_std"));
        columns.add(getColumn2("dps368_temp_5_var"));

        columns.add(getColumn2("dps368_pressure_5_on"));
        columns.add(getColumn2("dps368_pressure_5_min"));
        columns.add(getColumn2("dps368_pressure_5_max"));
        columns.add(getColumn2("dps368_pressure_5_mean"));
        columns.add(getColumn2("dps368_pressure_5_rms"));
        columns.add(getColumn2("dps368_pressure_5_std"));
        columns.add(getColumn2("dps368_pressure_5_var"));

        columns.add(getColumn2("tle4946k_hall_1_on"));
        columns.add(getColumn2("tle4946k_hall_1_min"));
        columns.add(getColumn2("tle4946k_hall_1_max"));
        columns.add(getColumn2("tle4946k_hall_1_mean"));
        columns.add(getColumn2("tle4946k_hall_1_rms"));
        columns.add(getColumn2("tle4946k_hall_1_std"));
        columns.add(getColumn2("tle4946k_hall_1_var"));

        columns.add(getColumn2("tle4946k_hall_2_on"));
        columns.add(getColumn2("tle4946k_hall_2_min"));
        columns.add(getColumn2("tle4946k_hall_2_max"));
        columns.add(getColumn2("tle4946k_hall_2_mean"));
        columns.add(getColumn2("tle4946k_hall_2_rms"));
        columns.add(getColumn2("tle4946k_hall_2_std"));
        columns.add(getColumn2("tle4946k_hall_2_var"));

        columns.add(getColumn2("tli4966g_double_hall_speed_1_on"));
        columns.add(getColumn2("tli4966g_double_hall_speed_1_min"));
        columns.add(getColumn2("tli4966g_double_hall_speed_1_max"));
        columns.add(getColumn2("tli4966g_double_hall_speed_1_mean"));
        columns.add(getColumn2("tli4966g_double_hall_speed_1_rms"));
        columns.add(getColumn2("tli4966g_double_hall_speed_1_std"));
        columns.add(getColumn2("tli4966g_double_hall_speed_1_var"));

        columns.add(getColumn2("tli4966g_double_hall_dir_1_on"));
        columns.add(getColumn2("tli4966g_double_hall_dir_1_min"));
        columns.add(getColumn2("tli4966g_double_hall_dir_1_max"));
        columns.add(getColumn2("tli4966g_double_hall_dir_1_mean"));
        columns.add(getColumn2("tli4966g_double_hall_dir_1_rms"));
        columns.add(getColumn2("tli4966g_double_hall_dir_1_std"));
        columns.add(getColumn2("tli4966g_double_hall_dir_1_var"));

        columns.add(getColumn2("tli493d_magnetic_x_1_on"));
        columns.add(getColumn2("tli493d_magnetic_x_1_min"));
        columns.add(getColumn2("tli493d_magnetic_x_1_max"));
        columns.add(getColumn2("tli493d_magnetic_x_1_mean"));
        columns.add(getColumn2("tli493d_magnetic_x_1_rms"));
        columns.add(getColumn2("tli493d_magnetic_x_1_std"));
        columns.add(getColumn2("tli493d_magnetic_x_1_var"));

        columns.add(getColumn2("tli493d_magnetic_y_1_on"));
        columns.add(getColumn2("tli493d_magnetic_y_1_min"));
        columns.add(getColumn2("tli493d_magnetic_y_1_max"));
        columns.add(getColumn2("tli493d_magnetic_y_1_mean"));
        columns.add(getColumn2("tli493d_magnetic_y_1_rms"));
        columns.add(getColumn2("tli493d_magnetic_y_1_std"));
        columns.add(getColumn2("tli493d_magnetic_y_1_var"));

        columns.add(getColumn2("tli493d_magnetic_z_1_on"));
        columns.add(getColumn2("tli493d_magnetic_z_1_min"));
        columns.add(getColumn2("tli493d_magnetic_z_1_max"));
        columns.add(getColumn2("tli493d_magnetic_z_1_mean"));
        columns.add(getColumn2("tli493d_magnetic_z_1_rms"));
        columns.add(getColumn2("tli493d_magnetic_z_1_std"));
        columns.add(getColumn2("tli493d_magnetic_z_1_var"));

        columns.add(getColumn2("tli493d_magnetic_x_2_on"));
        columns.add(getColumn2("tli493d_magnetic_x_2_min"));
        columns.add(getColumn2("tli493d_magnetic_x_2_max"));
        columns.add(getColumn2("tli493d_magnetic_x_2_mean"));
        columns.add(getColumn2("tli493d_magnetic_x_2_rms"));
        columns.add(getColumn2("tli493d_magnetic_x_2_std"));
        columns.add(getColumn2("tli493d_magnetic_x_2_var"));

        columns.add(getColumn2("tli493d_magnetic_y_2_on"));
        columns.add(getColumn2("tli493d_magnetic_y_2_min"));
        columns.add(getColumn2("tli493d_magnetic_y_2_max"));
        columns.add(getColumn2("tli493d_magnetic_y_2_mean"));
        columns.add(getColumn2("tli493d_magnetic_y_2_rms"));
        columns.add(getColumn2("tli493d_magnetic_y_2_std"));
        columns.add(getColumn2("tli493d_magnetic_y_2_var"));

        columns.add(getColumn2("tli493d_magnetic_z_2_on"));
        columns.add(getColumn2("tli493d_magnetic_z_2_min"));
        columns.add(getColumn2("tli493d_magnetic_z_2_max"));
        columns.add(getColumn2("tli493d_magnetic_z_2_mean"));
        columns.add(getColumn2("tli493d_magnetic_z_2_rms"));
        columns.add(getColumn2("tli493d_magnetic_z_2_std"));
        columns.add(getColumn2("tli493d_magnetic_z_2_var"));

        return CfnApplication.InputSchemaProperty.builder()
                .recordColumns(columns)
                .recordFormat(CfnApplication.RecordFormatProperty.builder().recordFormatType("JSON").build())
                .build();
    }

    private static void addSpectrumDataColumns(List<Object> columns, String name) {
        for (int i = 0; i < 128; i++) {
            columns.add(getColumn(name + i, name + i));
        }
    }

    private static CfnApplication.RecordColumnProperty getColumn(String name, String mapping) {
        return CfnApplication.RecordColumnProperty.builder()
                .name(name)
                .mapping("$." + mapping)
                .sqlType("DOUBLE").build();
    }

    private static CfnApplication.RecordColumnProperty getColumn2(String name) {
        return CfnApplication.RecordColumnProperty.builder()
                .name(name)
                .mapping("$." + name)
                .sqlType("DOUBLE").build();
    }
}
