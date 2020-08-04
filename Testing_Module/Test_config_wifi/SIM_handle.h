#include <Aruduino.h>
#include <SoftwareSerial.h>
#include "Utilities.h"

SoftwareSerial mySerial(RX3_PIN, TX3_PIN);//RX TX

#define TX3_PIN 33
#define RX3_PIN 34

#define mySerial SIM_Serial

//AT GENERAL
#define AT_PING_cmd "AT"
//#define AT_ECHO_cmd "ATE[x]"

//GPRS
#define AT_SEND_DATA_cmd ""
#define AT_SHUTDOWN_cmd ""
#define AT_SEND_SMS_cmd ""

//GPS
#define AT_READ_GPS_cmd "AT+CGPSINF=0"
#define AT_TURN_GPS_cmd ""
#define AT_CLOSE_GPS_cmd ""

#define Send_cmd(x) SIM_Serial.print(x)
#define Send_Endl SIM_Serial.print('\r\n')

#define SIM_AT_TIMEOUT 5000
//#define SIM_AT_TIMEOUT 5000

enum SIM_STATUS{
    AT_OK,
    AT_FAIL,
    SEND_SMS_OK,
    SEND_SMS_FAIL,
    SEND_GPRS_OK,
    SEND_GPRS_FAIL,
    UNKNOW,
};