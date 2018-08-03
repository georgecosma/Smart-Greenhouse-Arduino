# Smart Greenhouse Arduino

This code is part of my project named "Smart Greenhouse". It is the source code for the Arduino controller and its sensors and modules and it's used for both the system automation and control over the internet. Due to its internet connectivity, collected data such as: luminosity, temperature and soil moisture are visible from a web interface. Through the interface, the system's water pumps, air vent and fans can also be controlled remotely. 

<p align="center">
  <img width="600" height="300" src="https://i.imgur.com/XhnbyF9.png">
</p>

## Hardware components 
* Sensors: soil moisture, luminosity, temperature
* Modules: water pumps, fans, air vent, wifi module ESP8266

## Getting Started

In order to upload the code on the Arduino board, you must use the Arduino IDE (link attached in the below section). The pins and connections configuration is also presented in the code. To run properly, the .ino file must be contained by a folder with the same name.

### Prerequisites

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)


## Acknowledgments

* [Wifi module connection link](https://create.arduino.cc/projecthub/circuito-io-team/simple-arduino-uno-esp-8266-integration-dba10b)
* [Arduino playground](https://playground.arduino.cc/) - all the resouces needed for the modules connections and software commands
