#include <Arduino.h>
#include "User_LiquidCrystal_I2C.h"

//define LCD pin
#define SDA_PIN 21
#define SCL_PIN 22

#define LCD_COL 20
#define LCD_ROW 4
#define LCD_ADDR 0x27//0x3F with new device

#define GREETING "Hello, World!"

#define HEART_ICON 0
#define SMILELY_ICON 1

byte Check_I2C_Address(byte address);
void LCD_init();
void LCD_Creat_Special_Char();
void LCD_Clear_and_Go_XY(byte x, byte y);
void LCD_Print_Data_from_Serial();


