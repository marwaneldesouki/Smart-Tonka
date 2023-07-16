


# Smart Tonka

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![GitHub Stars](https://img.shields.io/github/stars/marwaneldesouki/Smart-Tonka.svg)](https://github.com/marwaneldesouki/Smart-Tonka/stargazers)
[![GitHub Issues](https://img.shields.io/github/issues/marwaneldesouki/Smart-Tonka.svg)](https://github.com/marwaneldesouki/pSmart-Tonka/issues)

## INTRODUCTION
This Project introduces a parallel parking car that utilizes an Arduino UNO microcontroller board and various components to enhance the parking process. The system incorporates four ultrasonic sensors, an L298 H-bridge motor driver, a Bluetooth module, four lithium batteries, four DC motors, and four wheels.

## Methodology
The parallel parking system for the vehicle operates as follows: Upon activating the parking mode through the mobile application, the vehicle initiates acceleration until the right ultrasonic sensor detects the presence of the first obstacle. Subsequently, the ultrasonic sensors calculate the elapsed time until the detection of the second obstacle, ensuring that the space between the two obstacles is of sufficient width to accommodate the vehicle for parking.


Upon verification of the suitable parking space, the vehicle initiates a left rotation until the front right ultrasonic sensor detects a distance of 70 cm between the sensor and the obstacle in front. Subsequently, the vehicle proceeds to move backward until the rear ultrasonic sensors detect the presence of an obstacle behind the car.

![image](https://github.com/marwaneldesouki/Smart-Tonka/assets/37198610/d551474d-0092-476e-85c0-c3b276e2cd08)

## Components
Arduino UNO
ultrasonic x4
L298 H-bridge
Bluetooth module
Lithium battery x4
DC motors x4
Wheel x4

## Circuit Diagram
![image](https://github.com/marwaneldesouki/Smart-Tonka/assets/37198610/dc446820-3de4-4726-8c1b-7033c69f28d3)

## Mobile Application
Parking mode:to initiate the automated parkingRightLeftForwardBackward
![image](https://github.com/marwaneldesouki/Smart-Tonka/assets/37198610/144fc236-dd12-416b-a1e2-96b8533a4581)

## Conclusion
In conclusion, the parallel parking system, utilizing an Arduino UNO microcontroller and multiple components such as ultrasonic sensors, an L298 H-bridge motor driver, and a Bluetooth module, enhances parking accuracy and efficiency. The methodology involves obstacle detection, space verification, and precise movements, enabling the vehicle to perform automated parallel parking with ease.

