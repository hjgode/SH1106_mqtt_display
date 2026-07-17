/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 by Daniel Eichhorn
 * Copyright (c) 2016 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/* 
 *  
 Libraries

  Using library ESP8266WiFi at version 1.0 in folder: .. packages/esp8266/hardware/esp8266/2.6.2/libraries/ESP8266WiFi 
  Using library ESP8266mDNS at version 1.2 in folder: .. packages/esp8266/hardware/esp8266/2.6.2/libraries/ESP8266mDNS 
  Using library pubsubclient-master at version 2.8 in folder: .. libraries/pubsubclient-master 
  Using library Wire at version 1.0 in folder: .. /packages/esp8266/hardware/esp8266/2.6.2/libraries/Wire 
  Using library ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays at version 4.6.2 in folder: .. libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays 


 *  For programming other ESP8266 modules such as ESP-12 or ESP-07, wire the pins like these:

For ESP8266
flasher pin   ESP8266 pin
VCC           VCC
GND           GND
TXD           RXD
RXD           TXD
RST           RST
GPIO0         GPIO0
CH_EN         CH_EN or CH_PD
 *  
  ESP12E Pins
  GPIO Pins

There is a total of 11 I/O pins. Therefore, these pins can perform multiple kinds of input and output functions that are interfaceable with all the TTL/CMOS devices. All GPIO pins are:

    Pin4 – GPIO16
    Pin5 – GPIO14
    Pin6 – GPIO12
    Pin7 – GPIO13
    Pin11 – GPIO9
    Pin12 – GPIO10
    Pin16 – GPIO15
    Pin18 – GPIO0
    Pin19 – GPIO4
    Pin20 – GPIO5

UART Communication Pins

The devices ESP 12E is programmable with UART communication in many IDE. Those UART pins are usable after even programming. Both pins are:

    Pin 21 – RXD0
    Pin 22 – TXD0
    Pin15 – RTS
    Pin13 – CTS
    Pin2 – TXD

ESP12E SPI Communication Pins

The module offers direct SPI communication with itself. This communication uses four pins for proper communication, which are:

    Pin12 – CS0
    Pin10 – MISO
    Pin9 – MOSI
    Pin14 – SCLK

I2C

In ESP12E some GPIO pins are useable for I2C communication. In this communication, only two pins help to communicate. One for clock and other for data. Therefore, in ESP, both are:

    Pin14 – SCL
    Pin2 – SDA

I2S

It isn’t common in every device. The I2S helps to collect, process and transmit the audio signal. The I2S uses 6 pins and in ESP 12E all I2S pins are:

    Pin12 – I2SI_DATA
    Pin13 – I2SI_BCK
    Pin14 – I2SI_WS
    Pin15 – I2SO_BCK
    Pin3 – I2SO_DATA
    Pin2 – I2SO_WS

PWM

In every controller, the ESP 12E can convert it every pin into PWM pins through programming. There are three specifics for the PWM signal. All these pins are:

    Pin12
    Pin13
    Pin15

IR Interface

The IR interface uses modulation and demodulation which requires NEC coding. The ESP12E is interfaceable using the IR interface pins and it is specific to these pins:

    Pin5 – IR_R
    Pin14 – IR_T

ADC

The device has a 10-bit ADC pin, which uses 0-1V range to convert the analog data to digital data.

    Pin2

Power and Control Pins

Power : ESP12E uses the VCC pin to power up the whole module and the ground pin to make the common ground with power supply and other devices

    Pin8 – VCC
    Pin15 – GND

Enable: The devices have an internal digital switch. The enable pin will receive the digital HIGH signal to activate the chip.

    Pin3

Reset: To reset the device the digital will help to reset it through the LOW state. The reset pin is the first pin of the module is:

    Pin1
*/

#define PIN_POWER (5)
long previousMillis = 0; 
long interval = 1000;           // interval after which to shut down (milliseconds)
long shutdown_counter=20;

String myText1;
String myText2;
String myText3;
String myText4;
String myText5;
String myText6;
String myClockText;

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
const char* ssid = "Horst1";
const char* password = "1234567890123";
const char* mqtt_server = "192.168.0.40";
WiFiClient espClient;
PubSubClient client(espClient);

 // Include the correct display library
 // For a connection via I2C using Wire include
 #include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "SH1106.h" //alis for `#include "SH1106Wire.h"`
 // For a connection via I2C using brzo_i2c (must be installed) include
 // #include <brzo_i2c.h> // Only needed for Arduino 1.6.5 and earlier
 // #include "SSD1306Brzo.h"
 // #include "SH1106Brzo.h"
 // For a connection via SPI include
 // #include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
 // #include "SSD1306Spi.h"
 // #include "SH1106SPi.h"

// Include the UI lib
#include "OLEDDisplayUi.h"

//extra font
//#include "Dialog_plain_14.h"
#include "DejaVu_Sans_Mono_14.h"
#define myFont DejaVu_Sans_Mono_14

// Include custom images
#include "images.h"

// Use the corresponding display class:

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using brzo_i2c
// D3 -> SDA    Pin2
// D5 -> SCL    Pin14
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

// Initialize the OLED display using Wire library
//SSD1306  display(0x3c, D3, D5);


// packages/esp8266/hardware/esp8266/2.6.2/variants/generic/pins_arduino.h
// #define PIN_WIRE_SDA (4)
// #define PIN_WIRE_SCL (5)
// static const uint8_t SDA = PIN_WIRE_SDA;
// static const uint8_t SCL = PIN_WIRE_SCL;

 SH1106 display(0x3c, SDA, SCL);

OLEDDisplayUi ui     ( &display );

void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  String rssi="dbm ";
  rssi+=String(WiFi.RSSI());
  display->drawString(128, 0, rssi);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 0, myClockText);
  
}

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // draw an xbm image.
  // Please note that everything that should be transitioned
  // needs to be drawn relative to x and y

  display->drawXbm(x + 34, y + 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  y*=3;
  //display->setFont(ArialMT_Plain_10);
  display->setFont(myFont);//ArialMT_Plain_16);
  
  display->drawString(0 + x, 10 + y, myText1);// "Arial 10");

  display->drawString(0 + x, 24 + y, myText2);

  //display->setFont(ArialMT_Plain_24);
  display->drawString(0 + x, 38 + y, myText3);
}

void drawFrame21(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_LEFT);//TEXT_ALIGN_CENTER);//TEXT_ALIGN_LEFT);
  //center x
  //x+=64;
  y+=3;
  //display->setFont(ArialMT_Plain_10);
  display->setFont(myFont);//ArialMT_Plain_16);
  display->drawString(0 + x, 10 + y, myText4);

  display->drawString(0 + x, 24 + y, myText5);

  //display->setFont(ArialMT_Plain_24);
  display->drawString(0 + x, 38 + y, myText6);
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Text alignment demo
  display->setFont(ArialMT_Plain_10);

  // The coordinates define the left starting point of the text
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0 + x, 11 + y, "Left aligned (0,10)");

  // The coordinates define the center of the text
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64 + x, 22 + y, "Center aligned (64,22)");

  // The coordinates define the right end of the text
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(128 + x, 33 + y, "Right aligned (128,33)");
}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demo for drawStringMaxWidth:
  // with the third parameter you can define the width after which words will be wrapped.
  // Currently only spaces and "-" are allowed for wrapping
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawStringMaxWidth(0 + x, 10 + y, 128, "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");
}

void drawFrame5(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {

}

// This array keeps function pointers to all frames
// frames are the single views that slide in
//FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4, drawFrame5 };
FrameCallback frames[] = { drawFrame2, drawFrame21 };//, drawFrame3, drawFrame4, drawFrame5 };

// how many frames are there?
int frameCount = 2; //5;

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;

//#################################################
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  
  Serial.print("] ");
  display.clear();
  String msg;
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    //display.clear();
    msg += (char)payload[i];
  }
  //assign text lines?
  String topicS="";
  topicS+=topic;
  if(topicS.indexOf( "text1" )>0)
    myText1=msg;
  else if(topicS.indexOf( "text2" )>0)
    myText2=msg;
  else if(topicS.indexOf( "text3" )>0)
    myText3=msg;
  else if(topicS.indexOf( "text4" )>0)
    myText4=msg;
  else if(topicS.indexOf( "text5" )>0)
    myText5=msg;
  else if(topicS.indexOf( "text6" )>0)
    myText6=msg;
  else if(topicS.indexOf( "clock" )>0)
    myClockText=msg;
/*
   // display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    if (D1mini) {
      display.drawStringMaxWidth(35,13,60,msg); //d1 mini
      } else {
      display.drawStringMaxWidth(0,0,120,msg); //ESP8266 w/OLED   }
      }
    display.display();
*/  
  
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    uint32_t chipid=ESP.getChipId();
    char clientid[25];
    snprintf(clientid,25,"WIFI-Display-%08X",chipid); //this adds the mac address to the client for a unique id
    Serial.print("Client ID: ");
    Serial.println(clientid);
    if (client.connect(clientid)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      String payload="";
      payload+=WiFi.localIP().toString();
      client.publish("display1/ip", (char*) payload.c_str(), true);
      
      // ... and resubscribe
      client.subscribe("display1/#",1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//#################################################

void setup() {
  pinMode(PIN_POWER, OUTPUT);
  digitalWrite(PIN_POWER, HIGH);
  
  Serial.begin(9600);
  Serial.println('Hello');
  Serial.println();

  myText1 = "Aussen 11";
  myText2 = "Schlaf 12";
  myText3 = "Wohnz. 13";
  
  myText4 = "4-----";
  myText5 = "5-----";
  myText6 = "6-----";

	// The ESP is capable of rendering 60fps in 80Mhz mode
	// but that won't give you much time for anything else
	// run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS(10);

	// Customize the active and inactive symbol
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(RIGHT);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, frameCount);

  // Add overlays
  ui.setOverlays(overlays, overlaysCount);

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
}

const unsigned long REFRESH_INTERVAL = 1000; // ms
unsigned long lastRefreshTime = 0;

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    shutdown_counter--;
    if(shutdown_counter<0){
      digitalWrite(PIN_POWER, LOW); //shutdown power
    }
  }
  
  int remainingTimeBudget = ui.update();
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
    {
      lastRefreshTime += REFRESH_INTERVAL;
      client.loop();
    }
  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    reconnect();
    //delay(remainingTimeBudget);
  }
}
