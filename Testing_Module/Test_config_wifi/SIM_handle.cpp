/* 
Date  : 04/08/2020
Author: DungTT
To handle application layer of SIM communication.
Use Software Serial (be carefull!)
Including: 

 */

#include "SIM_handle.h"

SoftwareSerial mySerial(RX3_PIN, TX3_PIN);//RX TX

void SIM_Send_cmd(String cmd){
    SIM_Serial.print(cmd);
}

void SIM_Ping(){
    SIM_Send_cmd(AT_PING_cmd);
    Send_Endl();
}

void SIM_Send_Data_GPRS(String data){
    SIM_Send_cmd(AT_SEND_DATA_cmd);
    SIM_Send_cmd(data);
    Send_Endl();
}

void SIM_Send_Data_SMS(String data){
    SIM_Send_cmd(AT_SEND_SMS_cmd);
    SIM_Send_cmd(data);
    Send_Endl();
}

void SIM_Shutdown(){
    SIM_Send_cmd(AT_SHUTDOWN_cmd);
    Send_Endl();
}

void SIM_Send2Get_GPS(){
    SIM_Send_cmd(AT_READ_GPS_cmd);
    Send_Endl();
}

void SIM_Get_Respond(String &outStr){
    if (SIM_Serial.available()){
        outStr = SIM_Serial.readStringUntil('\n');
    }
}

/* void SIM_Task_Handle(String &inStr){
    if (inStr == )
} */
