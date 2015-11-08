# esp-cheer-lights
CheerLights for ESP8266 Arduino IDE

This sketch gets the last color via HTTP GET requests from the ThingSpeak
CheerLights channel then changes the LEDs to that color.

## CheerLights
See the following for more info on CheerLights

http://cheerlights.com/

## ThingSpeak
CheerLights uses ThingSpeak to scan for @cheerlights and the color.

https://thingspeak.com/channels/1417
http://api.thingspeak.com/channels/1417/field/2/last.txt

The last value is the RGB color in hexadecimal.

## ESP8266 Arduino IDE
See the following for more info on the ESP8266 Arduino IDE

* https://github.com/esp8266/Arduino
* http://www.esp8266.com/

NOTE: This program requires the ESP8266 staging version dated Sep 30, 2015 or newer. In the IDE boards manager, the version string is currently "1.6.5-1160-gef26c5f".

* https://github.com/esp8266/arduino#staging-version-

## NeoPixelBus ws281x/NeoPixel driver
See the following for ESP8266 ws281x/NeoPixel driver.

https://github.com/Makuna/NeoPixelBus

## Hardware used for testing

* Adafruit Huzzah ESP8266 breakout board but any ESP8266 board should work.
* Adafruit NeoPixel 8 ws281x LED stick but any ws281x LEDs should work.
* TI 74AHCT125 3V3 to 5V level shifter
* 5V 1A power supply sufficient is for the ESP8266 and 8 LEDs but you need
a bigger power supply for more LEDs. See Adafruit tutorials for advice on
powering large numbers of LEDs.
