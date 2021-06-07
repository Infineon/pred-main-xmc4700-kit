<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="ADC_MEASUREMENT_ADV" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2" description="Measurement of analog signals using VADC via Queue and Scan request sources with advanced features.&#xA; Background request source is not supported." mode="NOTSHARABLE" version="4.0.20" minDaveVersion="4.0.1" instanceLabel="ADC_MEASUREMENT_ADV_2" appLabel="" containingProxySignal="true">
  <properties provideInit="true"/>
  <virtualSignals name="sr_interrupt_signal" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_nvic_src" hwSignal="signal_in" hwResource="//@hwResources.395"/>
  <virtualSignals name="iclass_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel" hwSignal="ch_class_sel" hwResource="//@hwResources.394"/>
  <virtualSignals name="queue_iclass_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_classselect_in" hwSignal="queue_class_sel" hwResource="//@hwResources.394" required="false"/>
  <virtualSignals name="class_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_classselect_out" hwSignal="class_sel" hwResource="//@hwResources.392"/>
  <virtualSignals name="queue_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel" hwSignal="select" hwResource="//@hwResources.392"/>
  <virtualSignals name="group_selection" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_config" hwSignal="req" hwResource="//@hwResources.392"/>
  <virtualSignals name="queue_to_global" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_global" hwSignal="global_signal" hwResource="//@hwResources.392"/>
  <virtualSignals name="trigger_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_greqtr0sel" hwSignal="greqtr0sel" hwResource="//@hwResources.392" visible="true"/>
  <virtualSignals name="gating_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_greqgt0sel" hwSignal="greqgt0sel" hwResource="//@hwResources.392" visible="true"/>
  <virtualSignals name="event_queue_source" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_sourceevent" hwSignal="sev" hwResource="//@hwResources.392" visible="true"/>
  <virtualSignals name="scan_iclass_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_classselect_in" hwSignal="scan_class_sel" hwResource="//@hwResources.394"/>
  <virtualSignals name="class_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_classselect_out" hwSignal="class_sel" hwResource="//@hwResources.393"/>
  <virtualSignals name="scan_select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_to_channel" hwSignal="select" hwResource="//@hwResources.393"/>
  <virtualSignals name="group_selection" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_to_config" hwSignal="req" hwResource="//@hwResources.393"/>
  <virtualSignals name="scan_to_global" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_to_global" hwSignal="global_signal" hwResource="//@hwResources.393"/>
  <virtualSignals name="trigger_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_greqtr1sel" hwSignal="greqtr1sel" hwResource="//@hwResources.393" visible="true"/>
  <virtualSignals name="gating_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_greqgt1sel" hwSignal="greqgt1sel" hwResource="//@hwResources.393" visible="true"/>
  <virtualSignals name="event_scan_source" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_sourceevent" hwSignal="sev" hwResource="//@hwResources.393" visible="true"/>
  <virtualSignals name="Channel_AN2_Slot1_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_0" hwSignal="pin" hwResource="//@hwResources.20"/>
  <virtualSignals name="Channel_A_sync_slaveA_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_1" hwSignal="pin" hwResource="//@hwResources.21"/>
  <virtualSignals name="Channel_A_sync_slaveB_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_2" hwSignal="pin" hwResource="//@hwResources.22"/>
  <virtualSignals name="Channel_A_sync_slaveC_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_3" hwSignal="pin" hwResource="//@hwResources.23"/>
  <virtualSignals name="Channel_B_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_4" hwSignal="pin" hwResource="//@hwResources.24"/>
  <virtualSignals name="Channel_B_sync_slaveA_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_5" hwSignal="pin" hwResource="//@hwResources.25"/>
  <virtualSignals name="Channel_B_sync_slaveB_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_6" hwSignal="pin" hwResource="//@hwResources.26"/>
  <virtualSignals name="Channel_B_sync_slaveC_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_7" hwSignal="pin" hwResource="//@hwResources.27"/>
  <virtualSignals name="Channel_C_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_8" hwSignal="pin" hwResource="//@hwResources.28"/>
  <virtualSignals name="Channel_C_sync_slaveA_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_9" hwSignal="pin" hwResource="//@hwResources.29"/>
  <virtualSignals name="Channel_C_sync_slaveB_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_10" hwSignal="pin" hwResource="//@hwResources.30"/>
  <virtualSignals name="Channel_C_sync_slaveC_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_11" hwSignal="pin" hwResource="//@hwResources.31"/>
  <virtualSignals name="Channel_D_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_12" hwSignal="pin" hwResource="//@hwResources.32"/>
  <virtualSignals name="Channel_D_sync_slaveA_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_13" hwSignal="pin" hwResource="//@hwResources.33"/>
  <virtualSignals name="Channel_D_sync_slaveB_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_14" hwSignal="pin" hwResource="//@hwResources.34"/>
  <virtualSignals name="Channel_D_sync_slaveC_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_15" hwSignal="pin" hwResource="//@hwResources.35"/>
  <virtualSignals name="Channel_E_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_16" hwSignal="pin" hwResource="//@hwResources.36"/>
  <virtualSignals name="Channel_F_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_17" hwSignal="pin" hwResource="//@hwResources.37"/>
  <virtualSignals name="Channel_G_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_18" hwSignal="pin" hwResource="//@hwResources.38"/>
  <virtualSignals name="Channel_H_pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_19" hwSignal="pin" hwResource="//@hwResources.39"/>
  <virtualSignals name="Channel_AN2_Slot1_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_0" hwSignal="pad" hwResource="//@hwResources.0"/>
  <virtualSignals name="Channel_A_sync_slaveA_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_1" hwSignal="pad" hwResource="//@hwResources.1"/>
  <virtualSignals name="Channel_A_sync_slaveB_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_2" hwSignal="pad" hwResource="//@hwResources.2"/>
  <virtualSignals name="Channel_A_sync_slaveC_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_3" hwSignal="pad" hwResource="//@hwResources.3"/>
  <virtualSignals name="Channel_B_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_4" hwSignal="pad" hwResource="//@hwResources.4"/>
  <virtualSignals name="Channel_B_sync_slaveA_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_5" hwSignal="pad" hwResource="//@hwResources.5"/>
  <virtualSignals name="Channel_B_sync_slaveB_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_6" hwSignal="pad" hwResource="//@hwResources.6"/>
  <virtualSignals name="Channel_B_sync_slaveC_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_7" hwSignal="pad" hwResource="//@hwResources.7"/>
  <virtualSignals name="Channel_C_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_8" hwSignal="pad" hwResource="//@hwResources.8"/>
  <virtualSignals name="Channel_C_sync_slaveA_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_9" hwSignal="pad" hwResource="//@hwResources.9"/>
  <virtualSignals name="Channel_C_sync_slaveB_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_10" hwSignal="pad" hwResource="//@hwResources.10"/>
  <virtualSignals name="Channel_C_sync_slaveC_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_11" hwSignal="pad" hwResource="//@hwResources.11"/>
  <virtualSignals name="Channel_D_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_12" hwSignal="pad" hwResource="//@hwResources.12"/>
  <virtualSignals name="Channel_D_sync_slaveA_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_13" hwSignal="pad" hwResource="//@hwResources.13"/>
  <virtualSignals name="Channel_D_sync_slaveB_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_14" hwSignal="pad" hwResource="//@hwResources.14"/>
  <virtualSignals name="Channel_D_sync_slaveC_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_15" hwSignal="pad" hwResource="//@hwResources.15"/>
  <virtualSignals name="Channel_E_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_16" hwSignal="pad" hwResource="//@hwResources.16"/>
  <virtualSignals name="Channel_F_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_17" hwSignal="pad" hwResource="//@hwResources.17"/>
  <virtualSignals name="Channel_G_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_18" hwSignal="pad" hwResource="//@hwResources.18"/>
  <virtualSignals name="Channel_H_pad" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_19" hwSignal="pad" hwResource="//@hwResources.19"/>
  <virtualSignals name="Channel_AN2_Slot1_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_0" hwSignal="gch" hwResource="//@hwResources.40" visible="true"/>
  <virtualSignals name="Channel_A_sync_slaveA_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_1" hwSignal="gch" hwResource="//@hwResources.41"/>
  <virtualSignals name="Channel_A_sync_slaveB_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_2" hwSignal="gch" hwResource="//@hwResources.42"/>
  <virtualSignals name="Channel_A_sync_slaveC_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_3" hwSignal="gch" hwResource="//@hwResources.43"/>
  <virtualSignals name="Channel_B_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_4" hwSignal="gch" hwResource="//@hwResources.44" visible="true"/>
  <virtualSignals name="Channel_B_sync_slaveA_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_5" hwSignal="gch" hwResource="//@hwResources.45"/>
  <virtualSignals name="Channel_B_sync_slaveB_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_6" hwSignal="gch" hwResource="//@hwResources.46"/>
  <virtualSignals name="Channel_B_sync_slaveC_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_7" hwSignal="gch" hwResource="//@hwResources.47"/>
  <virtualSignals name="Channel_C_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_8" hwSignal="gch" hwResource="//@hwResources.48" visible="true"/>
  <virtualSignals name="Channel_C_sync_slaveA_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_9" hwSignal="gch" hwResource="//@hwResources.49"/>
  <virtualSignals name="Channel_C_sync_slaveB_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_10" hwSignal="gch" hwResource="//@hwResources.50"/>
  <virtualSignals name="Channel_C_sync_slaveC_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_11" hwSignal="gch" hwResource="//@hwResources.51"/>
  <virtualSignals name="Channel_D_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_12" hwSignal="gch" hwResource="//@hwResources.52" visible="true"/>
  <virtualSignals name="Channel_D_sync_slaveA_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_13" hwSignal="gch" hwResource="//@hwResources.53"/>
  <virtualSignals name="Channel_D_sync_slaveB_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_14" hwSignal="gch" hwResource="//@hwResources.54"/>
  <virtualSignals name="Channel_D_sync_slaveC_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_15" hwSignal="gch" hwResource="//@hwResources.55"/>
  <virtualSignals name="Channel_E_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_16" hwSignal="gch" hwResource="//@hwResources.56" visible="true"/>
  <virtualSignals name="Channel_F_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_17" hwSignal="gch" hwResource="//@hwResources.57" visible="true"/>
  <virtualSignals name="Channel_G_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_18" hwSignal="gch" hwResource="//@hwResources.58" visible="true"/>
  <virtualSignals name="Channel_H_input" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_19" hwSignal="gch" hwResource="//@hwResources.59" visible="true"/>
  <virtualSignals name="Channel_AN2_Slot1_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_0" hwSignal="select" hwResource="//@hwResources.40"/>
  <virtualSignals name="Channel_A_sync_slaveA_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_1" hwSignal="select" hwResource="//@hwResources.41"/>
  <virtualSignals name="Channel_A_sync_slaveB_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_2" hwSignal="select" hwResource="//@hwResources.42"/>
  <virtualSignals name="Channel_A_sync_slaveC_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_3" hwSignal="select" hwResource="//@hwResources.43"/>
  <virtualSignals name="Channel_B_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_4" hwSignal="select" hwResource="//@hwResources.44"/>
  <virtualSignals name="Channel_B_sync_slaveA_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_5" hwSignal="select" hwResource="//@hwResources.45"/>
  <virtualSignals name="Channel_B_sync_slaveB_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_6" hwSignal="select" hwResource="//@hwResources.46"/>
  <virtualSignals name="Channel_B_sync_slaveC_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_7" hwSignal="select" hwResource="//@hwResources.47"/>
  <virtualSignals name="Channel_C_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_8" hwSignal="select" hwResource="//@hwResources.48"/>
  <virtualSignals name="Channel_C_sync_slaveA_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_9" hwSignal="select" hwResource="//@hwResources.49"/>
  <virtualSignals name="Channel_C_sync_slaveB_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_10" hwSignal="select" hwResource="//@hwResources.50"/>
  <virtualSignals name="Channel_C_sync_slaveC_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_11" hwSignal="select" hwResource="//@hwResources.51"/>
  <virtualSignals name="Channel_D_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_12" hwSignal="select" hwResource="//@hwResources.52"/>
  <virtualSignals name="Channel_D_sync_slaveA_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_13" hwSignal="select" hwResource="//@hwResources.53"/>
  <virtualSignals name="Channel_D_sync_slaveB_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_14" hwSignal="select" hwResource="//@hwResources.54"/>
  <virtualSignals name="Channel_D_sync_slaveC_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_15" hwSignal="select" hwResource="//@hwResources.55"/>
  <virtualSignals name="Channel_E_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_16" hwSignal="select" hwResource="//@hwResources.56"/>
  <virtualSignals name="Channel_F_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_17" hwSignal="select" hwResource="//@hwResources.57"/>
  <virtualSignals name="Channel_G_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_18" hwSignal="select" hwResource="//@hwResources.58"/>
  <virtualSignals name="Channel_H_sel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_19" hwSignal="select" hwResource="//@hwResources.59"/>
  <virtualSignals name="Channel_AN2_Slot1_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_0" hwSignal="iclass_sel" hwResource="//@hwResources.40" visible="true"/>
  <virtualSignals name="Channel_B_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_1" hwSignal="iclass_sel" hwResource="//@hwResources.44" visible="true"/>
  <virtualSignals name="Channel_C_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_2" hwSignal="iclass_sel" hwResource="//@hwResources.48" visible="true"/>
  <virtualSignals name="Channel_D_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_3" hwSignal="iclass_sel" hwResource="//@hwResources.52" visible="true"/>
  <virtualSignals name="Channel_E_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_4" hwSignal="iclass_sel" hwResource="//@hwResources.56" visible="true"/>
  <virtualSignals name="Channel_F_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_5" hwSignal="iclass_sel" hwResource="//@hwResources.57" visible="true"/>
  <virtualSignals name="Channel_G_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_6" hwSignal="iclass_sel" hwResource="//@hwResources.58" visible="true"/>
  <virtualSignals name="Channel_H_iclass" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_7" hwSignal="iclass_sel" hwResource="//@hwResources.59" visible="true"/>
  <virtualSignals name="master select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_0" hwSignal="select" hwResource="//@hwResources.397"/>
  <virtualSignals name="slaveA select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_1" hwSignal="select" hwResource="//@hwResources.398"/>
  <virtualSignals name="slaveB select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_2" hwSignal="select" hwResource="//@hwResources.399"/>
  <virtualSignals name="slaveC select" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_3" hwSignal="select" hwResource="//@hwResources.400"/>
  <virtualSignals name="Channel_AN2_Slot1_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_0" hwSignal="res_sel" hwResource="//@hwResources.60"/>
  <virtualSignals name="vs_Channel_A_sync_slaveA_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_1" hwSignal="res_sel" hwResource="//@hwResources.84"/>
  <virtualSignals name="vs_Channel_A_sync_slaveB_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_2" hwSignal="res_sel" hwResource="//@hwResources.100"/>
  <virtualSignals name="vs_Channel_A_sync_slaveC_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_3" hwSignal="res_sel" hwResource="//@hwResources.116"/>
  <virtualSignals name="Channel_B_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_4" hwSignal="res_sel" hwResource="//@hwResources.61"/>
  <virtualSignals name="vs_Channel_B_sync_slaveA_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_5" hwSignal="res_sel" hwResource="//@hwResources.148"/>
  <virtualSignals name="vs_Channel_B_sync_slaveB_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_6" hwSignal="res_sel" hwResource="//@hwResources.164"/>
  <virtualSignals name="vs_Channel_B_sync_slaveC_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_7" hwSignal="res_sel" hwResource="//@hwResources.180"/>
  <virtualSignals name="Channel_C_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_8" hwSignal="res_sel" hwResource="//@hwResources.62"/>
  <virtualSignals name="vs_Channel_C_sync_slaveA_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_9" hwSignal="res_sel" hwResource="//@hwResources.212"/>
  <virtualSignals name="vs_Channel_C_sync_slaveB_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_10" hwSignal="res_sel" hwResource="//@hwResources.228"/>
  <virtualSignals name="vs_Channel_C_sync_slaveC_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_11" hwSignal="res_sel" hwResource="//@hwResources.244"/>
  <virtualSignals name="Channel_D_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_12" hwSignal="res_sel" hwResource="//@hwResources.63"/>
  <virtualSignals name="vs_Channel_D_sync_slaveA_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_13" hwSignal="res_sel" hwResource="//@hwResources.276"/>
  <virtualSignals name="vs_Channel_D_sync_slaveB_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_14" hwSignal="res_sel" hwResource="//@hwResources.292"/>
  <virtualSignals name="vs_Channel_D_sync_slaveC_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_15" hwSignal="res_sel" hwResource="//@hwResources.308"/>
  <virtualSignals name="Channel_E_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_16" hwSignal="res_sel" hwResource="//@hwResources.64"/>
  <virtualSignals name="Channel_F_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_17" hwSignal="res_sel" hwResource="//@hwResources.65"/>
  <virtualSignals name="Channel_G_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_18" hwSignal="res_sel" hwResource="//@hwResources.66"/>
  <virtualSignals name="Channel_H_result_to_channel" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_19" hwSignal="res_sel" hwResource="//@hwResources.67"/>
  <virtualSignals name="Channel_AN2_Slot1_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_0" hwSignal="res_sel" hwResource="//@hwResources.40"/>
  <virtualSignals name="Channel_A_sync_slaveA_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_1" hwSignal="res_sel" hwResource="//@hwResources.41"/>
  <virtualSignals name="Channel_A_sync_slaveB_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_2" hwSignal="res_sel" hwResource="//@hwResources.42"/>
  <virtualSignals name="Channel_A_sync_slaveC_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_3" hwSignal="res_sel" hwResource="//@hwResources.43"/>
  <virtualSignals name="Channel_B_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_4" hwSignal="res_sel" hwResource="//@hwResources.44"/>
  <virtualSignals name="Channel_B_sync_slaveA_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_5" hwSignal="res_sel" hwResource="//@hwResources.45"/>
  <virtualSignals name="Channel_B_sync_slaveB_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_6" hwSignal="res_sel" hwResource="//@hwResources.46"/>
  <virtualSignals name="Channel_B_sync_slaveC_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_7" hwSignal="res_sel" hwResource="//@hwResources.47"/>
  <virtualSignals name="Channel_C_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_8" hwSignal="res_sel" hwResource="//@hwResources.48"/>
  <virtualSignals name="Channel_C_sync_slaveA_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_9" hwSignal="res_sel" hwResource="//@hwResources.49"/>
  <virtualSignals name="Channel_C_sync_slaveB_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_10" hwSignal="res_sel" hwResource="//@hwResources.50"/>
  <virtualSignals name="Channel_C_sync_slaveC_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_11" hwSignal="res_sel" hwResource="//@hwResources.51"/>
  <virtualSignals name="Channel_D_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_12" hwSignal="res_sel" hwResource="//@hwResources.52"/>
  <virtualSignals name="Channel_D_sync_slaveA_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_13" hwSignal="res_sel" hwResource="//@hwResources.53"/>
  <virtualSignals name="Channel_D_sync_slaveB_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_14" hwSignal="res_sel" hwResource="//@hwResources.54"/>
  <virtualSignals name="Channel_D_sync_slaveC_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_15" hwSignal="res_sel" hwResource="//@hwResources.55"/>
  <virtualSignals name="Channel_E_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_16" hwSignal="res_sel" hwResource="//@hwResources.56"/>
  <virtualSignals name="Channel_F_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_17" hwSignal="res_sel" hwResource="//@hwResources.57"/>
  <virtualSignals name="Channel_G_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_18" hwSignal="res_sel" hwResource="//@hwResources.58"/>
  <virtualSignals name="Channel_H_channel_to_result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_19" hwSignal="res_sel" hwResource="//@hwResources.59"/>
  <virtualSignals name="event_res_Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_0" hwSignal="rev" hwResource="//@hwResources.60" visible="true"/>
  <virtualSignals name="event_res_Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_1" hwSignal="rev" hwResource="//@hwResources.61" visible="true"/>
  <virtualSignals name="event_res_Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_2" hwSignal="rev" hwResource="//@hwResources.62" visible="true"/>
  <virtualSignals name="event_res_Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_3" hwSignal="rev" hwResource="//@hwResources.63" visible="true"/>
  <virtualSignals name="event_res_Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_4" hwSignal="rev" hwResource="//@hwResources.64" visible="true"/>
  <virtualSignals name="event_res_Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_5" hwSignal="rev" hwResource="//@hwResources.65" visible="true"/>
  <virtualSignals name="event_res_Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_6" hwSignal="rev" hwResource="//@hwResources.66" visible="true"/>
  <virtualSignals name="event_res_Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_evt_7" hwSignal="rev" hwResource="//@hwResources.67" visible="true"/>
  <virtualSignals name="event_ch_Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_0" hwSignal="cev" hwResource="//@hwResources.40" visible="true"/>
  <virtualSignals name="event_ch_Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_1" hwSignal="cev" hwResource="//@hwResources.44" visible="true"/>
  <virtualSignals name="event_ch_Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_2" hwSignal="cev" hwResource="//@hwResources.48" visible="true"/>
  <virtualSignals name="event_ch_Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_3" hwSignal="cev" hwResource="//@hwResources.52" visible="true"/>
  <virtualSignals name="event_ch_Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_4" hwSignal="cev" hwResource="//@hwResources.56" visible="true"/>
  <virtualSignals name="event_ch_Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_5" hwSignal="cev" hwResource="//@hwResources.57" visible="true"/>
  <virtualSignals name="event_ch_Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_6" hwSignal="cev" hwResource="//@hwResources.58" visible="true"/>
  <virtualSignals name="event_ch_Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_evt_7" hwSignal="cev" hwResource="//@hwResources.59" visible="true"/>
  <virtualSignals name="bound_fl_Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_0" hwSignal="gbflout" hwResource="//@hwResources.60" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_1" hwSignal="gbflout" hwResource="//@hwResources.84" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_2" hwSignal="gbflout" hwResource="//@hwResources.100" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_3" hwSignal="gbflout" hwResource="//@hwResources.116" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_4" hwSignal="gbflout" hwResource="//@hwResources.61" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_5" hwSignal="gbflout" hwResource="//@hwResources.148" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_6" hwSignal="gbflout" hwResource="//@hwResources.164" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_7" hwSignal="gbflout" hwResource="//@hwResources.180" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_8" hwSignal="gbflout" hwResource="//@hwResources.62" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_9" hwSignal="gbflout" hwResource="//@hwResources.212" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_10" hwSignal="gbflout" hwResource="//@hwResources.228" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_11" hwSignal="gbflout" hwResource="//@hwResources.244" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_12" hwSignal="gbflout" hwResource="//@hwResources.63" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_13" hwSignal="gbflout" hwResource="//@hwResources.276" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_14" hwSignal="gbflout" hwResource="//@hwResources.292" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_15" hwSignal="gbflout" hwResource="//@hwResources.308" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_16" hwSignal="gbflout" hwResource="//@hwResources.64" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_17" hwSignal="gbflout" hwResource="//@hwResources.65" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_18" hwSignal="gbflout" hwResource="//@hwResources.66" required="false" visible="true"/>
  <virtualSignals name="bound_fl_Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_bfl_out_result_19" hwSignal="gbflout" hwResource="//@hwResources.67" required="false" visible="true"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/appres_scan" requiredAppName="ADC_SCAN" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/appres_queue" requiredAppName="ADC_QUEUE" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#0" requiredAppName="ANALOG_IO" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../ANALOG_IO/v4_0_12/ANALOG_IO_2.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#1" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#2" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#3" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#4" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#5" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#6" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#7" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#8" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#9" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#10" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#11" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#12" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#13" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#14" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#15" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#16" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#17" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#18" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_appres_analog_io#19" requiredAppName="ANALOG_IO" required="false" requiringMode="SHARABLE"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/appres_global_adc" requiredAppName="GLOBAL_ADC" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../GLOBAL_ADC/v4_0_22/GLOBAL_ADC_0.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/appres_cpu" requiredAppName="CPU_CTRL_XMC4" required="false" requiringMode="SHARABLE"/>
  <hwResources name="Channel_AN2_Slot1 Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#0" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_A_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#1" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_A_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#2" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_A_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#3" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_B Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#4" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_B_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#5" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_B_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#6" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_B_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#7" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_C Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#8" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_C_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#9" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_C_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#10" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_C_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#11" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_D Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#12" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_D_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#13" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_D_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#14" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_D_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#15" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_E Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#16" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_F Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#17" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_G Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#18" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_H Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channel_pin#19" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="Channel_AN2_Slot1 Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#0" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_A_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#1" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_A_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#2" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_A_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#3" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_B Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#4" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_B_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#5" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_B_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#6" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_B_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#7" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_C Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#8" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_C_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#9" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_C_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#10" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_C_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#11" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_D Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#12" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_D_sync_slaveA Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#13" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_D_sync_slaveB Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#14" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_D_sync_slaveC Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#15" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_E Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#16" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_F Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#17" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_G Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#18" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_H Pin" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_pin_pad#19" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#0" resourceGroupUri="resources/48.0.0/peripheral/vadc/0/group/0/ch/2" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv0">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/vadc/vadc_0.dd#//@provided.25"/>
    <solverVarMap index="6">
      <value variableName="sv0" solverValue="2"/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv0" solverValue="2"/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#1" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv1">
    <solverVarMap index="6">
      <value variableName="sv1" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv1" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#2" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv2">
    <solverVarMap index="6">
      <value variableName="sv2" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv2" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#3" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv3">
    <solverVarMap index="6">
      <value variableName="sv3" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv3" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#4" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv4">
    <solverVarMap index="6">
      <value variableName="sv4" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv4" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#5" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv5">
    <solverVarMap index="6">
      <value variableName="sv5" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv5" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#6" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv6">
    <solverVarMap index="6">
      <value variableName="sv6" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv6" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#7" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv7">
    <solverVarMap index="6">
      <value variableName="sv7" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv7" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#8" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv8">
    <solverVarMap index="6">
      <value variableName="sv8" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv8" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#9" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv9">
    <solverVarMap index="6">
      <value variableName="sv9" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv9" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#10" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv10">
    <solverVarMap index="6">
      <value variableName="sv10" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv10" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#11" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv11">
    <solverVarMap index="6">
      <value variableName="sv11" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv11" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#12" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv12">
    <solverVarMap index="6">
      <value variableName="sv12" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv12" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#13" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv13">
    <solverVarMap index="6">
      <value variableName="sv13" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv13" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#14" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv14">
    <solverVarMap index="6">
      <value variableName="sv14" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv14" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#15" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv15">
    <solverVarMap index="6">
      <value variableName="sv15" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv15" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#16" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv16">
    <solverVarMap index="6">
      <value variableName="sv16" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv16" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#17" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv17">
    <solverVarMap index="6">
      <value variableName="sv17" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv17" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#18" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv18">
    <solverVarMap index="6">
      <value variableName="sv18" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv18" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_channels#19" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/*/ch/sv19">
    <solverVarMap index="6">
      <value variableName="sv19" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv19" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1 Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#0" resourceGroupUri="resources/48.0.0/peripheral/vadc/0/group/0/result_filter/15" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv21/sv22">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/vadc/vadc_0.dd#//@provided.22"/>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue="2"/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv21" solverValue="result_adv"/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv22" solverValue="0"/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue="2"/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv21" solverValue="result_adv"/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv22" solverValue="0"/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#1" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv24/sv25">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv24" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv25" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv24" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv25" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#2" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv27/sv28">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv27" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv28" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv27" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv28" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#3" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv30/sv31">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv30" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv31" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv30" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv31" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#4" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv33/sv34">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv33" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv34" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv33" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv34" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#5" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv36/sv37">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv36" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv37" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv36" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv37" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#6" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv39/sv40">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv39" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv40" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv39" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv40" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg#7" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv42/sv43">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv42" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv43" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv42" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv43" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1 Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#0" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv21/sv44">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv21" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv44" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv21" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv44" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#1" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv45/sv46">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv45" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv46" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv45" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv46" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#2" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv47/sv48">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv47" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv48" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv47" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv48" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#3" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv49/sv50">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv49" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv50" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv49" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv50" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#4" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv51/sv52">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv51" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv52" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv51" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv52" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#5" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv53/sv54">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv53" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv54" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv53" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv54" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#6" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv55/sv56">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv55" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv56" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv55" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv56" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#7" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv57/sv58">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv57" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv58" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv57" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv58" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#8" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv59/sv60">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv59" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv60" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv59" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv60" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#9" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv61/sv62">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv61" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv62" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv61" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv62" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#10" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv63/sv64">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv63" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv64" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv63" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv64" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#11" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv65/sv66">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv65" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv66" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv65" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv66" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#12" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv67/sv68">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv67" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv68" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv67" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv68" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#13" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv69/sv70">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv69" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv70" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv69" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv70" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#14" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv71/sv72">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv71" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv72" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv71" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv72" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_AN2_Slot1" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#15" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv20/sv73/sv74">
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv73" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv74" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv20" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv73" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv74" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#16" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv76/sv77">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv76" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv77" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv76" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv77" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#17" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv78/sv79">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv78" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv79" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv78" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv79" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#18" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv80/sv81">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv80" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv81" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv80" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv81" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#19" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv82/sv83">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv82" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv83" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv82" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv83" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#20" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv84/sv85">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv84" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv85" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv84" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv85" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#21" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv86/sv87">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv86" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv87" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv86" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv87" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#22" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv88/sv89">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv88" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv89" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv88" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv89" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#23" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv90/sv91">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv90" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv91" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv90" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv91" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#24" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv92/sv93">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv92" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv93" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv92" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv93" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#25" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv94/sv95">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv94" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv95" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv94" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv95" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#26" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv96/sv97">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv96" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv97" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv96" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv97" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#27" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv98/sv99">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv98" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv99" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv98" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv99" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#28" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv100/sv101">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv100" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv101" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv100" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv101" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#29" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv102/sv103">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv102" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv103" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv102" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv103" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#30" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv104/sv105">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv104" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv105" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv104" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv105" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#31" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv75/sv106/sv107">
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv106" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv107" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv75" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv106" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv107" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#32" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv109/sv110">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv109" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv110" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv109" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv110" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#33" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv111/sv112">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv111" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv112" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv111" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv112" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#34" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv113/sv114">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv113" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv114" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv113" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv114" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#35" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv115/sv116">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv115" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv116" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv115" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv116" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#36" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv117/sv118">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv117" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv118" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv117" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv118" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#37" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv119/sv120">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv119" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv120" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv119" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv120" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#38" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv121/sv122">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv121" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv122" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv121" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv122" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#39" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv123/sv124">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv123" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv124" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv123" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv124" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#40" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv125/sv126">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv125" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv126" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv125" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv126" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#41" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv127/sv128">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv127" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv128" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv127" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv128" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#42" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv129/sv130">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv129" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv130" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv129" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv130" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#43" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv131/sv132">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv131" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv132" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv131" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv132" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#44" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv133/sv134">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv133" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv134" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv133" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv134" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#45" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv135/sv136">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv135" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv136" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv135" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv136" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#46" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv137/sv138">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv137" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv138" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv137" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv138" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#47" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv108/sv139/sv140">
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv139" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv140" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv108" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv139" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv140" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#48" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv142/sv143">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv142" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv143" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv142" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv143" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#49" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv144/sv145">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv144" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv145" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv144" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv145" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#50" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv146/sv147">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv146" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv147" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv146" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv147" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#51" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv148/sv149">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv148" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv149" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv148" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv149" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#52" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv150/sv151">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv150" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv151" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv150" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv151" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#53" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv152/sv153">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv152" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv153" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv152" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv153" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#54" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv154/sv155">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv154" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv155" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv154" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv155" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#55" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv156/sv157">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv156" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv157" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv156" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv157" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#56" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv158/sv159">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv158" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv159" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv158" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv159" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#57" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv160/sv161">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv160" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv161" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv160" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv161" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#58" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv162/sv163">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv162" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv163" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv162" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv163" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#59" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv164/sv165">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv164" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv165" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv164" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv165" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#60" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv166/sv167">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv166" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv167" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv166" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv167" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#61" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv168/sv169">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv168" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv169" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv168" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv169" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#62" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv170/sv171">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv170" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv171" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv170" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv171" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_A_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#63" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv141/sv172/sv173">
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv172" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv173" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv141" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv172" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv173" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#64" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv24/sv174">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv24" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv174" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv24" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv174" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#65" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv175/sv176">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv175" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv176" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv175" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv176" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#66" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv177/sv178">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv177" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv178" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv177" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv178" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#67" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv179/sv180">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv179" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv180" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv179" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv180" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#68" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv181/sv182">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv181" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv182" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv181" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv182" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#69" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv183/sv184">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv183" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv184" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv183" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv184" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#70" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv185/sv186">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv185" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv186" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv185" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv186" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#71" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv187/sv188">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv187" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv188" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv187" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv188" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#72" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv189/sv190">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv189" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv190" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv189" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv190" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#73" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv191/sv192">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv191" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv192" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv191" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv192" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#74" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv193/sv194">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv193" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv194" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv193" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv194" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#75" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv195/sv196">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv195" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv196" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv195" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv196" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#76" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv197/sv198">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv197" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv198" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv197" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv198" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#77" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv199/sv200">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv199" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv200" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv199" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv200" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#78" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv201/sv202">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv201" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv202" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv201" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv202" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#79" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv23/sv203/sv204">
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv203" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv204" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv23" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv203" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv204" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#80" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv206/sv207">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv206" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv207" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv206" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv207" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#81" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv208/sv209">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv208" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv209" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv208" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv209" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#82" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv210/sv211">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv210" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv211" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv210" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv211" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#83" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv212/sv213">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv212" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv213" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv212" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv213" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#84" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv214/sv215">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv214" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv215" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv214" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv215" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#85" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv216/sv217">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv216" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv217" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv216" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv217" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#86" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv218/sv219">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv218" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv219" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv218" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv219" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#87" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv220/sv221">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv220" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv221" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv220" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv221" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#88" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv222/sv223">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv222" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv223" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv222" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv223" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#89" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv224/sv225">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv224" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv225" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv224" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv225" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#90" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv226/sv227">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv226" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv227" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv226" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv227" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#91" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv228/sv229">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv228" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv229" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv228" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv229" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#92" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv230/sv231">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv230" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv231" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv230" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv231" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#93" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv232/sv233">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv232" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv233" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv232" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv233" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#94" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv234/sv235">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv234" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv235" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv234" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv235" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#95" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv205/sv236/sv237">
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv236" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv237" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv205" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv236" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv237" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#96" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv239/sv240">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv239" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv240" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv239" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv240" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#97" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv241/sv242">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv241" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv242" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv241" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv242" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#98" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv243/sv244">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv243" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv244" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv243" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv244" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#99" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv245/sv246">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv245" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv246" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv245" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv246" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#100" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv247/sv248">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv247" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv248" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv247" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv248" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#101" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv249/sv250">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv249" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv250" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv249" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv250" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#102" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv251/sv252">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv251" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv252" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv251" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv252" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#103" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv253/sv254">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv253" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv254" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv253" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv254" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#104" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv255/sv256">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv255" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv256" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv255" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv256" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#105" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv257/sv258">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv257" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv258" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv257" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv258" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#106" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv259/sv260">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv259" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv260" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv259" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv260" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#107" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv261/sv262">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv261" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv262" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv261" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv262" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#108" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv263/sv264">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv263" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv264" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv263" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv264" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#109" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv265/sv266">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv265" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv266" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv265" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv266" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#110" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv267/sv268">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv267" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv268" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv267" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv268" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#111" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv238/sv269/sv270">
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv269" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv270" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv238" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv269" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv270" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#112" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv272/sv273">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv272" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv273" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv272" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv273" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#113" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv274/sv275">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv274" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv275" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv274" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv275" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#114" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv276/sv277">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv276" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv277" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv276" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv277" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#115" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv278/sv279">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv278" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv279" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv278" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv279" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#116" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv280/sv281">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv280" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv281" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv280" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv281" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#117" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv282/sv283">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv282" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv283" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv282" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv283" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#118" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv284/sv285">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv284" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv285" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv284" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv285" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#119" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv286/sv287">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv286" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv287" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv286" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv287" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#120" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv288/sv289">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv288" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv289" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv288" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv289" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#121" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv290/sv291">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv290" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv291" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv290" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv291" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#122" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv292/sv293">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv292" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv293" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv292" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv293" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#123" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv294/sv295">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv294" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv295" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv294" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv295" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#124" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv296/sv297">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv296" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv297" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv296" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv297" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#125" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv298/sv299">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv298" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv299" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv298" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv299" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#126" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv300/sv301">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv300" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv301" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv300" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv301" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_B_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#127" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv271/sv302/sv303">
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv302" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv303" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv271" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv302" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv303" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#128" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv27/sv304">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv27" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv304" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv27" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv304" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#129" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv305/sv306">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv305" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv306" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv305" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv306" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#130" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv307/sv308">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv307" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv308" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv307" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv308" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#131" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv309/sv310">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv309" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv310" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv309" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv310" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#132" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv311/sv312">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv311" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv312" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv311" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv312" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#133" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv313/sv314">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv313" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv314" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv313" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv314" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#134" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv315/sv316">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv315" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv316" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv315" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv316" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#135" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv317/sv318">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv317" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv318" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv317" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv318" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#136" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv319/sv320">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv319" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv320" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv319" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv320" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#137" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv321/sv322">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv321" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv322" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv321" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv322" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#138" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv323/sv324">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv323" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv324" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv323" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv324" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#139" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv325/sv326">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv325" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv326" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv325" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv326" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#140" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv327/sv328">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv327" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv328" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv327" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv328" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#141" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv329/sv330">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv329" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv330" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv329" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv330" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#142" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv331/sv332">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv331" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv332" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv331" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv332" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#143" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv26/sv333/sv334">
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv333" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv334" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv26" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv333" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv334" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#144" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv336/sv337">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv336" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv337" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv336" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv337" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#145" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv338/sv339">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv338" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv339" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv338" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv339" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#146" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv340/sv341">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv340" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv341" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv340" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv341" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#147" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv342/sv343">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv342" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv343" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv342" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv343" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#148" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv344/sv345">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv344" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv345" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv344" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv345" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#149" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv346/sv347">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv346" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv347" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv346" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv347" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#150" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv348/sv349">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv348" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv349" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv348" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv349" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#151" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv350/sv351">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv350" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv351" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv350" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv351" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#152" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv352/sv353">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv352" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv353" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv352" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv353" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#153" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv354/sv355">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv354" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv355" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv354" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv355" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#154" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv356/sv357">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv356" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv357" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv356" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv357" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#155" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv358/sv359">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv358" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv359" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv358" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv359" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#156" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv360/sv361">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv360" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv361" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv360" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv361" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#157" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv362/sv363">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv362" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv363" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv362" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv363" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#158" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv364/sv365">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv364" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv365" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv364" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv365" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#159" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv335/sv366/sv367">
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv366" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv367" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv335" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv366" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv367" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#160" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv369/sv370">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv369" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv370" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv369" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv370" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#161" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv371/sv372">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv371" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv372" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv371" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv372" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#162" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv373/sv374">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv373" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv374" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv373" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv374" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#163" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv375/sv376">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv375" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv376" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv375" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv376" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#164" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv377/sv378">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv377" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv378" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv377" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv378" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#165" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv379/sv380">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv379" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv380" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv379" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv380" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#166" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv381/sv382">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv381" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv382" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv381" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv382" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#167" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv383/sv384">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv383" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv384" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv383" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv384" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#168" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv385/sv386">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv385" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv386" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv385" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv386" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#169" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv387/sv388">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv387" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv388" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv387" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv388" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#170" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv389/sv390">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv389" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv390" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv389" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv390" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#171" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv391/sv392">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv391" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv392" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv391" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv392" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#172" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv393/sv394">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv393" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv394" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv393" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv394" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#173" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv395/sv396">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv395" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv396" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv395" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv396" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#174" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv397/sv398">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv397" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv398" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv397" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv398" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#175" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv368/sv399/sv400">
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv399" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv400" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv368" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv399" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv400" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#176" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv402/sv403">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv402" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv403" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv402" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv403" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#177" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv404/sv405">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv404" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv405" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv404" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv405" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#178" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv406/sv407">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv406" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv407" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv406" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv407" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#179" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv408/sv409">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv408" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv409" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv408" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv409" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#180" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv410/sv411">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv410" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv411" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv410" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv411" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#181" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv412/sv413">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv412" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv413" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv412" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv413" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#182" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv414/sv415">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv414" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv415" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv414" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv415" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#183" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv416/sv417">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv416" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv417" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv416" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv417" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#184" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv418/sv419">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv418" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv419" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv418" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv419" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#185" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv420/sv421">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv420" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv421" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv420" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv421" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#186" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv422/sv423">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv422" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv423" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv422" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv423" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#187" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv424/sv425">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv424" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv425" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv424" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv425" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#188" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv426/sv427">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv426" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv427" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv426" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv427" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#189" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv428/sv429">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv428" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv429" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv428" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv429" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#190" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv430/sv431">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv430" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv431" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv430" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv431" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_C_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#191" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv401/sv432/sv433">
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv432" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv433" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv401" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv432" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv433" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#192" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv30/sv434">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv30" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv434" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv30" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv434" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#193" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv435/sv436">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv435" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv436" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv435" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv436" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#194" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv437/sv438">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv437" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv438" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv437" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv438" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#195" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv439/sv440">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv439" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv440" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv439" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv440" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#196" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv441/sv442">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv441" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv442" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv441" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv442" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#197" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv443/sv444">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv443" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv444" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv443" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv444" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#198" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv445/sv446">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv445" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv446" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv445" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv446" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#199" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv447/sv448">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv447" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv448" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv447" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv448" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#200" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv449/sv450">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv449" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv450" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv449" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv450" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#201" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv451/sv452">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv451" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv452" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv451" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv452" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#202" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv453/sv454">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv453" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv454" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv453" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv454" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#203" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv455/sv456">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv455" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv456" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv455" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv456" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#204" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv457/sv458">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv457" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv458" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv457" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv458" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#205" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv459/sv460">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv459" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv460" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv459" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv460" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#206" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv461/sv462">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv461" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv462" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv461" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv462" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#207" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv29/sv463/sv464">
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv463" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv464" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv29" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv463" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv464" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#208" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv466/sv467">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv466" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv467" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv466" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv467" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#209" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv468/sv469">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv468" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv469" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv468" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv469" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#210" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv470/sv471">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv470" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv471" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv470" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv471" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#211" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv472/sv473">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv472" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv473" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv472" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv473" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#212" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv474/sv475">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv474" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv475" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv474" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv475" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#213" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv476/sv477">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv476" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv477" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv476" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv477" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#214" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv478/sv479">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv478" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv479" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv478" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv479" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#215" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv480/sv481">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv480" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv481" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv480" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv481" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#216" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv482/sv483">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv482" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv483" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv482" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv483" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#217" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv484/sv485">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv484" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv485" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv484" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv485" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#218" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv486/sv487">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv486" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv487" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv486" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv487" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#219" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv488/sv489">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv488" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv489" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv488" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv489" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#220" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv490/sv491">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv490" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv491" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv490" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv491" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#221" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv492/sv493">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv492" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv493" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv492" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv493" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#222" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv494/sv495">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv494" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv495" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv494" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv495" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#223" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv465/sv496/sv497">
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv496" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv497" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv465" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv496" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv497" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#224" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv499/sv500">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv499" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv500" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv499" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv500" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#225" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv501/sv502">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv501" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv502" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv501" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv502" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#226" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv503/sv504">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv503" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv504" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv503" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv504" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#227" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv505/sv506">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv505" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv506" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv505" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv506" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#228" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv507/sv508">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv507" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv508" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv507" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv508" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#229" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv509/sv510">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv509" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv510" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv509" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv510" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#230" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv511/sv512">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv511" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv512" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv511" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv512" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#231" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv513/sv514">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv513" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv514" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv513" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv514" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#232" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv515/sv516">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv515" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv516" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv515" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv516" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#233" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv517/sv518">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv517" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv518" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv517" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv518" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#234" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv519/sv520">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv519" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv520" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv519" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv520" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#235" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv521/sv522">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv521" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv522" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv521" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv522" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#236" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv523/sv524">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv523" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv524" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv523" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv524" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#237" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv525/sv526">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv525" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv526" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv525" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv526" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#238" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv527/sv528">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv527" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv528" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv527" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv528" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#239" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv498/sv529/sv530">
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv529" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv530" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv498" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv529" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv530" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#240" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv532/sv533">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv532" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv533" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv532" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv533" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#241" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv534/sv535">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv534" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv535" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv534" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv535" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#242" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv536/sv537">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv536" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv537" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv536" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv537" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#243" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv538/sv539">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv538" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv539" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv538" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv539" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#244" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv540/sv541">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv540" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv541" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv540" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv541" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#245" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv542/sv543">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv542" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv543" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv542" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv543" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#246" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv544/sv545">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv544" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv545" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv544" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv545" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#247" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv546/sv547">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv546" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv547" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv546" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv547" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#248" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv548/sv549">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv548" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv549" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv548" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv549" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#249" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv550/sv551">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv550" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv551" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv550" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv551" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#250" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv552/sv553">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv552" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv553" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv552" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv553" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#251" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv554/sv555">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv554" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv555" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv554" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv555" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#252" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv556/sv557">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv556" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv557" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv556" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv557" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#253" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv558/sv559">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv558" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv559" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv558" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv559" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#254" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv560/sv561">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv560" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv561" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv560" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv561" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_D_sync_slaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#255" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv531/sv562/sv563">
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv562" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv563" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv531" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv562" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv563" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#256" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv33/sv564">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv33" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv564" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv33" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv564" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#257" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv565/sv566">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv565" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv566" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv565" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv566" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#258" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv567/sv568">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv567" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv568" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv567" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv568" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#259" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv569/sv570">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv569" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv570" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv569" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv570" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#260" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv571/sv572">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv571" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv572" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv571" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv572" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#261" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv573/sv574">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv573" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv574" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv573" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv574" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#262" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv575/sv576">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv575" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv576" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv575" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv576" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#263" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv577/sv578">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv577" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv578" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv577" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv578" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#264" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv579/sv580">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv579" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv580" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv579" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv580" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#265" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv581/sv582">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv581" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv582" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv581" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv582" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#266" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv583/sv584">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv583" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv584" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv583" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv584" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#267" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv585/sv586">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv585" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv586" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv585" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv586" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#268" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv587/sv588">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv587" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv588" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv587" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv588" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#269" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv589/sv590">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv589" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv590" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv589" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv590" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#270" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv591/sv592">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv591" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv592" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv591" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv592" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_E" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#271" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv32/sv593/sv594">
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv593" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv594" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv32" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv593" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv594" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#272" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv36/sv595">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv36" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv595" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv36" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv595" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#273" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv596/sv597">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv596" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv597" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv596" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv597" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#274" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv598/sv599">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv598" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv599" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv598" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv599" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#275" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv600/sv601">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv600" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv601" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv600" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv601" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#276" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv602/sv603">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv602" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv603" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv602" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv603" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#277" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv604/sv605">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv604" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv605" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv604" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv605" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#278" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv606/sv607">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv606" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv607" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv606" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv607" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#279" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv608/sv609">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv608" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv609" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv608" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv609" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#280" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv610/sv611">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv610" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv611" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv610" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv611" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#281" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv612/sv613">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv612" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv613" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv612" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv613" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#282" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv614/sv615">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv614" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv615" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv614" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv615" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#283" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv616/sv617">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv616" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv617" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv616" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv617" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#284" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv618/sv619">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv618" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv619" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv618" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv619" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#285" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv620/sv621">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv620" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv621" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv620" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv621" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#286" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv622/sv623">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv622" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv623" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv622" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv623" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_F" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#287" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv35/sv624/sv625">
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv624" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv625" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv35" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv624" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv625" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#288" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv39/sv626">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv39" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv626" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv39" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv626" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#289" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv627/sv628">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv627" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv628" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv627" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv628" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#290" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv629/sv630">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv629" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv630" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv629" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv630" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#291" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv631/sv632">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv631" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv632" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv631" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv632" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#292" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv633/sv634">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv633" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv634" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv633" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv634" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#293" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv635/sv636">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv635" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv636" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv635" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv636" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#294" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv637/sv638">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv637" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv638" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv637" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv638" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#295" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv639/sv640">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv639" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv640" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv639" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv640" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#296" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv641/sv642">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv641" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv642" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv641" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv642" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#297" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv643/sv644">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv643" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv644" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv643" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv644" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#298" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv645/sv646">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv645" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv646" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv645" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv646" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#299" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv647/sv648">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv647" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv648" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv647" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv648" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#300" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv649/sv650">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv649" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv650" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv649" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv650" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#301" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv651/sv652">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv651" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv652" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv651" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv652" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#302" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv653/sv654">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv653" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv654" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv653" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv654" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_G" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#303" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv38/sv655/sv656">
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv655" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv656" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv38" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv655" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv656" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H Result" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#304" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv42/sv657">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv42" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv657" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv42" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv657" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#305" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv658/sv659">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv658" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv659" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv658" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv659" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#306" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv660/sv661">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv660" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv661" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv660" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv661" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#307" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv662/sv663">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv662" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv663" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv662" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv663" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#308" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv664/sv665">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv664" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv665" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv664" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv665" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#309" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv666/sv667">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv666" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv667" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv666" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv667" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#310" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv668/sv669">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv668" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv669" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv668" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv669" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#311" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv670/sv671">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv670" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv671" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv670" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv671" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#312" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv672/sv673">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv672" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv673" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv672" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv673" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#313" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv674/sv675">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv674" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv675" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv674" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv675" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#314" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv676/sv677">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv676" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv677" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv676" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv677" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#315" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv678/sv679">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv678" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv679" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv678" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv679" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#316" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv680/sv681">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv680" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv681" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv680" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv681" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#317" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv682/sv683">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv682" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv683" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv682" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv683" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#318" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv684/sv685">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv684" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv685" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv684" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv685" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Channel_H" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_fifo_sync#319" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv41/sv686/sv687">
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv686" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv687" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv41" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv686" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv687" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Subtraction Result Register " URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_subtraction_mode#0" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv688/result_adv/0">
    <solverVarMap index="4">
      <value variableName="sv688" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv688" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Subtraction Result Register Sync SlaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_subtraction_mode#1" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv689/result_adv/0">
    <solverVarMap index="4">
      <value variableName="sv689" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv689" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Subtraction Result Register Sync SlaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_subtraction_mode#2" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv690/result_adv/0">
    <solverVarMap index="4">
      <value variableName="sv690" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv690" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Subtraction Result Register Sync SlaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_hwres_adc_adv_measurement_result_reg_subtraction_mode#3" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv691/result_adv/0">
    <solverVarMap index="4">
      <value variableName="sv691" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv691" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Queue" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/hwres_vadc_queue" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/*/group/*/queue"/>
  <hwResources name="Scan" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/hwres_vadc_scan" resourceGroupUri="peripheral/vadc/*/group/*/scan" mResGrpUri="peripheral/vadc/*/group/*/scan">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/vadc/vadc_0.dd#//@provided.31"/>
  </hwResources>
  <hwResources name="Input Class" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/hwres_vadc_inputclass" resourceGroupUri="peripheral/vadc/*/group/*/class/*" mResGrpUri="peripheral/vadc/*/group/*/class/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/vadc/vadc_0.dd#//@provided.37"/>
  </hwResources>
  <hwResources name="Source Event Interrupt" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/hwres_nvicnode_srcevt" resourceGroupUri="" required="false" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*"/>
  <hwResources name="Sync Slave Input Class" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/hwres_adc_adv_measurement_sync_slave_iclass" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/0/class/1"/>
  <hwResources name="Sync Master" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_adc_adv_measurement_sync_resource#0" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv688/sync">
    <solverVarMap index="4">
      <value variableName="sv688" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv688" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Sync SlaveA" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_adc_adv_measurement_sync_resource#1" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv689/sync">
    <solverVarMap index="4">
      <value variableName="sv689" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv689" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Sync SlaveB" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_adc_adv_measurement_sync_resource#2" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv690/sync">
    <solverVarMap index="4">
      <value variableName="sv690" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv690" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="Sync SlaveC" URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/rarray_adc_adv_measurement_sync_resource#3" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv691/sync">
    <solverVarMap index="4">
      <value variableName="sv691" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv691" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_0" systemDefined="true" sourceSignal="Channel_A_pad" targetSignal="Channel_A_pin" srcVirtualSignal="//@virtualSignals.38" targetVirtualSignal="//@virtualSignals.18"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_0" systemDefined="true" sourceSignal="Channel_A_pin" targetSignal="Channel_A_pad" srcVirtualSignal="//@virtualSignals.18" targetVirtualSignal="//@virtualSignals.38"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_0" systemDefined="true" sourceSignal="Channel_A_pad" targetSignal="Channel_A_input" srcVirtualSignal="//@virtualSignals.38" targetVirtualSignal="//@virtualSignals.58"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_0" systemDefined="true" targetSignal="Channel_A_sel" required="false" targetVirtualSignal="//@virtualSignals.78" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_0" systemDefined="true" targetSignal="Channel_A_sel" required="false" targetVirtualSignal="//@virtualSignals.78" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_0" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_A_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.78"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_0" systemDefined="true" targetSignal="Channel_A_iclass" required="false" targetVirtualSignal="//@virtualSignals.98" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_0" systemDefined="true" targetSignal="Channel_A_iclass" required="false" targetVirtualSignal="//@virtualSignals.98" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_0" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_A_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.98"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_0" systemDefined="true" sourceSignal="pin" targetSignal="Channel_A_input" targetVirtualSignal="//@virtualSignals.58" proxySrcVirtualSignalUri="http://resources/4.0.12/app/ANALOG_IO/2/vs_analog_io_pad_pin" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../ANALOG_IO/v4_0_12/ANALOG_IO_2.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../ANALOG_IO/v4_0_12/ANALOG_IO_2.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_0" systemDefined="true" sourceSignal="Channel_A_channel_to_result" targetSignal="Channel_A_result_to_channel" srcVirtualSignal="//@virtualSignals.130" targetVirtualSignal="//@virtualSignals.110"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_1" systemDefined="true" sourceSignal="Channel_A_sync_slaveA_pad" targetSignal="Channel_A_sync_slaveA_pin" srcVirtualSignal="//@virtualSignals.39" targetVirtualSignal="//@virtualSignals.19"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_1" systemDefined="true" sourceSignal="Channel_A_sync_slaveA_pin" targetSignal="Channel_A_sync_slaveA_pad" srcVirtualSignal="//@virtualSignals.19" targetVirtualSignal="//@virtualSignals.39"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_1" systemDefined="true" sourceSignal="Channel_A_sync_slaveA_pad" targetSignal="Channel_A_sync_slaveA_input" srcVirtualSignal="//@virtualSignals.39" targetVirtualSignal="//@virtualSignals.59"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_1" systemDefined="true" targetSignal="Channel_A_sync_slaveA_input" required="false" targetVirtualSignal="//@virtualSignals.59" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_1" systemDefined="true" sourceSignal="Channel_A_sync_slaveA_channel_to_result" targetSignal="vs_Channel_A_sync_slaveA_result_to_channel" srcVirtualSignal="//@virtualSignals.131" targetVirtualSignal="//@virtualSignals.111"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_2" systemDefined="true" sourceSignal="Channel_A_sync_slaveB_pad" targetSignal="Channel_A_sync_slaveB_pin" srcVirtualSignal="//@virtualSignals.40" targetVirtualSignal="//@virtualSignals.20"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_2" systemDefined="true" sourceSignal="Channel_A_sync_slaveB_pin" targetSignal="Channel_A_sync_slaveB_pad" srcVirtualSignal="//@virtualSignals.20" targetVirtualSignal="//@virtualSignals.40"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_2" systemDefined="true" sourceSignal="Channel_A_sync_slaveB_pad" targetSignal="Channel_A_sync_slaveB_input" srcVirtualSignal="//@virtualSignals.40" targetVirtualSignal="//@virtualSignals.60"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_2" systemDefined="true" targetSignal="Channel_A_sync_slaveB_input" required="false" targetVirtualSignal="//@virtualSignals.60" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_2" systemDefined="true" sourceSignal="Channel_A_sync_slaveB_channel_to_result" targetSignal="vs_Channel_A_sync_slaveB_result_to_channel" srcVirtualSignal="//@virtualSignals.132" targetVirtualSignal="//@virtualSignals.112"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_3" systemDefined="true" sourceSignal="Channel_A_sync_slaveC_pad" targetSignal="Channel_A_sync_slaveC_pin" srcVirtualSignal="//@virtualSignals.41" targetVirtualSignal="//@virtualSignals.21"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_3" systemDefined="true" sourceSignal="Channel_A_sync_slaveC_pin" targetSignal="Channel_A_sync_slaveC_pad" srcVirtualSignal="//@virtualSignals.21" targetVirtualSignal="//@virtualSignals.41"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_3" systemDefined="true" sourceSignal="Channel_A_sync_slaveC_pad" targetSignal="Channel_A_sync_slaveC_input" srcVirtualSignal="//@virtualSignals.41" targetVirtualSignal="//@virtualSignals.61"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_3" systemDefined="true" targetSignal="Channel_A_sync_slaveC_input" required="false" targetVirtualSignal="//@virtualSignals.61" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_3" systemDefined="true" sourceSignal="Channel_A_sync_slaveC_channel_to_result" targetSignal="vs_Channel_A_sync_slaveC_result_to_channel" srcVirtualSignal="//@virtualSignals.133" targetVirtualSignal="//@virtualSignals.113"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_4/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_4" systemDefined="true" sourceSignal="Channel_B_pad" targetSignal="Channel_B_pin" srcVirtualSignal="//@virtualSignals.42" targetVirtualSignal="//@virtualSignals.22"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_4/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_4" systemDefined="true" sourceSignal="Channel_B_pin" targetSignal="Channel_B_pad" srcVirtualSignal="//@virtualSignals.22" targetVirtualSignal="//@virtualSignals.42"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_4/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_4" systemDefined="true" sourceSignal="Channel_B_pad" targetSignal="Channel_B_input" srcVirtualSignal="//@virtualSignals.42" targetVirtualSignal="//@virtualSignals.62"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_4" systemDefined="true" targetSignal="Channel_B_sel" required="false" targetVirtualSignal="//@virtualSignals.82" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_4" systemDefined="true" targetSignal="Channel_B_sel" required="false" targetVirtualSignal="//@virtualSignals.82" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_4" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_B_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.82"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_1" systemDefined="true" targetSignal="Channel_B_iclass" required="false" targetVirtualSignal="//@virtualSignals.99" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_1" systemDefined="true" targetSignal="Channel_B_iclass" required="false" targetVirtualSignal="//@virtualSignals.99" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_1" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_B_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.99"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_4/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_4" systemDefined="true" targetSignal="Channel_B_input" required="false" targetVirtualSignal="//@virtualSignals.62" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_4/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_4" systemDefined="true" sourceSignal="Channel_B_channel_to_result" targetSignal="Channel_B_result_to_channel" srcVirtualSignal="//@virtualSignals.134" targetVirtualSignal="//@virtualSignals.114"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_5/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_5" systemDefined="true" sourceSignal="Channel_B_sync_slaveA_pad" targetSignal="Channel_B_sync_slaveA_pin" srcVirtualSignal="//@virtualSignals.43" targetVirtualSignal="//@virtualSignals.23"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_5/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_5" systemDefined="true" sourceSignal="Channel_B_sync_slaveA_pin" targetSignal="Channel_B_sync_slaveA_pad" srcVirtualSignal="//@virtualSignals.23" targetVirtualSignal="//@virtualSignals.43"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_5/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_5" systemDefined="true" sourceSignal="Channel_B_sync_slaveA_pad" targetSignal="Channel_B_sync_slaveA_input" srcVirtualSignal="//@virtualSignals.43" targetVirtualSignal="//@virtualSignals.63"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_5/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_5" systemDefined="true" targetSignal="Channel_B_sync_slaveA_input" required="false" targetVirtualSignal="//@virtualSignals.63" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_5/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_5" systemDefined="true" sourceSignal="Channel_B_sync_slaveA_channel_to_result" targetSignal="vs_Channel_B_sync_slaveA_result_to_channel" srcVirtualSignal="//@virtualSignals.135" targetVirtualSignal="//@virtualSignals.115"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_6/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_6" systemDefined="true" sourceSignal="Channel_B_sync_slaveB_pad" targetSignal="Channel_B_sync_slaveB_pin" srcVirtualSignal="//@virtualSignals.44" targetVirtualSignal="//@virtualSignals.24"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_6/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_6" systemDefined="true" sourceSignal="Channel_B_sync_slaveB_pin" targetSignal="Channel_B_sync_slaveB_pad" srcVirtualSignal="//@virtualSignals.24" targetVirtualSignal="//@virtualSignals.44"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_6/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_6" systemDefined="true" sourceSignal="Channel_B_sync_slaveB_pad" targetSignal="Channel_B_sync_slaveB_input" srcVirtualSignal="//@virtualSignals.44" targetVirtualSignal="//@virtualSignals.64"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_6/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_6" systemDefined="true" targetSignal="Channel_B_sync_slaveB_input" required="false" targetVirtualSignal="//@virtualSignals.64" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_6/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_6" systemDefined="true" sourceSignal="Channel_B_sync_slaveB_channel_to_result" targetSignal="vs_Channel_B_sync_slaveB_result_to_channel" srcVirtualSignal="//@virtualSignals.136" targetVirtualSignal="//@virtualSignals.116"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_7/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_7" systemDefined="true" sourceSignal="Channel_B_sync_slaveC_pad" targetSignal="Channel_B_sync_slaveC_pin" srcVirtualSignal="//@virtualSignals.45" targetVirtualSignal="//@virtualSignals.25"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_7/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_7" systemDefined="true" sourceSignal="Channel_B_sync_slaveC_pin" targetSignal="Channel_B_sync_slaveC_pad" srcVirtualSignal="//@virtualSignals.25" targetVirtualSignal="//@virtualSignals.45"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_7/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_7" systemDefined="true" sourceSignal="Channel_B_sync_slaveC_pad" targetSignal="Channel_B_sync_slaveC_input" srcVirtualSignal="//@virtualSignals.45" targetVirtualSignal="//@virtualSignals.65"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_7/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_7" systemDefined="true" targetSignal="Channel_B_sync_slaveC_input" required="false" targetVirtualSignal="//@virtualSignals.65" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_7/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_7" systemDefined="true" sourceSignal="Channel_B_sync_slaveC_channel_to_result" targetSignal="vs_Channel_B_sync_slaveC_result_to_channel" srcVirtualSignal="//@virtualSignals.137" targetVirtualSignal="//@virtualSignals.117"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_8/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_8" systemDefined="true" sourceSignal="Channel_C_pad" targetSignal="Channel_C_pin" srcVirtualSignal="//@virtualSignals.46" targetVirtualSignal="//@virtualSignals.26"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_8/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_8" systemDefined="true" sourceSignal="Channel_C_pin" targetSignal="Channel_C_pad" srcVirtualSignal="//@virtualSignals.26" targetVirtualSignal="//@virtualSignals.46"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_8/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_8" systemDefined="true" sourceSignal="Channel_C_pad" targetSignal="Channel_C_input" srcVirtualSignal="//@virtualSignals.46" targetVirtualSignal="//@virtualSignals.66"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_8" systemDefined="true" targetSignal="Channel_C_sel" required="false" targetVirtualSignal="//@virtualSignals.86" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_8" systemDefined="true" targetSignal="Channel_C_sel" required="false" targetVirtualSignal="//@virtualSignals.86" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_8" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_C_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.86"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_2" systemDefined="true" targetSignal="Channel_C_iclass" required="false" targetVirtualSignal="//@virtualSignals.100" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_2" systemDefined="true" targetSignal="Channel_C_iclass" required="false" targetVirtualSignal="//@virtualSignals.100" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_2" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_C_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.100"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_8/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_8" systemDefined="true" targetSignal="Channel_C_input" required="false" targetVirtualSignal="//@virtualSignals.66" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_8/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_8" systemDefined="true" sourceSignal="Channel_C_channel_to_result" targetSignal="Channel_C_result_to_channel" srcVirtualSignal="//@virtualSignals.138" targetVirtualSignal="//@virtualSignals.118"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_9/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_9" systemDefined="true" sourceSignal="Channel_C_sync_slaveA_pad" targetSignal="Channel_C_sync_slaveA_pin" srcVirtualSignal="//@virtualSignals.47" targetVirtualSignal="//@virtualSignals.27"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_9/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_9" systemDefined="true" sourceSignal="Channel_C_sync_slaveA_pin" targetSignal="Channel_C_sync_slaveA_pad" srcVirtualSignal="//@virtualSignals.27" targetVirtualSignal="//@virtualSignals.47"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_9/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_9" systemDefined="true" sourceSignal="Channel_C_sync_slaveA_pad" targetSignal="Channel_C_sync_slaveA_input" srcVirtualSignal="//@virtualSignals.47" targetVirtualSignal="//@virtualSignals.67"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_9/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_9" systemDefined="true" targetSignal="Channel_C_sync_slaveA_input" required="false" targetVirtualSignal="//@virtualSignals.67" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_9/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_9" systemDefined="true" sourceSignal="Channel_C_sync_slaveA_channel_to_result" targetSignal="vs_Channel_C_sync_slaveA_result_to_channel" srcVirtualSignal="//@virtualSignals.139" targetVirtualSignal="//@virtualSignals.119"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_10/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_10" systemDefined="true" sourceSignal="Channel_C_sync_slaveB_pad" targetSignal="Channel_C_sync_slaveB_pin" srcVirtualSignal="//@virtualSignals.48" targetVirtualSignal="//@virtualSignals.28"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_10/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_10" systemDefined="true" sourceSignal="Channel_C_sync_slaveB_pin" targetSignal="Channel_C_sync_slaveB_pad" srcVirtualSignal="//@virtualSignals.28" targetVirtualSignal="//@virtualSignals.48"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_10/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_10" systemDefined="true" sourceSignal="Channel_C_sync_slaveB_pad" targetSignal="Channel_C_sync_slaveB_input" srcVirtualSignal="//@virtualSignals.48" targetVirtualSignal="//@virtualSignals.68"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_10/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_10" systemDefined="true" targetSignal="Channel_C_sync_slaveB_input" required="false" targetVirtualSignal="//@virtualSignals.68" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_10/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_10" systemDefined="true" sourceSignal="Channel_C_sync_slaveB_channel_to_result" targetSignal="vs_Channel_C_sync_slaveB_result_to_channel" srcVirtualSignal="//@virtualSignals.140" targetVirtualSignal="//@virtualSignals.120"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_11/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_11" systemDefined="true" sourceSignal="Channel_C_sync_slaveC_pad" targetSignal="Channel_C_sync_slaveC_pin" srcVirtualSignal="//@virtualSignals.49" targetVirtualSignal="//@virtualSignals.29"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_11/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_11" systemDefined="true" sourceSignal="Channel_C_sync_slaveC_pin" targetSignal="Channel_C_sync_slaveC_pad" srcVirtualSignal="//@virtualSignals.29" targetVirtualSignal="//@virtualSignals.49"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_11/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_11" systemDefined="true" sourceSignal="Channel_C_sync_slaveC_pad" targetSignal="Channel_C_sync_slaveC_input" srcVirtualSignal="//@virtualSignals.49" targetVirtualSignal="//@virtualSignals.69"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_11/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_11" systemDefined="true" targetSignal="Channel_C_sync_slaveC_input" required="false" targetVirtualSignal="//@virtualSignals.69" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_11/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_11" systemDefined="true" sourceSignal="Channel_C_sync_slaveC_channel_to_result" targetSignal="vs_Channel_C_sync_slaveC_result_to_channel" srcVirtualSignal="//@virtualSignals.141" targetVirtualSignal="//@virtualSignals.121"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_12/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_12" systemDefined="true" sourceSignal="Channel_D_pad" targetSignal="Channel_D_pin" srcVirtualSignal="//@virtualSignals.50" targetVirtualSignal="//@virtualSignals.30"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_12/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_12" systemDefined="true" sourceSignal="Channel_D_pin" targetSignal="Channel_D_pad" srcVirtualSignal="//@virtualSignals.30" targetVirtualSignal="//@virtualSignals.50"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_12/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_12" systemDefined="true" sourceSignal="Channel_D_pad" targetSignal="Channel_D_input" srcVirtualSignal="//@virtualSignals.50" targetVirtualSignal="//@virtualSignals.70"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_12" systemDefined="true" targetSignal="Channel_D_sel" required="false" targetVirtualSignal="//@virtualSignals.90" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_12" systemDefined="true" targetSignal="Channel_D_sel" required="false" targetVirtualSignal="//@virtualSignals.90" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_12" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_D_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.90"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_3" systemDefined="true" targetSignal="Channel_D_iclass" required="false" targetVirtualSignal="//@virtualSignals.101" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_3" systemDefined="true" targetSignal="Channel_D_iclass" required="false" targetVirtualSignal="//@virtualSignals.101" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_3" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_D_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.101"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_12/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_12" systemDefined="true" targetSignal="Channel_D_input" required="false" targetVirtualSignal="//@virtualSignals.70" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_12/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_12" systemDefined="true" sourceSignal="Channel_D_channel_to_result" targetSignal="Channel_D_result_to_channel" srcVirtualSignal="//@virtualSignals.142" targetVirtualSignal="//@virtualSignals.122"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_13/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_13" systemDefined="true" sourceSignal="Channel_D_sync_slaveA_pad" targetSignal="Channel_D_sync_slaveA_pin" srcVirtualSignal="//@virtualSignals.51" targetVirtualSignal="//@virtualSignals.31"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_13/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_13" systemDefined="true" sourceSignal="Channel_D_sync_slaveA_pin" targetSignal="Channel_D_sync_slaveA_pad" srcVirtualSignal="//@virtualSignals.31" targetVirtualSignal="//@virtualSignals.51"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_13/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_13" systemDefined="true" sourceSignal="Channel_D_sync_slaveA_pad" targetSignal="Channel_D_sync_slaveA_input" srcVirtualSignal="//@virtualSignals.51" targetVirtualSignal="//@virtualSignals.71"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_13/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_13" systemDefined="true" targetSignal="Channel_D_sync_slaveA_input" required="false" targetVirtualSignal="//@virtualSignals.71" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_13/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_13" systemDefined="true" sourceSignal="Channel_D_sync_slaveA_channel_to_result" targetSignal="vs_Channel_D_sync_slaveA_result_to_channel" srcVirtualSignal="//@virtualSignals.143" targetVirtualSignal="//@virtualSignals.123"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_14/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_14" systemDefined="true" sourceSignal="Channel_D_sync_slaveB_pad" targetSignal="Channel_D_sync_slaveB_pin" srcVirtualSignal="//@virtualSignals.52" targetVirtualSignal="//@virtualSignals.32"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_14/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_14" systemDefined="true" sourceSignal="Channel_D_sync_slaveB_pin" targetSignal="Channel_D_sync_slaveB_pad" srcVirtualSignal="//@virtualSignals.32" targetVirtualSignal="//@virtualSignals.52"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_14/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_14" systemDefined="true" sourceSignal="Channel_D_sync_slaveB_pad" targetSignal="Channel_D_sync_slaveB_input" srcVirtualSignal="//@virtualSignals.52" targetVirtualSignal="//@virtualSignals.72"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_14/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_14" systemDefined="true" targetSignal="Channel_D_sync_slaveB_input" required="false" targetVirtualSignal="//@virtualSignals.72" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_14/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_14" systemDefined="true" sourceSignal="Channel_D_sync_slaveB_channel_to_result" targetSignal="vs_Channel_D_sync_slaveB_result_to_channel" srcVirtualSignal="//@virtualSignals.144" targetVirtualSignal="//@virtualSignals.124"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_15/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_15" systemDefined="true" sourceSignal="Channel_D_sync_slaveC_pad" targetSignal="Channel_D_sync_slaveC_pin" srcVirtualSignal="//@virtualSignals.53" targetVirtualSignal="//@virtualSignals.33"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_15/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_15" systemDefined="true" sourceSignal="Channel_D_sync_slaveC_pin" targetSignal="Channel_D_sync_slaveC_pad" srcVirtualSignal="//@virtualSignals.33" targetVirtualSignal="//@virtualSignals.53"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_15/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_15" systemDefined="true" sourceSignal="Channel_D_sync_slaveC_pad" targetSignal="Channel_D_sync_slaveC_input" srcVirtualSignal="//@virtualSignals.53" targetVirtualSignal="//@virtualSignals.73"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_15/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_15" systemDefined="true" targetSignal="Channel_D_sync_slaveC_input" required="false" targetVirtualSignal="//@virtualSignals.73" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_15/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_15" systemDefined="true" sourceSignal="Channel_D_sync_slaveC_channel_to_result" targetSignal="vs_Channel_D_sync_slaveC_result_to_channel" srcVirtualSignal="//@virtualSignals.145" targetVirtualSignal="//@virtualSignals.125"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_16/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_16" systemDefined="true" sourceSignal="Channel_E_pad" targetSignal="Channel_E_pin" srcVirtualSignal="//@virtualSignals.54" targetVirtualSignal="//@virtualSignals.34"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_16/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_16" systemDefined="true" sourceSignal="Channel_E_pin" targetSignal="Channel_E_pad" srcVirtualSignal="//@virtualSignals.34" targetVirtualSignal="//@virtualSignals.54"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_16/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_16" systemDefined="true" sourceSignal="Channel_E_pad" targetSignal="Channel_E_input" srcVirtualSignal="//@virtualSignals.54" targetVirtualSignal="//@virtualSignals.74"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_16" systemDefined="true" targetSignal="Channel_E_sel" required="false" targetVirtualSignal="//@virtualSignals.94" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_16" systemDefined="true" targetSignal="Channel_E_sel" required="false" targetVirtualSignal="//@virtualSignals.94" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_16" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_E_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.94"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_4" systemDefined="true" targetSignal="Channel_E_iclass" required="false" targetVirtualSignal="//@virtualSignals.102" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_4" systemDefined="true" targetSignal="Channel_E_iclass" required="false" targetVirtualSignal="//@virtualSignals.102" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_4" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_E_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.102"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_16/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_16" systemDefined="true" targetSignal="Channel_E_input" required="false" targetVirtualSignal="//@virtualSignals.74" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_16/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_16" systemDefined="true" sourceSignal="Channel_E_channel_to_result" targetSignal="Channel_E_result_to_channel" srcVirtualSignal="//@virtualSignals.146" targetVirtualSignal="//@virtualSignals.126"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_17/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_17" systemDefined="true" sourceSignal="Channel_F_pad" targetSignal="Channel_F_pin" srcVirtualSignal="//@virtualSignals.55" targetVirtualSignal="//@virtualSignals.35"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_17/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_17" systemDefined="true" sourceSignal="Channel_F_pin" targetSignal="Channel_F_pad" srcVirtualSignal="//@virtualSignals.35" targetVirtualSignal="//@virtualSignals.55"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_17/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_17" systemDefined="true" sourceSignal="Channel_F_pad" targetSignal="Channel_F_input" srcVirtualSignal="//@virtualSignals.55" targetVirtualSignal="//@virtualSignals.75"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_17" systemDefined="true" targetSignal="Channel_F_sel" required="false" targetVirtualSignal="//@virtualSignals.95" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_17" systemDefined="true" targetSignal="Channel_F_sel" required="false" targetVirtualSignal="//@virtualSignals.95" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_17" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_F_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.95"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_5" systemDefined="true" targetSignal="Channel_F_iclass" required="false" targetVirtualSignal="//@virtualSignals.103" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_5" systemDefined="true" targetSignal="Channel_F_iclass" required="false" targetVirtualSignal="//@virtualSignals.103" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_5" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_F_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.103"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_17/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_17" systemDefined="true" targetSignal="Channel_F_input" required="false" targetVirtualSignal="//@virtualSignals.75" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_17/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_17" systemDefined="true" sourceSignal="Channel_F_channel_to_result" targetSignal="Channel_F_result_to_channel" srcVirtualSignal="//@virtualSignals.147" targetVirtualSignal="//@virtualSignals.127"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_18/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_18" systemDefined="true" sourceSignal="Channel_G_pad" targetSignal="Channel_G_pin" srcVirtualSignal="//@virtualSignals.56" targetVirtualSignal="//@virtualSignals.36"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_18/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_18" systemDefined="true" sourceSignal="Channel_G_pin" targetSignal="Channel_G_pad" srcVirtualSignal="//@virtualSignals.36" targetVirtualSignal="//@virtualSignals.56"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_18/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_18" systemDefined="true" sourceSignal="Channel_G_pad" targetSignal="Channel_G_input" srcVirtualSignal="//@virtualSignals.56" targetVirtualSignal="//@virtualSignals.76"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_18" systemDefined="true" targetSignal="Channel_G_sel" required="false" targetVirtualSignal="//@virtualSignals.96" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_18" systemDefined="true" targetSignal="Channel_G_sel" required="false" targetVirtualSignal="//@virtualSignals.96" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_18" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_G_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.96"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_6" systemDefined="true" targetSignal="Channel_G_iclass" required="false" targetVirtualSignal="//@virtualSignals.104" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_6" systemDefined="true" targetSignal="Channel_G_iclass" required="false" targetVirtualSignal="//@virtualSignals.104" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_6" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_G_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.104"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_18/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_18" systemDefined="true" targetSignal="Channel_G_input" required="false" targetVirtualSignal="//@virtualSignals.76" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_18/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_18" systemDefined="true" sourceSignal="Channel_G_channel_to_result" targetSignal="Channel_G_result_to_channel" srcVirtualSignal="//@virtualSignals.148" targetVirtualSignal="//@virtualSignals.128"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_19/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_19" systemDefined="true" sourceSignal="Channel_H_pad" targetSignal="Channel_H_pin" srcVirtualSignal="//@virtualSignals.57" targetVirtualSignal="//@virtualSignals.37"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_pin_pad_signal_19/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_19" systemDefined="true" sourceSignal="Channel_H_pin" targetSignal="Channel_H_pad" srcVirtualSignal="//@virtualSignals.37" targetVirtualSignal="//@virtualSignals.57"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_pin_signal_19/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_19" systemDefined="true" sourceSignal="Channel_H_pad" targetSignal="Channel_H_input" srcVirtualSignal="//@virtualSignals.57" targetVirtualSignal="//@virtualSignals.77"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_19" systemDefined="true" targetSignal="Channel_H_sel" required="false" targetVirtualSignal="//@virtualSignals.97" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_19" systemDefined="true" targetSignal="Channel_H_sel" required="false" targetVirtualSignal="//@virtualSignals.97" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_19" systemDefined="true" sourceSignal="queue_select" targetSignal="Channel_H_sel" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.97"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_scan_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_7" systemDefined="true" targetSignal="Channel_H_iclass" required="false" targetVirtualSignal="//@virtualSignals.105" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_queue_iclass_select/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_7" systemDefined="true" targetSignal="Channel_H_iclass" required="false" targetVirtualSignal="//@virtualSignals.105" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_iclass2channel/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_iclass_select_7" systemDefined="true" sourceSignal="iclass_select" targetSignal="Channel_H_iclass" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.105"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_channel_analog_io_pin_19/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_gch_19" systemDefined="true" targetSignal="Channel_H_input" required="false" targetVirtualSignal="//@virtualSignals.77" containingProxySignal="true"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_res_sel_19/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_result_res_sel_19" systemDefined="true" sourceSignal="Channel_H_channel_to_result" targetSignal="Channel_H_result_to_channel" srcVirtualSignal="//@virtualSignals.149" targetVirtualSignal="//@virtualSignals.129"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_0" systemDefined="true" sourceSignal="master select" targetSignal="Channel_A_sel" srcVirtualSignal="//@virtualSignals.106" targetVirtualSignal="//@virtualSignals.78"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_4" systemDefined="true" sourceSignal="master select" targetSignal="Channel_B_sel" srcVirtualSignal="//@virtualSignals.106" targetVirtualSignal="//@virtualSignals.82"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_8" systemDefined="true" sourceSignal="master select" targetSignal="Channel_C_sel" srcVirtualSignal="//@virtualSignals.106" targetVirtualSignal="//@virtualSignals.86"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_0/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_12" systemDefined="true" sourceSignal="master select" targetSignal="Channel_D_sel" srcVirtualSignal="//@virtualSignals.106" targetVirtualSignal="//@virtualSignals.90"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_1" systemDefined="true" sourceSignal="slaveA select" targetSignal="Channel_A_sync_slaveA_sel" srcVirtualSignal="//@virtualSignals.107" targetVirtualSignal="//@virtualSignals.79"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_5" systemDefined="true" sourceSignal="slaveA select" targetSignal="Channel_B_sync_slaveA_sel" srcVirtualSignal="//@virtualSignals.107" targetVirtualSignal="//@virtualSignals.83"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_9" systemDefined="true" sourceSignal="slaveA select" targetSignal="Channel_C_sync_slaveA_sel" srcVirtualSignal="//@virtualSignals.107" targetVirtualSignal="//@virtualSignals.87"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_1/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_13" systemDefined="true" sourceSignal="slaveA select" targetSignal="Channel_D_sync_slaveA_sel" srcVirtualSignal="//@virtualSignals.107" targetVirtualSignal="//@virtualSignals.91"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_2" systemDefined="true" sourceSignal="slaveB select" targetSignal="Channel_A_sync_slaveB_sel" srcVirtualSignal="//@virtualSignals.108" targetVirtualSignal="//@virtualSignals.80"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_6" systemDefined="true" sourceSignal="slaveB select" targetSignal="Channel_B_sync_slaveB_sel" srcVirtualSignal="//@virtualSignals.108" targetVirtualSignal="//@virtualSignals.84"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_10" systemDefined="true" sourceSignal="slaveB select" targetSignal="Channel_C_sync_slaveB_sel" srcVirtualSignal="//@virtualSignals.108" targetVirtualSignal="//@virtualSignals.88"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_14" systemDefined="true" sourceSignal="slaveB select" targetSignal="Channel_D_sync_slaveB_sel" srcVirtualSignal="//@virtualSignals.108" targetVirtualSignal="//@virtualSignals.92"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_3" systemDefined="true" sourceSignal="slaveC select" targetSignal="Channel_A_sync_slaveC_sel" srcVirtualSignal="//@virtualSignals.109" targetVirtualSignal="//@virtualSignals.81"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_7" systemDefined="true" sourceSignal="slaveC select" targetSignal="Channel_B_sync_slaveC_sel" srcVirtualSignal="//@virtualSignals.109" targetVirtualSignal="//@virtualSignals.85"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_11" systemDefined="true" sourceSignal="slaveC select" targetSignal="Channel_C_sync_slaveC_sel" srcVirtualSignal="//@virtualSignals.109" targetVirtualSignal="//@virtualSignals.89"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_sync_select_3/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_adv_measurement_ch_select_15" systemDefined="true" sourceSignal="slaveC select" targetSignal="Channel_D_sync_slaveC_sel" srcVirtualSignal="//@virtualSignals.109" targetVirtualSignal="//@virtualSignals.93"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_classselect_out/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_classselect_in" systemDefined="true" sourceSignal="class_select" targetSignal="queue_iclass_select" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.2"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_global_signal_to_request_src/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_to_global" systemDefined="true" sourceSignal="global_signal" targetSignal="queue_to_global" targetVirtualSignal="//@virtualSignals.6" proxySrcVirtualSignalUri="http://resources/4.0.22/app/GLOBAL_ADC/0/vs_global_adc_global" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_ADC/v4_0_22/GLOBAL_ADC_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_ADC/v4_0_22/GLOBAL_ADC_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_classselect_out/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_classselect_in" systemDefined="true" sourceSignal="class_select" targetSignal="scan_iclass_select" srcVirtualSignal="//@virtualSignals.11" targetVirtualSignal="//@virtualSignals.10"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_global_signal_to_request_src/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_to_global" systemDefined="true" sourceSignal="global_signal" targetSignal="scan_to_global" targetVirtualSignal="//@virtualSignals.14" proxySrcVirtualSignalUri="http://resources/4.0.22/app/GLOBAL_ADC/0/vs_global_adc_global" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_ADC/v4_0_22/GLOBAL_ADC_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_ADC/v4_0_22/GLOBAL_ADC_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_scan_sourceevent/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_nvic_src" systemDefined="true" sourceSignal="event_scan_source" targetSignal="sr_interrupt_signal" required="false" srcVirtualSignal="//@virtualSignals.17" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_queue_sourceevent/http://resources/4.0.20/app/ADC_MEASUREMENT_ADV/2/vs_adc_measurement_adv_nvic_src" systemDefined="true" sourceSignal="event_queue_source" targetSignal="sr_interrupt_signal" required="false" srcVirtualSignal="//@virtualSignals.9" targetVirtualSignal="//@virtualSignals.0"/>
</ResourceModel:App>
