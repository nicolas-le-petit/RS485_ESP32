/* 
Date  : 03/08/2020
Author: DungTT
To test case by case functions of module.
Including: 
Check data storage in EEPROM.
Check WiFi function.
Check Bluetooth function.
 */

/* #ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_
#endif */
#include "Unit_Test.h"

String cmd_menu[] = {
    "1.1, Read EEPROM",
    "1.2, Write EEPROM",
    "2.1, Config Wifi",
    "2.2, Check Wifi connect",
    "3.1, Check LCD",
    "4.1, Check RS485 Receive",
    "4.2, Check RS485 Transmit",
    "5.1, Check SIM Ping",
    "5.2, Check SIM GPS",
    "5.3, Check SIM SMS",
    "5.4, Check SIM GPRS",
};

void Log_Menu_cmd(){
    Serial.println("Unit test ready:");
    for (int i=0; i<11; i++){
        Serial.println(cmd_menu[i]);
    }
}

void Check_Log(){
    if (Serial.available()){
        String cmd = Serial.readStringUntil('\n');

        if (cmd == "1.1"){
            Show_Data_EEPROM(0, EEPROM_SIZE);
        }

        else if (cmd == "1.2"){
            Reset_Data_EEPROM(0, EEPROM_SIZE);
            delay(10);
            Show_Data_EEPROM(0, EEPROM_SIZE);
        }

        else if (cmd == "2.2"){
            const char* user_ssid;
            const char* user_password;

            String ssid = Read_EEPROM(WIFI_SSID_ADDRESS, WIFI_SSID_BUFFER_MAX);
            user_ssid = ssid.c_str();

            String password = Read_EEPROM(WIFI_PASSWORD_ADDRESS, WIFI_PW_BUFFER_MAX);
            user_password = password.c_str();

            if (ssid == "" || password == ""){
                Serial.println("No data in memory, please config Wifi first!");
            }
            // Wifi_Connect(user_ssid, user_password);
        }
        else if (cmd == "2.1"){
            const char* user_ssid;
            const char* user_password;
            Config_SSID_Password(user_ssid, user_password);
            
            Wifi_Connect(user_ssid, user_password);
        }

        else if (cmd == "3.1"){
            LCD_Print_Data_from_Serial();
        }

        else if (cmd == "4.1"){
            //test RS485 receive here
            Serial.println("Select the channel: please press 0-7");
            while (!Serial.available()){};
            byte _channel = (byte)Serial.read();
            Serial.println("Wait for data from:");
            while (!Serial.available()){};
            Serial.println(RS485_Read_by_String(_channel));
        }        
        else if (cmd == "4.2"){
            //test RS485 transmit here
            Serial.println("Select the channel: please press 0-7");
            while (!Serial.available()){};
            byte _channel = (byte)Serial.read();
            Serial.println("Content to print (<15 chars):");
            while (!Serial.available()){};
            String outStr = Serial.readStringUntil('\n');
            RS485_Write_by_String(_channel, outStr);
        }
    }
}
