/**
 * Class definition for mySpiffs
 * The mySpiffs class is designed to provide persistent data (that survives 
 * deep sleep) that can hold, in this case, SSID and password data for 
 * connecting to local access point(s). The library is different depending 
 * on whether we're using an 8266 or an ESP32.
 * 
 * @author  David Argles, d.argles@gmx.com
 * @version 28Dec2021 17:39h
 */

#if defined(ESP8266)
#pragma message "ESP8266 stuff happening!"
#include  <LittleFS.h>
#elif defined(ESP32)
#pragma message "ESP32 stuff happening!"
#include "SPIFFS.h"
#else
#error "This isn't an ESP8266 or ESP32 - you can't do SPIFFS!"
#endif

class mySpiffs
{
  public:

    String  SSID;
    String  passwd;
    
  /**
   * connect
   * Starts up the WiFi
   */
  void begin()
  {
    #if defined(ESP8266)
      LittleFS.begin();
      File info = LittleFS.open("info.txt","w+"); // Open info.txt for WiFi info
      if(!info) Serial.println("Failed to open SPIFFS file");  // Check we opened it OK
      else Serial.println("SPIFFS file opened");
      
    #elif defined(ESP32)
      SPIFFS.begin();
    #endif
  }
};
