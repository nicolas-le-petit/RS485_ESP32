/**
    Date  : 20/07/2020
    Author: DungTT
    To handle communicate via RS485.
    Including: 
    Separate 1 UART to 8 UART by MUX74HC4067.
    Send/receive data via MAX485.

   Base on library follow the link below:
   https://github.com/pAIgn10/MUX74HC4067

*/
//#include "RS485_protocol.h"
#include "RS485_handle.h"

MUX74HC4067 mux(MUX_EN_PIN, MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2);

/*
@date : 23/07/2020
@brief: init RS485 serial.
@para : baud rate.
 */
void RS485_Init(int baud_rate, byte config = SERIAL_8N1){

    RS485_Serial.begin(baud_rate, config);
    
    //enable pin of MUX module
    pinMode(MUX_EN_PIN, OUTPUT);

    //enable RX - disable TX
    pinMode(RS485_PIN_DE, OUTPUT);
    RS485_Receive();
}

/*
@date : 23/07/2020
@brief: read a string via RS485.
@para : channel need to read.
 */
String RS485_Read_by_String(uint8_t channel) {

  uint8_t tx_pin_slave = channel * 2;

  mux.setChannel(tx_pin_slave);//select the pin
  mux.enable();
  mux.signalPin(RX2_PIN, INPUT_PULLUP, DIGITAL);//select pin to read data --> no need to set PULLUP, hw will handle
  
  RS485_Receive();//change RS485 module to receive mode

  if (RS485_Serial.available()) {
    String incoming_data = RS485_Serial.readStringUntil('\n');
    //Serial.println(incoming_data);
    mux.disable();
    return incoming_data;
  } 
}

/*
@date : 23/07/2020
@brief: write a string via RS485.
@para : channel need to write.
 */
void RS485_Write_by_String(uint8_t channel, String data_frame) {
 
  uint8_t rx_pin_slave = channel + 8;

  mux.setChannel(rx_pin_slave);
  mux.enable();
  mux.signalPin(TX2_PIN, OUTPUT, DIGITAL);//select pin to write data

  RS485_Transmit();  // cho phép gửi
  RS485_Serial.println(data_frame);
  RS485_Serial.flush();
  RS485_Receive();//change RS485 module to receive mode

  mux.disable();
}

/*
@date : 03/08/2020
@brief: calculate CRC 16 bit.
@para : data, len of all frame
 */
unsigned short crc16(const byte* data_p, byte len, unsigned short polynomial = 0xFFFF){
    unsigned char x;
    unsigned short crc = polynomial;

    while (len--){
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    return crc;
}

/*
@date : 03/08/2020
@brief: calculate & send data follow Modbus RTU frame.
@para : slave ID, function code, length of frame, pointer to data
 */
void RS485_Send_Data_by_Byte(byte SlaveID, byte Fcode, byte len, const byte* data) {

    byte* msg;
    msg[0] = SlaveID;
    msg[1] = Fcode;
    msg[2] = len;
    byte msg_len = 3 + len/2 + 2;//ID + Code + Len + Data + CRC 

    RS485_Transmit(); // allow to transmit

    RS485_Serial.write(msg, msg_len);

    /* unsigned short CRC = crc16(msg, msg_len);

    RS485_Serial.write(CRC, 2); */
    
    RS485_Receive();  // idle state
}

/* String RS485_Receive_Data_by_Byte(byte Fcode, byte len, const byte* data, unsigned long timeout) {

    byte Revmsg [];
    msg[0] = SlaveID;
    msg[1] = Fcode;
    msg[2] = len;
} */

/* static byte crc8 (const byte *addr, byte len)
{
  byte crc = 0;
  while (len--) 
    {
    byte inbyte = *addr++;
    for (byte i = 8; i; i--)
      {
      byte mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) 
        crc ^= 0x8C;
      inbyte >>= 1;
      }  // end of for
    }  // end of while
  return crc;
}  // end of crc8 */

/* void sendComplemented (WriteCallback fSend, const byte what)
{
  byte c;

  // first nibble
  c = what >> 4;
  fSend ((c << 4) | (c ^ 0x0F)); 

  // second nibble
  c = what & 0x0F;
  fSend ((c << 4) | (c ^ 0x0F)); 
  
}  // end of sendComplemented */

