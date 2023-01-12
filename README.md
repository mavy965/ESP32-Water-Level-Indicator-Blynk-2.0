
# [ESP32] Water Level Indicator

A brief description of what this project does and who it's for


## Parts Used

 - [ESP32](https://www.espressif.com/en/products/socs/esp32)
 - [HC-SR04 Ultrasonic Sensor](https://web.eece.maine.edu/~zhu/book/lab/HC-SR04%20User%20Manual.pdf)
 - 5VDC Relay
 - Water Pump



## Tokens


`BLYNK_TEMPLATE_ID`

`BLYNK_DEVICE_NAME`

`BLYNK_AUTH_TOKEN`


## Changes required before using ino file

- Tokens
- GPIO Pins
- TANK_ZERO, TANK_MAX
## Blynk Dashboard Setup

1. Go to https://blynk.cloud and create a new account. Log into your account.
2. Create a template named "Water Tank".
3. In the datastream tab create two virtual data streams:
    ```
    V0:
    Name: Water Pump Switch
    Data Type: Integer
    ```
    ```
    V4:
    Name: Water Level
    Data Type: Double
    Max: 100
    Units: Percentage
    ```
4. Go to the web dashboard tab and create a suitable web dashboard. For that, I used a button and one gauge widget.
5. Assign Datastream V4 to guage and V0 to Switch.
6. For Switch, change OFF value to 1 and ON value to 0.
7. Get BLYNK_AUTH_TOKEN token from mail, BLYNK_TEMPLATE_ID and BLYNK_DEVICE_NAME from Info tab in dashboard.
## Screenshots

- Web Dashboard: https://i.imgur.com/BMVSPYp.png
- Android App: https://i.imgur.com/LeixN6b.jpeg

