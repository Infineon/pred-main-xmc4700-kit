<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="I2S_CONFIG" URI="http://resources/4.0.6/app/I2S_CONFIG/0" description="Configures the USIC peripheral to function as an I2S master or slave device" mode="NOTSHARABLE" version="4.0.6" minDaveVersion="4.2.4" instanceLabel="I2S_CONFIG_0" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="Serial Data In" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dx0ins" hwSignal="dx0ins" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../DIGITAL_IO/v4_0_16/DIGITAL_IO_30.app#//@connections.2"/>
  </virtualSignals>
  <virtualSignals name="dx1ins" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dx1ins" hwSignal="dx1ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="dx1ins_out" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dx1ins_sys_out" hwSignal="dx1ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="dx2ins" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dx2ins" hwSignal="dx2ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="Serial Data Out" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dout0" hwSignal="dout0" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="dx2ins_out" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dx2ins_sys_out" hwSignal="dx2ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="selox" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_selo_0" hwSignal="selo0" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="sclkout" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_sclkout" hwSignal="sclkout" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="mclkout" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_mclkout" hwSignal="mclkout" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="transmit_buffer_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_standard_tx_event" hwSignal="transmit_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="standard_receive_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_standard_rx_event" hwSignal="standard_receive_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="transmit_shift_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_tx_shift_event" hwSignal="transmit_shift_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="receive_start_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_rx_start_event" hwSignal="receive_start_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="alternate_receive_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_alt_rx_event" hwSignal="alternate_receive_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="protocol_specific_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_proto_specfic_event" hwSignal="protocol_specific_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_standard_transmit_buffer_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_tx_event" hwSignal="standard_transmit_buffer_int" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="fifo_transmit_buffer_error_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_tx_err_event" hwSignal="transmit_buffer_error_int" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="fifo_standard_receive_buffer_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_rx_event" hwSignal="standard_receive_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_receive_buffer_error_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_rx_err_event" hwSignal="receive_buffer_error_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_alternate_receive_buffer_event" URI="http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_alt_rx_event" hwSignal="alternate_receive_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <requiredApps URI="http://resources/4.0.6/app/I2S_CONFIG/0/ra_clock" requiredAppName="CLOCK_XMC4" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CLOCK_XMC4/v4_0_22/CLOCK_XMC4_0.app#/"/>
  </requiredApps>
  <hwResources name="Channel" URI="http://resources/4.0.6/app/I2S_CONFIG/0/hwres_usic_channel" resourceGroupUri="peripheral/usic/0/channel/1" constraintType="GLOBAL_RESOURCE" mResGrpUri="peripheral/usic/*/channel/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/usic0/usic0_0.dd#//@provided.43"/>
  </hwResources>
  <connections URI="http://resources/4.0.6/app/I2S_CONFIG/0/http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dout0/http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_dx0ins" systemDefined="true" sourceSignal="Serial Data Out" targetSignal="Serial Data In" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.0.6/app/I2S_CONFIG/0/http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_sclkout/http://resources/4.0.16/app/DIGITAL_IO/31/vs_digital_io_pad_pin" sourceSignal="sclkout" targetSignal="pin" srcVirtualSignal="//@virtualSignals.7">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../DIGITAL_IO/v4_0_16/DIGITAL_IO_31.app#//@virtualSignals.1"/>
    <targetVirtualSignal href="../../DIGITAL_IO/v4_0_16/DIGITAL_IO_31.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.0.6/app/I2S_CONFIG/0/http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_selo_0/http://resources/4.0.16/app/DIGITAL_IO/32/vs_digital_io_pad_pin" sourceSignal="selox" targetSignal="pin" srcVirtualSignal="//@virtualSignals.6">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../DIGITAL_IO/v4_0_16/DIGITAL_IO_32.app#//@virtualSignals.1"/>
    <targetVirtualSignal href="../../DIGITAL_IO/v4_0_16/DIGITAL_IO_32.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.0.6/app/I2S_CONFIG/0/http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_alt_rx_event/http://resources/4.0.10/app/INTERRUPT/0/vs_nvic_signal_in" sourceSignal="fifo_alternate_receive_buffer_event" targetSignal="sr_irq" srcVirtualSignal="//@virtualSignals.19">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../INTERRUPT/v4_0_10/INTERRUPT_0.app#//@virtualSignals.0"/>
    <targetVirtualSignal href="../../INTERRUPT/v4_0_10/INTERRUPT_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.6/app/I2S_CONFIG/0/http://resources/4.0.6/app/I2S_CONFIG/0/vs_i2s_fifo_rx_event/http://resources/4.0.10/app/INTERRUPT/0/vs_nvic_signal_in" sourceSignal="fifo_standard_receive_buffer_event" targetSignal="sr_irq" srcVirtualSignal="//@virtualSignals.17">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../INTERRUPT/v4_0_10/INTERRUPT_0.app#//@virtualSignals.0"/>
    <targetVirtualSignal href="../../INTERRUPT/v4_0_10/INTERRUPT_0.app#//@virtualSignals.0"/>
  </connections>
</ResourceModel:App>
