// //This example code is in the Public Domain (or CC0 licensed, at your option.)
// //By Evandro Copercini - 2018
// //
// //This example creates a bridge between Serial and Classical Bluetooth (SPP)
// //and also demonstrate that SerialBT have the same functionalities of a normal Serial
// #include <stdio.h>
// #include "Bluetooth_handle.h"

// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// #endif

// BluetoothSerial SerialBT;

// void Bluetooth_Init(){
//   SerialBT.begin(BLUETOOTH_NAME);
// }

// void Bluetooth_End(){
//   SerialBT.disconnect();
//   SerialBT.end();
// }

// void Bluetooth_Write(uint8_t* outStr, int size){
//   /* const uint8_t * outStr = msg.c_str();
//   int size = msg.length(); */
//   SerialBT.write(outStr, size);
// }

// void Bluetooth_Read_String(String& outStr){
//   char* inStr;
//   int sizeStr;
//   while (SerialBT.available()){
//       inStr += SerialBT.read();
//       sizeStr++;
//   }

//   SerialBT.flush();

//   for (int i = 0; i < sizeStr; i++) { 
//         outStr += inStr[i]; 
//     }
// }


