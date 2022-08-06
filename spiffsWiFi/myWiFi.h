/**
 * Class definition for myWiFi
 * 
 * The myWiFi class provides a unified approach for connecting to WiFi - it needs to be 
 * different depending on which chip you're using. This class will need to be altered 
 * to suit different chips.
 * 
 * @author  David Argles, d.argles@gmx.com
 * @version 06aug2022 13:56h
 */
#include <ESP8266WiFi.h>  // Change this for ESP32

#define WIFI_SSID     "MySSID" // This is the default SSID
#define WIFI_PASSWORD "MyPasswd"   // - and the default password

class myWiFi
{
  public:
  bool  connected = false;
  String ssid     = WIFI_SSID;
  String password = WIFI_PASSWORD;

  /**
   * connect
   * Starts up the WiFi
   */

  void setSSID(String newSSID)
  {
    ssid = newSSID;
    return;
  }
  
  void setPwd(String newPwd)
  {
    password = newPwd;
    return;
  }
  
  void connect()
  {
    // *** Start up the WiFi ***
    if(trace)Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    int tries = 20;
    while ( (WiFi.status() != WL_CONNECTED) && (tries-- > 0) ) {
      delay ( 500 );
      if(trace)Serial.print ( "." );
    }
    if(WiFi.status() == WL_CONNECTED){
      connected = true;
      if(trace)Serial.println("connected");
    }
    else if(trace)Serial.println("FAILED");
    return;    
  }
};
