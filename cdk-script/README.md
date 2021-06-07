# AWS Infrastructure Deployment Guide: CDK Script <!-- omit in toc -->

<img src="../docs/00_Images/BoardBanner_Intro.jpg" width="100%">

## Table of Content <!-- omit in toc -->
- [Quick Start Guide](#quick-start-guide)
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
- [Technologies and Libraries](#technologies-and-libraries)
- [Known Problems and Support](#known-problems-and-support)
- [License](#license)

## Quick Start Guide

<img src="../docs/00_Images/QuickStart_Initial.jpg" width="100%">

To directly access the [**Getting Started Guide**](/docs/00_QuickStart.md) for the evaluation kit, click the corresponding link [here](/docs/00_QuickStart.md).  

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

**IMPORTANT:** links to your Kibana Dashboard and IoT endpoint were saved to appropriate `kibana.txt` and `endpoint.txt` files in the project directory `./patch/credentials`. You will need it for the firmware deployment steps.

The following steps will add a device with deviceName (ThingName in AWS terminology) and certificate for secure connection and authentication to AWS.  
To register your device, execute the following steps from a terminal:

1. Run `make register-device` 

2. Enter a device with a deviceName. You could use any name you prefer, e.g. `demo`, `Dev_board`, `HVACR_kit`, `my_thing`, `device1234`, etc.

3. Every `Extension Board for Sensors` is equipped with a unique OPTIGA™ Trust M secure element.
   The respective (public) certificate of the OPTIGA™ Trust M will be used for authentication in combination with AWS Multi-Account registration.

4. If you want to receive the public certificate of the EVAL_XMC47_PREDMAIN_AA kit, you could either:  
    * Get it online for your device with [Infineon Toolbox](https://softwaretools.infineon.com/?_ga=2.64790316.20786652.1621330825-107268889.1614749757) by scanning the QR code of the box or entering the serial number from the `Extension Board for Sensors`.  
    For more information, please follow the instructions here [Get the Certificate from the OPTIGA™ Trust M with Infineon Toolbox](#get-the-certificate-from-the-optiga-trust-m-with-infineon-toolbox)
    * Get it offline for your device via a serial connection to a connected and [programmed](/patch/README.md) evaluation board during start-up.  
    For more information, please follow the instructions here [Get the Certificate from the OPTIGA™ Trust M with a Serial Connection](#get-the-certificate-from-the-optiga-trust-m-with-a-serial-connection)

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

1. During AWS infrastructure deployment, the page with the Kibana Dashboard opens automatically in your default browser.  
Links to your Kibana Dashboard were also saved to `kibana.txt` file in the project directory `./patch/credentials`.

2. Open the Kibana dashboard landing page and create an account by clicking `Sign up` and providing the details:  
![](/docs/00_Images/KibanaDashboard_Register.png)

3. During registration, a verification code will be sent to the provided mailbox.  
Provide this code during registration in the Kibana Dashboard.

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

Upon completion of [Kibana Dashboard Setup](#kibana-dashboard-setup), data from 8 sensors are displayed in the Kibana Dashboard (graphs quantity however is 11 as the DPS368 pressure sensors are combined and measure temperature and pressure).

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

## Technologies and Libraries
This is the list of technologies that were used for developing this stack.
However, for deploying it to AWS not all of them are required. 

* Java
* Maven
* AWS CLI
* CDK
* NPM
* Python

## Known Problems and Support
Currently, there are no known problems or limitations. 

**Note**: Please open an issue as part of this repository if you need help or support with specific problems.

## License
This repository is licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License Agreement V1.0.  
The EVAL_XMC47_PREDMAIN_AA Evaluation Software License Agreement can be found in the `LICENSE.txt` file at the root of the repository or here:

[LICENSE](/LICENSE.txt)

This repository contains software components licensed under 3rd party licenses or Open Source Software (OSS) as part of this software package. 
The respective license files are part of the software components and/or referenced in the source files.

Details on how to obtain the licenses are provided as part of the software components.

Please contact Infineon Technologies AG for questions regarding the software licensing.