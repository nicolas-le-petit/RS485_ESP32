/* 
Date  : 30/07/2020
Author: DungTT
To handle Wifi function.
Including: 
Connect Wifi.
Load SSID & PASSWORD in EEPROM.
Config new SSID & PASSWORD in EEPROM.
 */

#define _DEBUG_
#include "WiFi_handle.h"

#define TIME_WAIT_TO_CONNECT_WIFI 40 // time = TIME_WAIT_TO_CONNECT_WIFI/2 (s)

/*
@date : 30/07/2020
@brief: connect to wifi.
@para : address of ssid, password
 */

void Wifi_Connect(const char * & ssid, const char * & password) {
  WiFi.begin(ssid, password);

  for (int i=0; i<TIME_WAIT_TO_CONNECT_WIFI; i++){
    if (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    else{
      break;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/*
@date : 30/07/2020
@brief: load ssid & password in EEROM, pass-by-reference!
@para : address of ssid, password
 */

void Load_SSID_Password(const char * & ssid, const char * & password){
  String load_ssid = Read_EEPROM(WIFI_SSID_ADDRESS, WIFI_SSID_BUFFER_MAX);
  /* Serial.print("SSID load from EEPROM: ");
  Serial.println(load_ssid); */

  ssid = load_ssid.c_str();
  /* Serial.println("Value ssid after convert: ");
  Serial.println(ssid); */

  String load_password = Read_EEPROM(WIFI_PASSWORD_ADDRESS, WIFI_PW_BUFFER_MAX);   
  /* Serial.print("Password load from EEPROM: ");
  Serial.println(load_password); */

  password = load_password.c_str();
  /* Serial.println("Value password after convert: ");
  Serial.println(password); */
}

/*
@date : 30/07/2020
@brief: write new ssid & password to EEROM.
@para : ssid, pass
 */

void Config_SSID_Password(const char* ssid, const char* password){
  //Read ssid & password from Serial
  Serial.println();
  Serial.println("SSID: ");
  while (!Serial.available()) {};//wait until get char from Serial

  String incomming_ssid = Serial.readStringUntil('\n');
  ssid = incomming_ssid.c_str();

  Serial.println("Password: ");
  while (!Serial.available()) {};
  
  String incomming_password = Serial.readStringUntil('\n');
  password = incomming_password.c_str();

  //Storage data into EEPROM
  Write_EEPROM(WIFI_SSID_ADDRESS, incomming_ssid.length(), ssid);

  /* #if 0
    Serial.println("Wifi SSID has been storaged in EEPROM!");
    String load_ssid = Read_EEPROM(WIFI_SSID_ADDRESS, WIFI_SSID_BUFFER_MAX);
    Serial.println(load_ssid);
  #endif */

  Write_EEPROM(WIFI_PASSWORD_ADDRESS, incomming_password.length(), password);
  
  /* #if 0
    Serial.println("Wifi password has been storaged in EEPROM!");
    String load_password = Read_EEPROM(WIFI_PASSWORD_ADDRESS, WIFI_PW_BUFFER_MAX);
    Serial.println(load_password);
  #endif */
}