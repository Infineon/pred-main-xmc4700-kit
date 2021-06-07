# Quick-start for Device Firmware <!-- omit in toc -->

<img src="../docs/00_Images/BoardBanner_Intro.jpg" width="100%">

## Table of Content <!-- omit in toc -->
- [Quick Start Guide](#quick-start-guide)
- [**Windows 10**: Device Firmware Guide](#windows-10-device-firmware-guide)
  - [Introduction for Windows](#introduction-for-windows)
  - [Preparation](#preparation)
  - [Step-by-step Guide for Windows](#step-by-step-guide-for-windows)
- [Hardware Configuration of the Kit](#hardware-configuration-of-the-kit)
- [Software Modification of the Firmware](#software-modification-of-the-firmware)
- [Known Problems and Support](#known-problems-and-support)
- [License](#license)

## Quick Start Guide

<img src="../docs/00_Images/QuickStart_Initial.jpg" width="100%">

To directly access the [**Getting Started Guide**](/docs/00_QuickStart.md) for the evaluation kit, click the corresponding link [here](/docs/00_QuickStart.md).  

## **Windows 10**: Device Firmware Guide

### Introduction for Windows
This section explains how to quickly set up the firmware for the predictive maintenance evaluation kit on Windows.  
The quick-start is enabled by modifying a precompiled `.hex` file and flashing it to the device.

The `patch` folder contains additional `.hex` and Windows `.bat` files for semi-automatic deployment procedures on Windows.  
If you are an experienced user, you can also build the project from source as described [here](../docs/03_Software/01_SoftwareDevelopment.md).

### Preparation
To communicate with the XMC4700 Relax Kit's on-board debugging probe, you need the drivers included in the J-Link Software and Documentation pack. 
You can download the J-Link Software and Documentation pack from SEGGER's [J-Link software download](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack) page.  
After installation, please make sure that it is available from the `PATH` environment variable.

Moreover, make sure you have [Python](https://www.python.org/downloads/) installed and it is available from the `PATH` environment variable as well.  
Please check during installation "Add Python `<version>` to PATH" as shown here or add it afterwards manually:

![](/docs/00_Images/PythonInstallation_Path.png)

### Step-by-step Guide for Windows
** IMPORTANT NOTE:** the power-up sequence is important to avoid any backfeeding via the PC USB port (protection circuitry is provided on the boards, though).

1. Connect the Extension Board for Sensors (the green one) of the EVAL_XMC47_PREDMAIN_AA kit to the power supply via the provided USB Type-C power supply.  
   ![](/docs/00_Images/ConnectionMainboard_Extension.png)

2. Only after having powered up the extension board, connect the XMC4700 Relax Kit (the red one) to your PC via the provided micro USB cable. 

3. Launch the file explorer and go to the directory `./patch` from the root project directory.  
   ![](/docs/00_Images/ProjectRoot_Directory.png)

4. Double click or execute the `start.bat` Windows Batch File  
   ![](/docs/00_Images/ScriptPatch_Start.png)

5. Enter your network settings in the started console session:

   * AWS endpoint - was shown in console before as part of the AWS deployment procedure and was saved to the file in the project directory `./patch/credentials/endpoint.txt`
   * ThingName - enter the name registered in AWS before as part of the AWS deployment procedure
   * Choose the connection type: Wi-Fi of LTE
   * In case of Wi-Fi connection, type your Wi-Fi SSID 
   * In case of Wi-Fi connection, type your Wi-Fi password and press Enter.  
   Make sure you have an active Wi-Fi access point so that the device can connect to it.  
   
   ![](/docs/00_Images/ScriptStart_Firmware.png)

6. Connect the respective Satellite Boards with the Sensor Boards to the Extension Board for Sensors via the RJ45 connectors and the twisted-pair cabling.  
   A detailed [Step-by-step setup guide](/docs/02_Hardware/02_Setup.md) is available as well for these steps.  
   The step-by-step guide gives additional details for the hardware configuration and guides you through a detailed setup of the sensors.

## Hardware Configuration of the Kit
Further details about the hardware configuration and options of the EVAL_XMC47_PREDMAIN_AA kit can be found in the hardware documentation.

Please refer to the hardware documentation for more details:

* [Overview](/docs/02_Hardware/01_Overview.md)
* [Step-by-step setup guide](/docs/02_Hardware/02_Setup.md)

## Software Modification of the Firmware
Further details about the software configuration and options of the EVAL_XMC47_PREDMAIN_AA firmware can be found in the software development documentation.

Please refer to the software documentation for more details on how to set up the environment and start firmware modification:

* [Software Development Setup](/docs/03_Software/01_SoftwareDevelopment.md)

Details about the build process and firmware modification can be found in the section [Build and Run the FreeRTOS Firmware](/docs/03_Software/01_SoftwareDevelopment.md##build-and-run-the-freertos-firmware).

## Known Problems and Support
Currently, there are no known problems or limitations. 

**Note**: please open an issue as part of this repository if you need help or support with specific problems.

## License
This repository is licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License Agreement V1.0.  
The EVAL_XMC47_PREDMAIN_AA Evaluation Software License Agreement can be found in the `LICENSE.txt` file at the root of the repository or here:

[LICENSE](/LICENSE.txt)

This repository contains software components licensed under 3rd party licenses or Open Source Software (OSS) as part of this software package. 
The respective license files are part of the software components and/or referenced in the source files.

Details on how to obtain the licenses are provided as part of the software components.

Please contact Infineon Technologies AG for questions regarding the software licensing.