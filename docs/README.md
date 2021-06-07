# Documentation Overview <!-- omit in toc -->

## Table of Content <!-- omit in toc -->
- [Introduction](#introduction)
- [Organization of the Documentation](#organization-of-the-documentation)
- [Quick Start Guide](#quick-start-guide)
- [Hardware Documentation](#hardware-documentation)
- [Software Firmware Development Documentation](#software-firmware-development-documentation)
- [Software Documentation](#software-documentation)
- [AWS Infrastructure Setup](#aws-infrastructure-setup)
- [AWS Cloud Architecture](#aws-cloud-architecture)
- [Dashboard Overview](#dashboard-overview)
- [Known Problems and Support](#known-problems-and-support)

## Introduction
This document provides information about the documentation of the XENSIV™ Predictive Maintenance Evaluation Kit EVAL_XMC47_PREDMAIN_AA.  
For a generic description of the features and benefits, please compare the [README.md](/README.md) file from the repository root.

## Organization of the Documentation
Overall, the documentation is divided into the following sections:

* README.md
* Quick Start Guide
* Software Documentation
* AWS Infrastructure Documentation
* Hardware Documentation

## Quick Start Guide
**Link to the [Quick Start Guide](./00_QuickStart.md)**

The quick start document provides a step-by-step guide on how to quickly setup an instance of the kit.  
It provides information on how to deploy the AWS infrastructure with an automatized process.  
Moreover, based on a precompiled `.hex` file, it allows the user to flash the XMC700 microcontroller of the EVAL_XMC47_PREDMAIN_AA kit.

All users who want to have a first, quick setup should start from this document.
If a user wants to get full development access, the following sections provide additional information. 

## Hardware Documentation
**Link to the [Hardware Documentation](./02_Hardware/01_Overview.md)**

The hardware documentation provides all documentation of the hardware including board descriptions, simplified schematics and layout.  
It provides information on the XMC700 Relax Kit, the Extension Board for Sensors, all Satellite Boards as well as Sensor boards.  
Moreover, the basic setup of the kit with a [step-by-step guide](./02_Hardware/02_Setup.md) is also described there.

All users who want to have full details about the hardware and get a better understanding of it, should start from this document.

## Software Firmware Development Documentation
**Link to the [Software Firmware Development Documentation](./03_Software/01_SoftwareDevelopment.md)**

The Software Development Documentation provides documentation of software infrastructure setup.

All users who want to start software development and modify the firmware, should start from this document.

## Software Documentation
**Link to the [Software Documentation](./03_Software/02_Software.md)**

The Software Documentation provides documentation of the Amazon FreeRTOS firmware running on the XMC700 Relax Kit.
The XMC700 Relax Kit is the underlying microcontroller board that is utilized for the EVAL_XMC47_PREDMAIN_AA kit.

All users who want to have insights into the software running on the XMC700 Relax Kit and get a deeper understanding of it, should start from this document.

## AWS Infrastructure Setup
**Link to the [AWS Infrastructure Setup](./01_AWS/01_AWSInfrastructure.md)**

The AWS infrastructure setup provides a step-by-step guide on how to setup the AWS infrastructure based on a CDK script.  
It provides information on the deployment steps for the AWS infrastructure with a step-by-step guide for all relevant parts.

All users who want to have full access to the deployment options and get a deeper understanding of the AWS infrastructure deployment process, should start from this document.

## AWS Cloud Architecture
**Link to the [AWS Cloud Architecture Documentation](./01_AWS/02_AWSArchitecture.md)**

The AWS architecture documentation provides an overview on the AWS infrastructure and implemented services.  
It provides information on the utilized AWS infrastructure and services with a complete system overview.

All users who want to have full access to the Cloud development options and get a deeper understanding of the AWS Cloud infrastructure, should start from this document.

## Dashboard Overview
**Link to the [Dashboard Overview](./01_AWS/03_KibanaDashboard.md)**

The Dashboard Overview provides an overview on the Kibana dashboard.  
It provides information on the main concepts and describes existing objects that are created by the CKD script.

All users who want to have full access to the dashboard development options and get a deeper understanding of it, should start from this document.

## Known Problems and Support
Currently, there are no known problems or limitations. 

**Note:** please open an issue as part of this repository if you need help or support with specific problems.