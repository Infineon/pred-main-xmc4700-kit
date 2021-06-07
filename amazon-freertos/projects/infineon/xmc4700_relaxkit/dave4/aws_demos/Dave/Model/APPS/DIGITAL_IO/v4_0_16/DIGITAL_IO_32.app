<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="DIGITAL_IO" URI="http://resources/4.0.16/app/DIGITAL_IO/32" description="The DIGITAL_IO APP is used to configure &#xA; a port pin as digital Input/Output." mode="NOTSHARABLE" version="4.0.16" minDaveVersion="4.0.0" instanceLabel="I2S_LRCLK" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="software controlled output signal" URI="http://resources/4.0.16/app/DIGITAL_IO/32/vs_digital_io_sw_pin" hwSignal="swreg_out" hwResource="//@hwResources.0"/>
  <virtualSignals name="pin" URI="http://resources/4.0.16/app/DIGITAL_IO/32/vs_digital_io_pad_pin" hwSignal="pad" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../I2S_CONFIG/v4_0_6/I2S_CONFIG_0.app#//@connections.2"/>
  </virtualSignals>
  <virtualSignals name="hardware pin control" URI="http://resources/4.0.16/app/DIGITAL_IO/32/vs_digital_io_hwsel" hwSignal="hw_o" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="pin_signal" URI="http://resources/4.0.16/app/DIGITAL_IO/32/__pin_vs_digital_io_pad_pin" hwSignal="pin" hwResource="//@hwResources.1"/>
  <hwResources name="pin" URI="http://resources/4.0.16/app/DIGITAL_IO/32/hwres_port_pin" resourceGroupUri="port/p/sv0/pad/*" solverVariable="true" mResGrpUri="port/p/sv0/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/port6/port6_6.dd#//@provided.10"/>
    <solverVarMap index="2">
      <value variableName="sv0" solverValue="6"/>
    </solverVarMap>
    <solverVarMap index="2">
      <value variableName="sv0" solverValue="6"/>
    </solverVarMap>
  </hwResources>
  <hwResources name="pin" URI="http://resources/4.0.16/app/DIGITAL_IO/32/__pin_hwres_port_pin" resourceGroupUri="devicepackage/0/100" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.68"/>
  </hwResources>
  <connections URI="http://resources/4.0.16/app/DIGITAL_IO/32/http://resources/4.0.16/app/DIGITAL_IO/32/vs_digital_io_pad_pin/http://resources/4.0.16/app/DIGITAL_IO/32/__pin_vs_digital_io_pad_pin" systemDefined="true" sourceSignal="pin" targetSignal="pin_signal" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.0.16/app/DIGITAL_IO/32/http://resources/4.0.16/app/DIGITAL_IO/32/__pin_vs_digital_io_pad_pin/http://resources/4.0.16/app/DIGITAL_IO/32/vs_digital_io_pad_pin" systemDefined="true" sourceSignal="pin_signal" targetSignal="pin" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.1"/>
</ResourceModel:App>
