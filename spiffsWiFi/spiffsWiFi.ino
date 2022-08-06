/**
 * Program: spiffsWiFi
 * Purpose:
 *   An exploration of the SPIFFS virtual file system to see if it can be used to 
 *   carry info over during deep sleep. In particular, the idea is to get the ESP 
 *   to go into softAP mode while unable to connect to the Internet, to get an SSID 
 *   and associated password via (eg) a mobile phone, and then to connect in future 
 *   to a local AP so it has Internet access.
 *   Notes:
 *   - SPIFFS looks like it operates differently on ESP8266 and ESP32, so this will 
 *     need addressing
 * @author: David Argles, d.argles@gmx.com
 */

/* Program identification */ 
#define PROG    "spiffsWiFi"
#define VER     "1.1"
#define BUILD   "06aug2022 @13:50h"

// Set trace to be false if you don't want diagnostic output to serial port
#define trace true

/* Necessary includes */
#include  "flashscreen.h"
#include  "myWiFi.h"
// #include "myTime.h" Don't think I want time on this project
#include  "mySpiffs.h"

/* Global "defines" - may have to look like variables because of type */
#define BAUDRATE 115200     // Baudrate for serial output

/* Some 'defines' have to be variables */
uint64_t  deepSleepTime = 5e6; // Deep sleep delay (millionths of sec)

/* ----- Initialisation ------------------------------------------------- */

/* Global stuff that must happen outside setup() */
flashscreen flash;
myWiFi      wifi;
mySpiffs    wifiData;
//myTime      timer;

void setup() {
  Serial.begin(BAUDRATE);           // Start up the serial output port
  // Serial.setDebugOutput(true);
  flash.message(PROG, VER, BUILD);  // Send program details to serial output

  // Set the built-in led as an output
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH); // Turn the built-in LED *off*!!

  //Start up SPIFFS
  LittleFS.begin();
  
  // The following code is only there for testing purposes
  /*File info = LittleFS.open("info.txt","w");
  info.println(wifi.ssid);
  info.println(wifi.password);
  info.close(); */

  File info = LittleFS.open("info.txt","r"); // Open info.txt for WiFi info
  if(!info) Serial.println("Failed to open SPIFFS file");  // Check we opened it OK
  else Serial.println("SPIFFS file opened");
  // Get and set the stored WiFi data
  String incoming = info.readString();
  int ptr = incoming.indexOf(10);
  wifi.ssid = incoming.substring(0,ptr);
  Serial.print("SSID: ");
  Serial.println(wifi.ssid);
  int ptr2 = incoming.indexOf(10,ptr+1);
  wifi.password = incoming.substring(ptr+1, ptr2);
  Serial.print("pwd: ");
  Serial.println(wifi.password);
  /*int count = line.toInt();
  Serial.print("count = ");
  Serial.println(count);
  count++;*/
  info.close();
  

  // Start up WiFi
  wifi.connect();

  // Start up time server
  // if(wifi.connected)timer.sync();

  // put your remaining setup code here, to run once:
  
}

void loop() {
  // If we failed to get the WiFi or the time, try again now
  if(!wifi.connected) wifi.connect();
  // if(wifi.connected && !timer.running) timer.sync();
  
// At the moment, the rest of loop does something random just to show it's working

/* On the minute, print out the date and time to the serial output
  if(second()==0){
    Serial.print("Time now: ");
    Serial.println(dateTime());
  }*/
  // Toggle the built-in LED on or off
  digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
  // And deep sleep a bit (5 seconds)
  Serial.println("Nighty nighty!");
  ESP.deepSleep(deepSleepTime); 
}
