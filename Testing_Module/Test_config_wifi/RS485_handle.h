//define MUX74HC4067 pin
//para1: en pin
//para2-5: control pin
#include <Arduino.h>
#include "MUX74HC4067.h"

#define FCODE_READ_COIL 01
#define FCODE_READ_DISCRETE_INPUT 02
#define FCODE_READ_HOLDING_REGISTER 03
#define FCODE_READ_INPUT_REGISTER   04

#define MUX_EN_PIN 4
#define MUX_PIN_S0 25
#define MUX_PIN_S1 26
#define MUX_PIN_S2 27

//define RS485 pin
#define RS485_PIN_DE 32//control pin RS485, HIGH to transmit - LOW to receive
#define RS485_Transmit() digitalWrite(RS485_PIN_DE, HIGH)
#define RS485_Receive() digitalWrite(RS485_PIN_DE, LOW)
#define RS485_BUFFER 20

#define TX2_PIN 17
#define RX2_PIN 16

#define RS485_Serial Serial2

void RS485_Send_Data_by_Byte(byte SlaveID, byte Fcode, byte len, const byte* data);
void RS485_Write_by_String(uint8_t channel, String data_frame);
String RS485_Read_by_String(uint8_t channel);
void RS485_Init(int baud_rate, byte config);
unsigned short CRC16(const byte* buf, int len);