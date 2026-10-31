IoT-Based Stress Monitoring System Using ESP32 and Machine Learning

An IoT and Machine Learning project designed to demonstrate stress-level estimation using heart-rate and temperature parameters. The project combines ESP32-based hardware development, sensor simulation, machine learning classification, and a web-based monitoring dashboard.

<p align="center">
  <a href="https://iot-based-stress-level-sensor-aditi.streamlit.app/">
    <strong>🚀 Live Dashboard</strong>
  </a>
  &nbsp; | &nbsp;
  <a href="https://wokwi.com/projects/478408079586210817">
    <strong>🔬 Wokwi Simulation</strong>
  </a>
</p>

📌 Table of Contents

Project Overview

Problem Statement

Objectives

Key Features

System Architecture

Hardware Requirements

Software and Technologies

Project Structure

Working Methodology

Machine Learning Workflow

Web Dashboard

Simulation

Installation and Setup

Results and Current Status

Limitations

Future Scope

Applications

Conclusion

Project Links

📖 Project Overview

Stress can influence physiological parameters such as heart rate and body temperature. Monitoring these parameters can help demonstrate how sensor technology and machine learning can be combined to analyze physiological data.

The IoT-Based Stress Monitoring System is a prototype project that explores the use of an ESP32 microcontroller, physiological sensors, and a machine learning classifier to estimate stress categories.

The project includes:

ESP32 firmware development using PlatformIO.

Temperature monitoring using a DS18B20 sensor.

Heart-rate and pulse-signal sensing using a MAX30102 sensor.

OLED display integration.

A machine learning model for classifying readings into Low, Medium, and High categories.

A Streamlit dashboard for visualizing readings and model predictions.

Wokwi simulation for demonstrating selected hardware components.

The current online dashboard operates in simulation mode and generates demonstration readings in software. Live transmission of readings from the physical ESP32 to the deployed dashboard remains future work.

🎯 Problem Statement

Stress monitoring can involve observing physiological indicators and interpreting their changes over time. Manual observation alone may not provide a convenient way to visualize patterns in collected measurements.

This project explores a prototype approach that combines embedded systems, sensor data, machine learning, and data visualization to demonstrate how physiological measurements can be processed and classified.

The system is intended for educational and research purposes. It is not a medical diagnostic or clinically validated stress-detection device.

🎯 Objectives

Develop an ESP32-based prototype for acquiring physiological sensor measurements.

Explore heart-rate and temperature monitoring.

Display sensor information through an OLED interface.

Develop a machine learning classification workflow using heart-rate and temperature features.

Visualize readings, trends, and predicted categories through a web dashboard.

Simulate selected hardware functionality using Wokwi.

Demonstrate the integration of embedded systems, IoT concepts, machine learning, and web-based visualization.

✨ Key Features

ESP32-based development: Embedded firmware designed for the ESP32 development board.

Temperature sensing: DS18B20 sensor integration in the prototype.

Pulse sensing: MAX30102 sensor included in the hardware design.

OLED interface: Displays information from supported sensor modules.

Machine learning classification: Demonstrates Low, Medium, and High category predictions.

Interactive dashboard: Streamlit controls for the number of simulated samples and simulation seed.

Data visualization: Heart-rate trends and other monitoring information.

Simulation support: Wokwi project for demonstrating selected hardware components.

Online deployment: Publicly accessible Streamlit dashboard.

🏗️ System Architecture

The project is organized into four main components.

       PHYSIOLOGICAL SENSOR INPUTS
       ┌──────────────────────────┐
       │       MAX30102           │
       │   Pulse / PPG Sensor     │
       ├──────────────────────────┤
       │       DS18B20            │
       │ Temperature Sensor       │
       └─────────────┬────────────┘
                     │
                     ▼
       ┌──────────────────────────┐
       │       ESP32 Board        │
       │ Sensor Reading and       │
       │ Embedded Processing      │
       └─────────────┬────────────┘
                     │
            ┌────────┴────────┐
            ▼                 ▼
   ┌────────────────┐  ┌────────────────┐
   │   OLED Display │  │ Future Wi-Fi   │
   │ Local Output   │  │ Data Transfer  │
   └────────────────┘  └────────┬───────┘
                                │
                                ▼
                     ┌────────────────────┐
                     │ Data Processing    │
                     │ and ML Classifier  │
                     └─────────┬──────────┘
                               │
                               ▼
                     ┌────────────────────┐
                     │ Streamlit Dashboard│
                     │ Trends and Results │
                     └────────────────────┘

Implementation note: The diagram represents the intended overall system architecture. The current deployed dashboard uses simulated software-generated readings; the complete physical sensor-to-dashboard communication pipeline has not yet been implemented.

🔧 Hardware Requirements

Component

Purpose

ESP32 development board

Microcontroller for embedded processing and Wi-Fi capability

MAX30102 pulse sensor

Pulse waveform sensing and heart-rate estimation

DS18B20 temperature sensor

Temperature measurement

SSD1306 OLED display

Local display of readings and system information

Breadboard

Prototype circuit assembly

Jumper wires

Electrical connections

4.7 kΩ resistor

Pull-up resistor for the DS18B20 data line, where required by the circuit

Hardware Status

The components are part of the planned hardware prototype. Successful software compilation and partial Wokwi simulation do not establish that all sensors are functioning correctly in the physical circuit.

In particular, the MAX30102 sensor has previously failed initialization during hardware testing, so its physical operation requires further verification.

💻 Software and Technologies

Technology

Purpose

C++

ESP32 firmware development

PlatformIO

Embedded development and firmware compilation

Arduino framework

ESP32 firmware environment

Python

Machine learning and dashboard development

Streamlit

Interactive web dashboard

Pandas

Data handling and processing

NumPy

Numerical operations

Scikit-learn

Machine learning model training and evaluation

Joblib

Saving and loading the trained model

Wokwi

Online hardware simulation

Git and GitHub

Version control and source-code hosting

Streamlit Community Cloud

Dashboard deployment

Embedded Libraries

The firmware project uses libraries for supported sensor and display components, including:

Wire

OneWire

DallasTemperature

Adafruit GFX

Adafruit SSD1306

SparkFun MAX3010x Sensor Library

📂 Project Structure

ESP32_Stress_Monitor/
│
├── dashboard/
│   ├── app.py
│   └── requirements.txt
│
├── data/
│   └── sample_stress_data.csv
│
├── include/
│   └── README
│
├── lib/
│   └── README
│
├── ml/
│   ├── train_model.py
│   └── stress_model.joblib
│
├── src/
│   └── main.cpp
│
├── test/
│   └── README
│
├── wokwi/
│   ├── diagram.json
│   ├── library.txt
│   ├── sketch.ino
│   └── wokwi.toml
│
├── platformio.ini
├── .gitignore
└── README.md

Folder descriptions:

dashboard/: Streamlit dashboard and Python dependencies.

data/: Sample dataset used for model training.

ml/: Model training script and saved model.

src/: ESP32 firmware source code.

wokwi/: Simulation configuration and source files.

include/ and lib/: PlatformIO project directories.

test/: Directory reserved for tests.

platformio.ini: PlatformIO board, framework, and build configuration.

⚙️ Working Methodology

1. Sensor Data Acquisition

The intended hardware prototype uses the ESP32 to interface with physiological sensors.

The MAX30102 measures optical pulse signals that can be processed to estimate heart rate. The DS18B20 measures temperature.

Reliable measurements depend on correct wiring, sensor initialization, signal processing, and appropriate testing.

2. Data Processing

The current sample dataset contains these features:

Feature

Description

heart_rate

Heart rate in beats per minute (BPM)

temperature

Temperature value in degrees Celsius

stress_level

Demonstration target label: Low, Medium, or High

The sample dataset contains synthetic demonstration values rather than a validated collection of physiological measurements.

3. Machine Learning

A Random Forest classifier is trained using the sample data. The trained model is saved to:

ml/stress_model.joblib

The dashboard loads the saved model and generates predictions from its input features.

4. Visualization

The Streamlit dashboard displays simulated readings, the predicted category, and graphical trends.

The dashboard provides an accessible way to demonstrate the software workflow without requiring the physical hardware to be connected to the online application.

🤖 Machine Learning Workflow

The current machine learning workflow is:

Sample CSV Dataset
        │
        ▼
Data Loading
        │
        ▼
Feature and Target Selection
        │
        ▼
Training and Test Split
        │
        ▼
Random Forest Classifier
        │
        ▼
Model Evaluation
        │
        ▼
Save Model Using Joblib
        │
        ▼
Load Model in Streamlit
        │
        ▼
Predict Demonstration Categories

Model Features

Algorithm: Random Forest Classifier

Input features: Heart rate and temperature

Target variable: stress_level

Output classes: Low, Medium, High

Model file: ml/stress_model.joblib

Training script: ml/train_model.py

Model Evaluation

An initial training run reported 100% demonstration accuracy on a test set containing only three samples from the synthetic dataset.

This result is not sufficient evidence of real-world predictive performance. The dataset is extremely small and synthetic, and the reported accuracy should not be interpreted as proof that the system can accurately detect human stress.

Further evaluation requires a larger, appropriate dataset, reliable ground-truth labels, and a more rigorous validation procedure.

📊 Web Dashboard

The project includes a deployed Streamlit dashboard.

Open the dashboard:
https://iot-based-stress-level-sensor-aditi.streamlit.app/

Dashboard Features

Latest simulated heart-rate reading.

Latest simulated temperature reading.

ML-predicted demonstration category.

Heart-rate trend visualization.

Adjustable number of demonstration samples.

Adjustable simulation seed.

Additional data visualizations and prediction information.

Dashboard Screenshot

Add your dashboard screenshot to:

docs/screenshots/dashboard.png

Then display it in this README using:

![IoT Stress Monitoring Dashboard](docs/screenshots/dashboard.png)

🔬 Simulation

The project includes a Wokwi simulation for selected ESP32 hardware components.

Open the simulation:
https://wokwi.com/projects/478408079586210817

The previously tested simulation demonstrated:

ESP32 development board operation.

OLED initialization.

DS18B20 initialization.

Temperature readings in the serial monitor.

Example simulation output:

OLED initialized successfully!
DS18B20 initialized.
IoT Stress Monitor Started!
Temperature: 25.0 C

These messages describe the previously observed simulation output. They do not establish successful operation of every sensor or the complete physical hardware system.

Simulation Screenshot

Add your Wokwi screenshot to:

docs/screenshots/wokwi_simulation.png

Then display it using:

![ESP32 Wokwi Simulation](docs/screenshots/wokwi_simulation.png)

🚀 Installation and Setup

Prerequisites

Install the following tools:

Python

Git

Visual Studio Code

PlatformIO extension for ESP32 firmware development

1. Clone the Repository

git clone https://github.com/aditikarn-analyst/IOT-based-Stress-level-sensor.git

Navigate to the project directory:

cd IOT-based-Stress-level-sensor

2. Create a Python Virtual Environment

Windows PowerShell:

python -m venv venv

Activate the environment:

.\venv\Scripts\Activate.ps1

3. Install Dashboard Dependencies

From the repository root, run:

pip install -r dashboard/requirements.txt

4. Run the Dashboard Locally

From the repository root:

python -m streamlit run dashboard/app.py

Streamlit will display a local address in the terminal. Open that address in your browser.

5. Train the Machine Learning Model

If you want to retrain the model, run:

python ml/train_model.py

The training script should create or update:

ml/stress_model.joblib

The dashboard requires this model file to be available.

6. Build the ESP32 Firmware

Open the project in Visual Studio Code with PlatformIO installed.

Build the firmware from the VS Code terminal:

python -m platformio run

A successful build confirms that the firmware compiles for the configured board. It does not guarantee that the physical sensors are wired correctly or operating successfully.

📈 Results and Current Status

The project has achieved the following milestones:

ESP32 firmware compilation completed successfully.

OLED and DS18B20 operation demonstrated in Wokwi simulation.

A sample dataset created for the machine learning workflow.

A Random Forest model trained and saved using Joblib.

A Streamlit dashboard developed to visualize simulated readings and predictions.

The dashboard deployed successfully using Streamlit Community Cloud.

Source code uploaded to GitHub.

Current Implementation Status

Component

Status

ESP32 firmware compilation

Completed

OLED and DS18B20 simulation

Demonstrated

Sample dataset

Created

ML model training

Completed on synthetic data

Streamlit dashboard

Deployed

GitHub repository

Available

MAX30102 physical sensor operation

Requires further verification

Live physical sensor integration with the dashboard

Not implemented

Real-world ML validation

Not completed

⚠️ Limitations

Synthetic data: The training dataset is small and uses demonstration values.

Limited validation: The reported test accuracy is based on very few test samples.

Simulated dashboard: The online dashboard does not currently receive live readings from the physical ESP32.

Hardware verification: Physical operation of all sensor modules has not been confirmed.

Stress estimation: Heart rate and temperature alone are insufficient to establish a reliable clinical stress assessment.

Medical use: The prototype has not been clinically validated and must not be used for medical diagnosis or treatment decisions.

🔮 Future Scope

Potential improvements include:

Verify and integrate the physical MAX30102 sensor.

Establish reliable data acquisition from all hardware components.

Transmit ESP32 readings to the dashboard over Wi-Fi.

Add timestamped sensor data storage.

Collect a larger and appropriately labelled dataset.

Improve the model using suitable validation methods.

Investigate additional physiological features where appropriate.

Add sensor-error handling and data-quality checks.

Evaluate the system under varied operating conditions.

Improve dashboard usability and monitoring capabilities.

These are potential future enhancements and are not claims about existing functionality.

🌍 Applications

The project demonstrates concepts that may be useful in educational and prototype research involving:

IoT-based physiological monitoring.

Embedded systems development.

Sensor data acquisition.

Machine learning classification.

Real-time data visualization.

Health-monitoring system prototyping.

Any application involving human health requires appropriate validation, privacy safeguards, and clinical evaluation before practical deployment.

📝 Conclusion

The IoT-Based Stress Monitoring System demonstrates how embedded hardware development, physiological sensor concepts, machine learning, and web-based visualization can be combined into a single project.

The work includes an ESP32 firmware project, a Wokwi simulation, a sample-data machine learning pipeline, and a deployed Streamlit dashboard.

Although the dashboard currently uses simulated readings and the model is trained on synthetic data, the project provides a foundation for further development and evaluation of an integrated IoT monitoring prototype.

🔗 Project Links

GitHub Repository: https://github.com/aditikarn-analyst/IOT-based-Stress-level-sensor

Live Streamlit Dashboard: https://iot-based-stress-level-sensor-aditi.streamlit.app/

Wokwi Simulation: https://wokwi.com/projects/478408079586210817

👩‍💻 Author

Aditi Karn

GitHub: @aditikarn-analyst

Disclaimer: This project is an educational prototype. Its predictions are based on synthetic demonstration data and are not medically validated.