# Quick Start Guide <!-- omit in toc -->

## Table of Content <!-- omit in toc -->
- [Introduction](#introduction)
- [**Windows 10**: AWS Infrastructure Deployment Guide](#windows-10-aws-infrastructure-deployment-guide)
  - [Step-by-step Guide for Windows](#step-by-step-guide-for-windows)
  - [Overview Available Commands](#overview-available-commands)
- [Kibana Dashboard Setup](#kibana-dashboard-setup)
  - [Step-by-step Guide for Kibana Dashboard Setup](#step-by-step-guide-for-kibana-dashboard-setup)
- [Anomaly Detection](#anomaly-detection)
  - [General Information](#general-information)
  - [Preparation and Training](#preparation-and-training)
  - [Test Cases](#test-cases)
- [Additional Documentation](#additional-documentation)
- [**Windows 10**: Device Firmware Guide](#windows-10-device-firmware-guide)
  - [Introduction for Windows](#introduction-for-windows)
  - [Preparation](#preparation)
  - [Step-by-step Guide for Windows](#step-by-step-guide-for-windows-1)
- [Hardware Configuration of the Kit](#hardware-configuration-of-the-kit)
- [Software Modification of the Firmware](#software-modification-of-the-firmware)
- [Known Problems and Support](#known-problems-and-support)

## Introduction
This quick-start guides you step-by-step through setting up the XENSIV™ Predictive Maintenance Evaluation Kit EVAL_XMC47_PREDMAIN_AA for Windows.  
Depending on your OS, a slightly modified approach might be required from the one for Windows.

The following steps have to be completed for a quick-start of the XENSIV™ Predictive Maintenance Evaluation Kit:

1. [AWS Infrastructure Deployment](#windows-10-aws-infrastructure-deployment-guide)
2. [Kibana Dashboard Setup](#kibana-dashboard-setup)
3. [Device Firmware Guide](#windows-10-device-firmware-guide)

Please refer to the respective section as outlined in the above table of content (ToC).

[The following section is taken from ../cdk-script/README.md]: #
## **Windows 10**: AWS Infrastructure Deployment Guide

### Step-by-step Guide for Windows
The below step-by-step guide shows how to deploy the AWS infrastructure from a machine running Windows 10.

**IMPORTANT:** an AWS account is required.

* Install WSL and configure it according to the instructions here: https://docs.microsoft.com/en-us/windows/wsl/install-win10. This approach is only available for **Windows 10 64 Bit (excluding LTSB/LTSC systems)**.

To install the Windows Subsystem for Linux using PowerShell, follow these steps:

1. Open *Start*
1. Search for *PowerShell*, right-click the top result, and select the *Run as administrator*  
![](/docs/00_Images/PowerShell_Instruction.png)

1. Type the following command to enable the Linux subsystem and press *Enter*: `Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux`
2. Type `Y` and press *Enter* to confirm and restart your computer

To install Ubuntu from Microsoft store, follow these steps:

1. Open the Microsoft store  
![](/docs/00_Images/MicrosoftStore_Open.png)

1. Install [Ubuntu](https://www.microsoft.com/en-us/p/ubuntu/9nblggh4msv6) from Microsoft store  
![](/docs/00_Images/MicrosoftStore_Ubuntu.png)

1. Launch Ubuntu application and after installation enter a new username and password. **IMPORTANT:** remember or record it, the username and password will be required for the following steps.  
![](/docs/00_Images/UbuntuConsole_Installation.png)

**IMPORTANT:** for the next steps, you will need to enter a lot of commands into the Ubuntu terminal. You don't need to type them manually. It is much easier to copy them from instruction using `Ctrl+C` and paste into Ubuntu terminal by simply pressing the right mouse button.

To get the repository, execute from a running Ubuntu terminal the following steps:

* Prepare the project and clone this repository:

    ```bash
    # Create a folder for the project
    mkdir /mnt/c/project/
    # Change to the created folder
    cd /mnt/c/project/
    # Set autocrlf config
    git config --global core.autocrlf true
    # Clone source code from GitHub (user Ubuntu username and password combination):
    sudo git clone --recurse-submodules https://github.com/Infineon/pred-main-xmc4700-kit.git
    # Change to the created folder
    cd pred-main-xmc4700-kit
    ```

To deploy the system to the AWS cloud, execute from a running Ubuntu terminal the following steps:

1. The following steps assume that you are in the root folder of the `hvacr-reference-kit` project 

2. Execute the following commands to start deploying the AWS infrastructure:

    ```bash
    # Change to the cdk-script folder
    cd cdk-script
    # Start the process by executing the script
    ./start.sh
    # The installation process has started - it will now take some time
    # If required, enter the password for the running Ubuntu session
    ```

3. The script will install all needed dependencies and will deploy the stack to AWS. You will see a progress bar status and the overall **process will take about 30 minutes**.

4. During execution, AWS `Access Key` and `Secret Key` will be required.  
  You may receive them during AWS registration procedure (for private users) or from your system administrator (for business users). For more information, please see [here](https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_access-keys.html).

1. In case of typing an incorrect password, re-launch `./start.sh` and press *Enter* to repeat the step

1. The default region name is `us-east-1`

1. Field `default output format` should be empty, please press “Enter”

**IMPORTANT NOTE:** Windows terminals have a [peculiarity](https://stackoverflow.com/questions/33883530/why-is-my-command-prompt-freezing-on-windows-10) with lingering processes as it could stop refreshing the displayed output. Therefore, please be patient and avoid using scroll and text high-lighting in the console during the deployment process. In case of selection of any text, the console header switches to *Select* mode. To leave it, press the *Enter* button.  
![](/docs/00_Images/CDK-Script_Output.png)

If the process completes successfully, you will see a message similar to the following one:  
![](/docs/00_Images/StartScript_Success.png)

**IMPORTANT:** links to your Kibana dashboard and IoT endpoint were saved to appropriate `kibana.txt` and `endpoint.txt` files in the project directory `./patch/credentials`. You will need it for the firmware deployment steps.

The following steps will add a device with deviceName (ThingName in AWS terminology) and certificate for secure connection and authentication to AWS.  
To register your device, execute the following steps from a terminal:

1. Run `make register-device` 

2. Enter a device with a deviceName. You could use any name you prefer, e.g. `demo`, `Dev_board`, `HVACR_kit`, `my_thing`, `device1234`, etc.

3. Every `Extension Board for Sensors` is equipped with a unique OPTIGA™ Trust M secure element.
   The respective (public) certificate of the OPTIGA™ Trust M will be used for authentication in combination with AWS Multi-Account registration.

4. If you want to receive the public certificate of the EVAL_XMC47_PREDMAIN_AA kit, you could either:  
    * Get it online for your device with [Infineon Toolbox](https://softwaretools.infineon.com/?_ga=2.64790316.20786652.1621330825-107268889.1614749757) by scanning the QR code of the box or entering the serial number from the `Extension Board for Sensors`.  
    For more information, please follow the instructions here [Get the Certificate from the OPTIGA™ Trust M with Infineon Toolbox](/docs/03_Software/01_SoftwareDevelopment.md#get-the-certificate-from-the-optiga-trust-m-with-infineon-toolbox)
    * Get it offline for your device via a serial connection to a connected and [programmed](/patch/README.md) evaluation board during start-up.  
    For more information, please follow the instructions here [Get the Certificate from the OPTIGA™ Trust M with a Serial Connection](/docs/03_Software/01_SoftwareDevelopment.md#get-the-certificate-from-the-optiga-trust-m-with-a-serial-connection)

5. Enter the received certificate from the OPTIGA™ Trust M secure element by copying and pasting it.  
![](/docs/00_Images/SerialConsole_Certificate.png)

4. If the device registration completes successfully, you will see a similar message in your console as shown here:  
![](/docs/00_Images/DeviceRegister_Success.png)

**IMPORTANT:** when you decide to stop or finish using the AWS stack, run the command  `make delete-stack` to delete the deployed infrastructure stack from AWS and avoid unnecessary payments.

### Overview Available Commands
1. Run `make start` or `./start.sh` to install all needed dependencies and deploy stack to AWS
2. Run `make describe-stack` to obtain Kibana and IoT EndPoints from the deployed stack  
![](/docs/00_Images/MakeDescribe_Stack.png)
3. Run `make register-device` to add device with deviceName to AWS  
![](/docs/00_Images/SerialConsole_Certificate.png)
4. Run `make deregister-device` to delete device from AWS  
![](/docs/00_Images/MakeDeregister_Device.png)
5. Run `make delete-stack` to delete deployed infrastructure stack from AWS

## Kibana Dashboard Setup

### Step-by-step Guide for Kibana Dashboard Setup
1. The following steps assume that you have successfully deployed the AWS infrastructure

1. During AWS infrastructure deployment, the link to the Kibana dashboard was printed on the terminal.  
The link to your Kibana dashboard was also saved to `kibana.txt` file in the project directory `/patch/credentials`.

2. Open the Kibana dashboard landing page and create an account by clicking `Sign up` and providing the details:  
![](/docs/00_Images/KibanaDashboard_Register.png)

3. During registration, a verification code will be sent to the provided mailbox.  
Provide this code during registration in the Kibana dashboard.

4. Go to `Dashboard` from the tabs on the left side or by the link in the center:  
![](/docs/00_Images/KibanaDashboard_Visualization.png)

5. Choose `InfineonBoard Detailed`:  
![](/docs/00_Images/KibanaDashboard_Detailed.png)

6. Discover your device and open the tab `SAVED QUERIES` to select the respective query.  
The name was given during device registration and can be different from the shown one here:  
![](/docs/00_Images/KibanaDiscover_Device.png)

2. Setup display and refresh periods in the right upper corner (e.g. last 15 min and every second).  
Graphs will appear on your dashboard if you click `Start` and `Apply` buttons. Condition Monitoring is available:  
![](/docs/00_Images/KibanaDashboard_Refresh.png)

**IMPORTANT NOTE:** pay attention that the graphs have autoscaling and auto-set to a useful value range instead of full range from zero. This helps to focus on data changes only and not show flat charts with low volatility.

![](/docs/00_Images/KibanaDashboard_Autoscaling.png)

## Anomaly Detection

### General Information
The system is able to independently process the collected data, determine when the values differ from the *regular* (normal) ones and report it. Such situations are called anomalies.  
To detect anomalies, an unsupervised algorithm Amazon SageMaker [Random Cut Forest](https://docs.aws.amazon.com/sagemaker/latest/dg/randomcutforest.html) is used. The algorithm calculates the value of the internal parameter Anomaly Score. Low values of this parameter correspond to *regular* values of the measured parameters from the sensors. High values mean data deviation.  
For a system designed for installation on industrial equipment, such anomalies can be perceived as a potential problem with the correct functioning of the mechanisms and units. Their detection allows to respond in a timely manner and carry out the necessary maintenance work, identifying and eliminating problems or malfunctions in the operation of units.  
For example, increased pressure in the air channel may indicate a clogged filter; increased level of current, magnetic field, temperature and / or noise - about a malfunction of the electric motor or compressor. Comprehensive analysis of several parameters allows to get a more accurate picture.

Based on the data calculated by the Anomaly Detection algorithm, it is possible to develop a Predictive Maintenance system customized for specific operating conditions.

### Preparation and Training

Upon completion of [Kibana Dashboard Setup](#kibana-dashboard-setup), data from 8 sensors are displayed in the Kibana dashboard (graphs quantity however is 11 as the DPS368 pressure sensors are combined and measure temperature and pressure).

To calculate and display the parameter Anomaly Score, the system must accumulate a certain amount of data. This usually takes about 10 minutes. After that, a dynamically changing value will appear on the circular anomaly gauge on the top left and on the anomaly graph on top right.

![](/docs/00_Images/OverviewAnomaly_Gauge.png)

However, the system does not yet understand what can be considered as *normal* and what is not, and the values of the Anomaly Score cannot yet be considered as relevant.  
To distinguish between normal and non-normal, the system must train itself and operate for some time under normal conditions. As the amount of data is accumulated and processed the calculation accuracy will increase.  
Usually for reaching sufficient accuracy, 24 hours is enough. Further training of the model will no longer give a noticeable increase in accuracy.  
It is desirable that during the period of initial training the data to be the most *normal*, i.e. without significant deviations. Otherwise, the system will also treat them as *normal* which is expected to negatively affect the accuracy of determining anomalies.

**IMPORTANT:** before starting testing the functionality, please study the table below. Some of the shown sensors collect and send data, but this data doesn't affect the calculation of the Anomaly Score. This is indicated by the last column.

![](/docs/00_Images/OverviewSensors_Anomaly.png)

**Notes**
* The more stable (with less volatility) values are given by the sensors in normal mode and the stronger the deviation, the more prominent the anomaly will be (the value of the Anomaly Score).
* For a more rigid Anomaly Score change, it is better to change several parameters at the same time. For example, two adjacent pressure sensors by pressing a finger on the pressure sensor. Both the pressure value and the temperature value measured by the pressure sensor will rise.
* The value of the Anomaly Score parameter is calculated from a certain amount of accumulated data. Therefore, for a clear manifestation of the anomaly, the impact on the sensors should be at least several seconds long. A short-term exposure (a second or two) and a rollback to normal values will show changes, but will not give a clear picture. 
* The limit value of the anomaly gauge (green-red zone) is a value that is empirically adjusted for a specific system. This allows the accuracy of the response to be corrected. 

### Test Cases
* Temperature and pressure sensors could be affected by pressing a finger, using a cigarette lighter, hair dryer or any other heater, hot or cold object. However please be careful with the open flame, because the maximum temp limit of the sensor is 85 °C (185 F). Besides that, try to avoid using liquids and wet objects to prevent shortcut and damage of the hardware.
* Current sensor can be put in series to any electric line with an powerful electric consumer, e.g. heater, kettle, motor, etc. Default settings designed for measurement rang up to 120A and don't require calibration procedure. Therefore low level current (less than 3-5A) will lead to inaccurate values.  
Moreover, the current sensor is based on a magnetic measurement principle, hence could be triggered by moving a strong magnet as well.
* Magnetic Hall sensor could be triggered by moving a strong magnet in front of the sensor (closer-farther). Please consider correct pole polarity depending on the respective Hall sensor.
* Microphone testing does not require any additional equipment, just produce any type of noise: shouting, whistling, clapping hands, knocking, etc. However, pay your attention that data from the microphone has no effect on anomaly calculation in the current edition of the software. You could see a data splash on the appropriate graph only.

## Additional Documentation
Additional documentation and details about the CDK deployment and development can be found [here](/docs/01_AWS/01_AWSInfrastructure.md).
Please refer also to the generic documentation and details as described here in the [README.md](/docs/README.md) of the documentation.

[The following section is taken from ../patch/README.md]: #
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

**Note**: Please open an issue as part of this repository if you need help or support with specific problems.
