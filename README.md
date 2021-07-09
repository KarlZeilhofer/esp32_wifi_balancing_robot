# ESP32_Wifi_Balancing_Robot
 An Self Balancing Robot based ESP32 can be controlled use Android over Wifi

This self-balancing robot is based on [B-Robot][https://www.jjrobots.com/much-more-than-a-self-balancing-robot/], which is open sourced on jjrobots. Thanks to the article by "[ghmartin77][https://www.jjrobots.com/community/migrated-forums-4-jjrobots-b-robot/esp32-port-of-b-robot_evo2-code-3/]" posted on the B-Robot forum.

# Toolchain for Arduino
## Arduino IDE
  * File, Preferences, Additional Boards Manater URLs: https://dl.espressif.com/dl/package_esp32_index.json
  * Tools, Board, Boards Manger: Install "ESP32"
  * Tools, Board, ESP32 Arduino, ESP32 Dev Module

## Linux Terminal
  * sudo apt install python3-serial python3-is-python
  * cd ~/Arduino/libraries
  * git clone https://github.com/me-no-dev/ESPAsyncWebServer.git
  * git clone https://github.com/me-no-dev/AsyncTCP.git
  * mkdir ~/git
  * cd  ~/git
  * git clone https://github.com/KarlZeilhofer/esp32_wifi_balancing_robot.git


