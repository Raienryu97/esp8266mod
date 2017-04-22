**RYUU**
=========

### **About Project**
This repository is a documentation of the codes me, Pranav Cherukupalli and my team mate Vamsy Durvasula have developed for a college project.
The overview of our work was to create a smart immersion heater with a user module that can help remotely control the temperature until which water can be heated to.
The code probably isn't the best, but it sure works ;)

### **Ingredients Used**

* [ESP8266 ESP-12E](http://amzn.in/2BH7R6l) (x2)
* [KG186 5V One Channel Relay](http://amzn.in/6Ym1z7B)
* [DS18B20 Temperature Sensor](http://amzn.in/a15qQW3)
* [16x2 I2C LCD](http://amzn.in/dAuNAGC)
* Push Buttons (x2)
* Misc electronic components like resistors, jumper wires etc

For full documentation related to ESP-12E please visit [this link](https://github.com/nodemcu/nodemcu-devkit-v1.0).

### **Brief Working Model**
There are two modules to this project, the _User Module_ and the _Sensor Module_. The _Sensor Module_ is the MCU that is linked to the temperature sensor. It reads the current temperature of water and at regular intervals sends it to the MCU located in the _User Module_.

The _User Module_ has an LCD screen and two push buttons attached to it through it's GPIOs. This module receives the temperature sent by the _Sensor Module_ and displays it to the user on the LCD panel. The user can then either increase or decrease temperature using the pushbuttons and leave it at a temperature of his choice. The _User Module_ sends the _Sensor Module_ the user required temperature.

Once the temperature reaches the required one, the relay turns off the heating and both the ESPs go to sleep until required next time, where they must be then reset.

### **Credits**
We have used a few open source libraries for our project.
Special thanks to them for making our work easier :)

* [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C)
* [One Wire](https://github.com/PaulStoffregen/OneWire)
* [Dallas Temperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)

###### _PS_
Ryuu in japanese means Dragon. Since our projects deals with ~~burning~~ heating stuff up, we decided to go with this name. My github username being similar is just a coincidence.   
