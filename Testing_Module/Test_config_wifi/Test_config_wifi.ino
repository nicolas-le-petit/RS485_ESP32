/**
  SPI
  MOSI 23  13
  MISO 19  12
  CLK  18  14
  CS   5   15

  Strapping Pins
  The ESP32 chip has the following strapping pins:

  GPIO 0
  GPIO 2
  GPIO 4
  GPIO 5 (must be HIGH during boot)
  GPIO 12 (must be LOW during boot)
  GPIO 15 (must be HIGH during boot)
*/

#define _DEBUG_ 4

//All library here
/*#include <WiFi.h>*/
/* #include "Storage.h"
#include "WiFi_handle.h"
#include "Config_handle.h" */
#include "Unit_Test.h"

//extern int _init_mode;
const char* user_ssid;
const char* user_password;

void setup()
{ 
  Serial.begin(9600);
  Serial.println("Hello world!");
  Serial.println("Serial is ready now!");
  
  EEPROM.begin(EEPROM_SIZE);
  delay(500);

  // Bluetooth_Init();

  /* String ssid = Read_EEPROM(WIFI_SSID_ADDRESS, WIFI_SSID_BUFFER_MAX);
  user_ssid = ssid.c_str();

  String password = Read_EEPROM(WIFI_PASSWORD_ADDRESS, WIFI_PW_BUFFER_MAX);
  user_password = password.c_str();
  
  int _init_mode = Menu_Init_Log();

  

  Serial.print("_init_mode = ");
  Serial.println(_init_mode);

  if (CONFIG == _init_mode){
    Serial.println("Mode Config");
    Config_SSID_Password(user_ssid, user_password);
    Wifi_Connect(user_ssid, user_password);
  }
  else if (EXECUTE == _init_mode){
    Serial.println("Mode Execute");
    Wifi_Connect(user_ssid, user_password);
  } */
}

void loop()
{
  Log_Menu_cmd();
  while (!Serial.available());
  Unit_Test_cmd();
}

/*------------------------------WIFI HANDLE---------------------------*/
//need to check User can login to config device

/*void send_data_to_cloud_via_WIFI(String sensor_data)
{
#ifdef _DEBUG_
  Serial.print("connecting to ");
  Serial.println(_host);
#endif

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(_host, _httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/input/";
//  url += streamId;
//  url += "?private_key=";
//  url += privateKey;
//  url += "&value=";
//  url += value;

#ifdef _DEBUG_
  Serial.print("Requesting URL: ");
  Serial.println(url);
#endif

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
  #ifdef _DEBUG_
      Serial.print(line);
  #endif
  }

  #ifdef _DEBUG_
    Serial.println();
    Serial.println("closing connection");
  #endif
}*/
/*----------------------------------------------------------------------*/