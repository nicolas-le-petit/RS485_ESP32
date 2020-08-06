#include "LCD_handle.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COL, LCD_ROW);
//byte LCD_Address = 0x27;
byte heart[8] = {0b00000,0b01010,0b11111,0b11111,0b11111,0b01110,0b00100,0b00000};
byte smilely[8] = {0b00000,0b00000,0b01010,0b00000,0b00000,0b10001,0b01110,0b00000};

byte Check_I2C_Address(byte address){
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    return error;
}

void LCD_init(){
    /* if (Check_I2C_Address(LCD_ADDR) == 0){
        Serial.println("LCD is ready!");
        lcd.init();
        // turn on LCD backlight                      
        lcd.backlight();
        // set cursor to first column, first row
        lcd.setCursor(0, 0);
        // print message
        lcd.print("Hello, World!");
    }
    return; */
    
    lcd.init();
    // turn on LCD backlight                      
    lcd.backlight();
    // set cursor to first column, first row
    lcd.setCursor(0, 0);
    // print message
    Serial.println("LCD is ready!");
    lcd.print("Hello, World!");
}

void LCD_Creat_Special_Char(){
    lcd.createChar(0, heart);//heart
    lcd.createChar(1, smilely);
    return;
}

void LCD_Clear_and_Go_XY(byte x, byte y){
    lcd.clear();
    if (x>19 || y>3){
        lcd.setCursor(0,0);
    }
    lcd.setCursor(x, y);
}

void LCD_Print_Data_from_Serial(){
    Serial.println("Write something to display on LCD:");
    while (!Serial.available()){}
    String incomming_data = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(incomming_data);
}

