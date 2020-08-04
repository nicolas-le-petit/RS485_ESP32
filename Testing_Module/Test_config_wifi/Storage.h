/*#include "Storage.h"*/
#include <EEPROM.h>
/*#ifndef _STORAGE_H_
#define _STORAGE_H_*/

#define EEPROM_MASK 255//value by default of EEPROM
#define EEPROM_SIZE 100
#define DEVICE_NAME_ADDRESS 00
#define DEVICE_VERSION_ADDRESS 06
#define MAC_ID_ADDRESS 20
#define USER_LOGIN_ADDRESS 40
#define WIFI_SSID_ADDRESS 60//address to storage data for ssid is 60->79
#define WIFI_PASSWORD_ADDRESS 80//address to storage data for password is 80->99

#define WIFI_SSID_BUFFER_MAX 20
#define WIFI_PW_BUFFER_MAX 20
#define DEVICE_NAME_BUFFER_MAX 6
#define DEVICE_VERSION_BUFFER_MAX 14
#define MAC_ID_BUFFER_MAX 12

void Write_EEPROM(int add, int max_size, const char* inStr);
String Read_EEPROM(int add, int max_size);
void Show_Data_EEPROM(int startAdd, int size);
int Reset_Data_EEPROM(int startAdd, int size);