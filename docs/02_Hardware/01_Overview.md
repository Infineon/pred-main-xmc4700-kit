# Hardware Documentation Overview <!-- omit in toc -->

## Table of Content <!-- omit in toc -->
- [Introduction](#introduction)
- [Organization of Hardware Documentation](#organization-of-hardware-documentation)
- [Supported Sensors](#supported-sensors)
- [Additional Information and Material](#additional-information-and-material)
- [Important Notes and Warnings](#important-notes-and-warnings)

## Introduction
Overall, the EVAL_XMC47_PREDMAIN_AA kit consists of the following elements:

* 1 XMC4700 Relax Kit as mainboard
* 1 Extension Board for Sensors to be combined with XMC4700 Relax Kit
* 7 Satellite Boards to be connected to Extension Board for Sensors
* 13 Sensor Boards to be connected to Satellite Boards

The Satellite Boards are each implementing specific hardware interfaces, e.g. as I2C Satellite Board or as SPI Satellit Board.  
The respective Satellite Boards are connected via twisted-pair Ethernet cabling and RJ45 jacks with the Extension Board for Sensors.  
Please note that crossover cabling cannot be used as the connections are point-to-point between the RJ45 jacks.  

**Important Notes and Warnings:** please read the important notes and warnings [here](#important-notes-and-warnings) before continuing.

## Organization of Hardware Documentation
The hardware documentation is organized in separate chapters and paragraphs.
An overview of the basic hardware setup and step-by-step guide can be found here:

* [Step-by-step setup guide](./02_Setup.md)

Every board has an own sub-page summarizing all details including layout and schematics.
The documentation of the boards is organized as follows:

* [XMC4700 Relax Kit](./10_XMC4700RelaxKit.md)
* [Extension Board for Sensors](./03_ExtensionBoard.md)
* [Analog Satellite Board](./04_AnalogSatelliteBoard.md) including analog sensors
* [SPI Satellite Board](./05_SPISatelliteBoard.md) including SPI sensors
* [I2C Satellite Board](./06_I2CSatelliteBoard.md) including I2C sensors
* [I2S Satellite Board](./07_I2SSatelliteBoard.md) including I2S sensors
* [GPIO Satellite Board](./08_GPIOSatelliteBoard.md) including sensors with GPIO interface
* [UART Satellite Board](./09_UARTSatelliteBoard.md) for UART interface

## Supported Sensors
An overview of all supported sensors is provided in the following table:

| #   | Sensor         | Description                     | Hardware Interface | Note                               |
| --- | -------------- | ------------------------------- | ------------------ | ---------------------------------- |
| 1   | DPS368         | Pressure and temperature sensor | I2C &amp; GPIO     | Address 0x77                       |
| 2   | DPS368         | Pressure and temperature sensor | I2C &amp; GPIO     | Address 0x76                       |
| 3   | TLI493D-W2BW   | 3D magnetic sensor              | I2C &amp; GPIO     | Address A0 variant                 |
| 4   | DPS368         | Pressure and temperature sensor | SPI                | 4 Wire SPI                         |
| 5   | DPS368         | Pressure and temperature sensor | SPI                | 4 Wire SPI                         |
| 6   | DPS368         | Pressure and temperature sensor | SPI                | 4 Wire SPI                         |
| 7   | TLI4971-A025T5 | Magnetic current sensor         | Analog &amp; GPIO  | Single-ended and OCD1/OCD2         |
| 8   | TLI4971-A025T5 | Magnetic current sensor         | Analog &amp; GPIO  | Single-ended and OCD1/OCD2         |
| 9   | TLI4971-A025T5 | Magnetic current sensor         | Analog &amp; GPIO  | Single-ended and OCD1/OCD2         |
| 10  | TLE4997A8      | Linear hall sensor              | Analog             | Mapping 5 V to 3.3 V analog output |
| 11  | IM69D130       | MEMS Microphone                 | I2S                | Stereo mode – left                 |
| 12  | IM69D130       | MEMS Microphone                 | I2S                | Stereo mode – right                |
| 13  | TLE4961-3K     | Hall effect latch               | GPIO               |                                    |
| 14  | TLE4964-4M     | Hall switch                     | GPIO               |                                    |
| 15  | TLE4961-1K     | Hall effect latch               | GPIO               |                                    |
| 16  | TLE4913        | Hall switch                     | GPIO               |                                    |
| 17  | TLI4966G       | Double Hall sensor              | GPIO               |                                    |

Additional documentation and guides for the sensors is provided as part of the respective board documentation.  
Moreover, the respective product pages are listed below:

**Product Pages of Sensors**
* [DPS368](https://www.infineon.com/cms/en/product/sensor/pressure-sensors/pressure-sensors-for-iot/dps368/)
* [TLI493D-W2BW A0](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tli493d-w2bw-a0/)
* [TLI4971-A025T5-U-E0001](https://www.infineon.com/cms/en/product/sensor/current-sensors/tli4971-a025t5-u-e0001/)
* [TLE4997A8](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/linear-halls/tle4997a8/)
* [IM69D130](https://www.infineon.com/cms/en/product/sensor/mems-microphones/mems-microphones-for-consumer/im69d130/)
* [TLE4961-3K](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/hall-switches/tle4961-3k/)
* [TLE4964-4M](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/hall-switches/tle4964-4m/) 
* [TLE4961-1K](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/hall-switches/tle4961-1k/) 
* [TLE4913](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/hall-switches/tle4913/)
* [TLI4966G](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/hall-switches/tli4966g/)

## Additional Information and Material
Please create an issue as part of this repository to get support (or contact your local Infineon representative/support).
PCB design files and additional documentation is available on request.

## Important Notes and Warnings
The use of this kit is strictly only for your **evaluation usage**.  
By operating the kit, you agree to only use this kit for **such evaluation**.  
If you do not agree to this term, do not operate the kit.

Please ensure proper voltage/current levels and power limits when operating this kit.  
Although the evaluation kit has implemented protection circuitry for overcurrent and ESD events, proper safety measures have to be taken into account.

Always validate the operating conditions of the kit and perform propoer measurements to ensure that the kit stays within safe operating conditions.