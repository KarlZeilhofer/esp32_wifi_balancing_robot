Lemming 2 - Firmware
==============
ESP32 Wifi BalancingRobot
-----------------------------


This self-balancing robot is based on [B-Robot][https://www.jjrobots.com/much-more-than-a-self-balancing-robot/], which is open sourced on jjrobots. Thanks to the article by "[ghmartin77][https://www.jjrobots.com/community/migrated-forums-4-jjrobots-b-robot/esp32-port-of-b-robot_evo2-code-3/]" posted on the B-Robot forum.

# Toolchain for Arduino
## Arduino IDE
  * File, Preferences, Additional Boards Manater URLs: https://dl.espressif.com/dl/package_esp32_index.json
  * Tools, Board, Boards Manger: Install "ESP32"
  * Tools, Board, ESP32 Arduino, ESP32 Dev Module
  * Tools, Upload Speed: 460800

## Linux Terminal
  * sudo apt install python3-serial python-is-python3
  * cd ~/Arduino/libraries
  * git clone https://github.com/me-no-dev/ESPAsyncWebServer.git
  * git clone https://github.com/me-no-dev/AsyncTCP.git
  * git clone https://github.com/adafruit/Adafruit-GFX-Library.git
  * git clone https://github.com/adafruit/Adafruit_SSD1306.git
  * git clone https://github.com/adafruit/Adafruit_BusIO.git
  * mkdir ~/git
  * cd  ~/git
  * git clone https://github.com/KarlZeilhofer/esp32_wifi_balancing_robot.git


