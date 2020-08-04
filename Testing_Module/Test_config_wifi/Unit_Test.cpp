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
    "2.1, Check Wifi connect",
    "3.1, Check BL connect",
};

void Log_Menu_cmd(){
    Serial.println("Unit test ready:");
    for (int i=0; i<4; i++){
        Serial.println(cmd_menu[i]);
    }
}

void Check_Storage(){
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

        else if (cmd == "2.1"){
            const char* user_ssid;
            const char* user_password;

            String ssid = Read_EEPROM(WIFI_SSID_ADDRESS, WIFI_SSID_BUFFER_MAX);
            user_ssid = ssid.c_str();

            String password = Read_EEPROM(WIFI_PASSWORD_ADDRESS, WIFI_PW_BUFFER_MAX);
            user_password = password.c_str();

            if (ssid == "" || password == ""){
                Config_SSID_Password(user_ssid, user_password);
            }
            Wifi_Connect(user_ssid, user_password);
        }
    }
}

void Check_Menu_Config(){

}

void Check_Bluetooth(){
/*     if (Serial.available(){
        cmd = Serial.readStringUntil('\n');

        if (cmd == "3.1"){
            while (!Serial.available()){};
            char data_BL = SerialBT.read();
            Ser
        }
    }) */
}

void Unit_Test_cmd(){
    
    Check_Storage();
}
