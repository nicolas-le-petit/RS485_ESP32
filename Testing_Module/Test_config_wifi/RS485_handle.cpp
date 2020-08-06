// /**
//    Date  : 20/07/2020
//    Author: DungTT
//    To handle communicate via RS485.
//    Including: 
//    Expand 1 UART to 8 UART by MUX74HC4067.
//    Send/receive data via MAX485.

//   Base on library follow the link below:
//   https://github.com/pAIgn10/MUX74HC4067

// */
// //#include "RS485_protocol.h"
// #include "RS485_handle.h"

// MUX74HC4067 mux(MUX_EN_PIN, MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2);

// /*
// @date : 23/07/2020
// @brief: init RS485 serial.
// @para : baud rate.
//        config mode (optional)
// */
// void RS485_Init(int baud_rate, byte config = SERIAL_8N1){

//    RS485_Serial.begin(baud_rate, config);
   
//    //enable pin of MUX module
//    pinMode(MUX_EN_PIN, OUTPUT);

//    //enable RX - disable TX
//    pinMode(RS485_PIN_DE, OUTPUT);
//    RS485_Receive();
// }

// /*
// @date : 23/07/2020
// @brief: read a string via RS485.
// @para : channel need to read.
// */
// String RS485_Read_by_String(uint8_t channel) {

//  uint8_t tx_pin_slave = channel * 2;

//  mux.setChannel(tx_pin_slave);//select the pin
//  mux.enable();
//  mux.signalPin(RX2_PIN, INPUT_PULLUP, DIGITAL);//select pin to read data --> no need to set PULLUP, hw will handle
 
//  RS485_Receive();//change RS485 module to receive mode

//  if (RS485_Serial.available()) {
//    String incoming_data = RS485_Serial.readStringUntil('\n');
//    //Serial.println(incoming_data);
//    mux.disable();
//    return incoming_data;
//  } 
// }

// /*
// @date : 23/07/2020
// @brief: write a string via RS485.
// @para : channel need to write.
// */
// void RS485_Write_by_String(uint8_t channel, String data_frame) {

//  uint8_t rx_pin_slave = channel + 8;

//  mux.setChannel(rx_pin_slave);
//  mux.enable();
//  mux.signalPin(TX2_PIN, OUTPUT, DIGITAL);//select pin to write data

//  RS485_Transmit();  // cho phép gửi
//  RS485_Serial.println(data_frame);
//  RS485_Serial.flush();
//  RS485_Receive();//change RS485 module to receive mode

//  mux.disable();
// }

// /*
// @date : 03/08/2020
// @brief: calculate CRC 16 bit.
// @para : data, len of all frame
// */
// unsigned short CRC16(const byte* buf, int len)
// {
//  unsigned short crc = 0xFFFF;

//  for (int pos = 0; pos < len; pos++)
//  {
//    crc ^= (unsigned short)buf[pos];          // XOR byte into least sig. byte of crc

//    for (int i = 8; i != 0; i--) {    // Loop over each bit
//      if ((crc & 0x0001) != 0) {      // If the LSB is set
//        crc >>= 1;                    // Shift right and XOR 0xA001
//        crc ^= 0xA001;
//      }
//      else                            // Else LSB is not set
//        crc >>= 1;                    // Just shift right
//    }
//  }
//  return crc;//check ok :)
//  //return int -> need convert to hex
// }

// /* const byte* uint16_to_byte(unsigned short input){
//  byte output[2];

//  output[0] = (byte)((input >> 8) & 0XFF);
//  output[1] = (byte)((input & 0XFF00) >> 8); 
//  return output;
// } */

// /*
// @date : 03/08/2020
// @brief: calculate & send data follow Modbus RTU frame. (ID - Fcode - Data len - Data - CRC16)
// @para : slave ID, 
//        function code, 
//        length of frame, 
//        pointer to data
// */
// void RS485_Send_Data_by_Byte(byte SlaveID, byte Fcode, byte len, const byte* data) {

//    byte* msg;
//    msg[0] = SlaveID;
//    msg[1] = Fcode;
//    msg[2] = len;
//    byte msg_len = 3 + len/2 + 2;//ID + Code + Len + Data + CRC 

//    RS485_Transmit(); // allow to transmit

//    RS485_Serial.write(msg, msg_len);

//    //calculate CRC 16
//    unsigned short CRC = CRC16(msg, msg_len);

//    byte crc_msg[2];
//    crc_msg[0] = (byte)((CRC >> 8) & 0XFF);
//    crc_msg[1] = (byte)(CRC & 0XFF); 

//    //Send CRC to end frame
//    RS485_Serial.write(crc_msg, 2);
   
//    RS485_Receive();  // idle state
// }

// /*
// @date : 05/08/2020
// @brief: receive data RS485
// @para : data buffer - pass by referrence
//         max len
// @return: len of data received
// */
// byte RS485_Receive_Data_by_Byte(byte* & rev_msg, byte max_len = RS485_BUFFER) {
//     byte nbyte=0;
//     while (RS485_Serial.available()){
//     if (RS485_Serial.read()=='\n' || RS485_Serial.read()=='\0'){break;} 
//         rev_msg[nbyte] = RS485_Serial.read();//read hex here
//         nbyte++;
//     }
//     return nbyte;
// }

// /*
// @date : 05/08/2020
// @brief: process data RS485
// @para : data buffer - pass by referrence
//         max len
// @return: len of data received
// */
// void RS485_Process_Data(byte* & rev_msg, byte len = RS485_BUFFER){

//     len = RS485_Receive_Data_by_Byte(byte* & rev_msg);
//     byte SlaveID = rev_msg[0];
//     byte Fcode = rev_msg[1];
//     byte data_len = rev_msg[2];

//     byte data_rev[data_len];
//     for (byte i=3; i<data_len; i++){
//         data_rev[i-3] = rev_msg[i];
//     }

//     //ignore 2 byte CRC, assume that is correct
// }

// /* static byte crc8 (const byte *addr, byte len)
// {
//  byte crc = 0;
//  while (len--) 
//    {
//    byte inbyte = *addr++;
//    for (byte i = 8; i; i--)
//      {
//      byte mix = (crc ^ inbyte) & 0x01;
//      crc >>= 1;
//      if (mix) 
//        crc ^= 0x8C;
//      inbyte >>= 1;
//      }  // end of for
//    }  // end of while
//  return crc;
// }  // end of crc8 */

// /* void sendComplemented (WriteCallback fSend, const byte what)
// {
//  byte c;

//  // first nibble
//  c = what >> 4;
//  fSend ((c << 4) | (c ^ 0x0F)); 

//  // second nibble
//  c = what & 0x0F;
//  fSend ((c << 4) | (c ^ 0x0F)); 
 
// }  // end of sendComplemented */
