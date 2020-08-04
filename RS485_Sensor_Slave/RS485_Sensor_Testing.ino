/**
   This example demonstrates how to combine reading inputs and writing
   outputs, whether they are digital or analog
   It assumes there are 2 push buttons with pullup resistors connected
   to channels C0 and C1, 2 potentiometers connected to channels C2
   and C3, and 4 LEDs+resistors with the positive lead of the LEDs
   connected to channels C4 to C7
   PIN A0 is used for reading the inputs and should connect to the SIG pin
   PIN 3 is used for writing the outputs and should connect to the SIG pin
   Connecting both PIN A0 and PIN 3 to the SIG pin won't create a problem
   because when the pins are not used, they are declared as inputs which
   puts them in a high impedance state

   For more about the interface of the library go to
   https://github.com/pAIgn10/MUX74HC4067

  MUX74HC4067 KEYWORD1// declare the MUX 4-16

  setChannel  KEYWORD2//set channel
  enable  KEYWORD2//enable module
  disable KEYWORD2//disable module
  signalPin KEYWORD2//select the pin read/write signal
  read  KEYWORD2
  write KEYWORD2

  SPI
  MOSI 23  13
  MISO 19  12
  CLK  18  14
  CS   5   15
*/
#include "MUX74HC4067.h"
//#define USE_SERIAL_0
#define USE_SERIAL_2// TX:17, RX:16

//define MUX74HC4067 pin
//para1: en pin
//para2-5: control pin
#define MUX_EN_PIN 34
#define MUX_SIG_PIN 17
#define MUX_PIN_S0 25
#define MUX_PIN_S1 26
#define MUX_PIN_S2 27
#define MUX_PIN_S3 14

MUX74HC4067 mux(MUX_EN_PIN, MUX_PIN_S0, MUX_PIN_S1, MUX_PIN_S2, MUX_PIN_S3);

//define LCD pin
#define LCD_SDA 21
#define LCD_DC 22
#define LCD_SCK 23
#define LCD_CS 24
#define LCD_RST 25

//define RS485 pin
#define RS485_PIN_DE 12//control pin RS485, HIGH to transmit - LOW to receive
#define RS485_Transmit HIGH
#define RS485_Receive LOW

#define TX2_PIN 17
#define RX2_PIN 16

#ifdef USE_SERIAL_0
#define RS485_Serial Serial
#else USE_SERIAL_2
#define RS485_Serial Serial2
#endif

void setup()
{
  Serial.begin(9600);
  Serial.printf("Serial 0 is ready now!");
  delay(1000);

  Serial2.begin(9600);
  Serial.printf("Serial 2 is ready now!");
  delay(1000);

  pinMode(RS485_PIN_DE, OUTPUT);
  pinMode(MUX_EN_PIN, OUTPUT);
//  pinMode(MUX_SIG_PIN, OUTPUT);

  //display LCD here
}

void loop()
{
  //String data_test = "Hello world";
  if (Serial.available()){
    String rev = Serial.readStringUntil('\n');
    write_serial_by_channel(1, rev);
  }
  //delay(1000);
  read_serial_by_channel(7);
}


//channel will be 0-7
void read_serial_by_channel(uint8_t channel) {
  //Select the pin
  uint8_t tx_pin_slave = channel * 2;

  mux.setChannel(tx_pin_slave);//select the pin
  mux.enable();
  mux.signalPin(RX2_PIN, INPUT_PULLUP, DIGITAL);//select pin to read data

  if (RS485_Serial.available()) {
    char incoming_data = RS485_Serial.read();
    //String incoming_data = RS485_Serial.readStringUntil('\n');
    //RS485_Serial.flush();
    Serial.println(incoming_data);
  }  
  mux.disable();
}

void write_serial_by_channel(uint8_t channel, String data_frame) {
  //Select the pin
  uint8_t rx_pin_slave = channel * 2 + 1;

  mux.setChannel(rx_pin_slave);
  mux.enable();
  mux.signalPin(TX2_PIN, OUTPUT, DIGITAL);//select pin to write data
  digitalWrite(RS485_PIN_DE, RS485_Receive);//change RS485 module to receive mode
  RS485_Serial.println(data_frame);
  RS485_Serial.flush();
  //RS485_Serial.print(data_frame);
  mux.disable();
}

void fWrite (const byte what)
{
  RS485_Serial.write (what);
}

int fAvailable ()
{
  return RS485_Serial.available ();
}

int fRead ()
{
  return RS485_Serial.read ();
}

String get_data_from_frame(String data_frame) {

}

void display_data_receive() {

}

void display_time() {

}

void display_wifi_infor() {

}
