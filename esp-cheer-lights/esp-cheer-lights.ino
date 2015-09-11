/****************************
The MIT License (MIT)

Copyright (c) 2015 by bbx10node@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************/

// CheerLights for the ESP8266 using the Arduino IDE

#include <ESP8266WiFi.h>
#include <NeoPixelBus.h>

// The Adafruit NeoPixel stick has 8 LEDs. Change this to match the number
// of LEDs in your string.
const int NUM_LEDS = 8;

// The Adafruit Huzzah ESP8266 board GPIO#2 is connected to the NeoPixel
// data in pin.
const int LED_PIN = 2;

NeoPixelBus strip = NeoPixelBus(NUM_LEDS, LED_PIN);

const char ssid[]     = "xxxxxxx";
const char password[] = "yyyyyyyyyyyyy";

const char host[] = "api.thingspeak.com";

void setup()
{
    Serial.begin(115200);

    strip.Begin();
    strip.Show(); // Initialize all pixels to 'off'

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

static unsigned long LastColor = 0;

void loop()
{
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/channels/1417/field/2/last.txt";

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
            "Host: " + host + "\r\n" +
            "Connection: close\r\n\r\n");

    // Read all the lines of the reply from server and scan for hex color
    while(client.available()) {
        unsigned long color;
        String line = client.readStringUntil('\n');
        // Example line: #808182
        if ((line[0] == '#') && (line.length() == 8)) {
            int r, g, b;
            Serial.println(line);
            color = strtoul(line.c_str()+1, NULL, 16);
            // Update LEDs only when color changes
            if (color != LastColor) {
                LastColor = color;
                Serial.println(color, HEX);
                r = (color & 0xFF0000) >> 16;
                g = (color & 0x00FF00) >>  8;
                b = (color & 0x0000FF);
                strip.ClearTo(r, g, b);
                strip.Show();
            }
        }
    }

    // ThingSpeak does not allow updates more often than every 15 seconds.
    delay(15000);
}
