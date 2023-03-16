# SMA Meter Traffic Light

This project is a life traffic to indicate the energetic balance of a house with a SMA installation.

## Beerware licensed
As long as you retain this notice you can do whatever you want with this stuff. If we meet some day, and you think 
this stuff is worth it, you can buy me a beer in return.

## Hardware needed
I did the project using a UNO R3 MEGA328P to control the traffic light and an ESP8266 for the wireless communication.

![UNO-R3-MEGA328P-ESP8266.jpg](docs%2FUNO-R3-MEGA328P-ESP8266.jpg)

## Overview
Our device it's able to connect to the Wi-Fi and communicate with the SMA ENERGY METER to get our home energy balance. 
With this information the project will manage the traffic light and the screen(Pantalla) to display relevant information.
The control of the screen isn't implemented yet.

![img.png](docs/overview.png)

In the folder **src**, you can find 2 projects. 

By one hand we have the chip ESP8266 with the next responsabilities:
 - Manage the connectivity.
 - Get the energetic information.
 - Send this information as events.

By the other hand we have the AtMega328 with the next responsabilities:
 - Get and process the events.
 - Manage the status
 - Update the peripherals.

![img.png](docs/chips-responsabilities.png)

## Traffic Light Logic

This is the current logic implemented for the Traffic Light. Have in mind my solar instalation only can generate 2.5 KWh
in the best scenario. For this reason I considered relevant this ranges.

![img.png](docs/traffic-light-logic.png)

## Next Steps
This is the roadmap for the project:
- Add a how to install it in your hardware.
- Renew the SMA Meter Token every X time.(I have 4 days the project working without renew the token, maybe not needed)
- Add conections diagram.
- Use a OLED display to show information.
- See the information we can get from the SMA inverter.