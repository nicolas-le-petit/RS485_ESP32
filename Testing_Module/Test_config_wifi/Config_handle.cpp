#include "Storage.h"
#include "Config_handle.h"


String menu_init[] ={
	"Please select mode:",
	"1. Press number (1) to access config mode",
	"2. Press number(2) to access execute mode",
};

String menu_config_mode[] = {
	"Please select config mode:"
	"1, Press number (1) to config Device",
	"2, Press number (2) to config Wifi",
};

String menu_config_device[] = {
	"Please select device:",
	"1, Device Information - Press (1)",
	"2, Setup Wifi - Press (2)",
	"3, Calibartion - Press (3)",
};

// void Load_User_Login(const char * & user, const char * & password){
//   String load_user = Read_EEPROM(WIFI_SSID_ADDRESS, WIFI_SSID_BUFFER_MAX);
//   /* Serial.print("SSID load from EEPROM: ");
//   Serial.println(load_ssid); */

//   ssid = load_ssid.c_str();
//   /* Serial.println("Value ssid after convert: ");
//   Serial.println(ssid); */

//   String load_password = Read_EEPROM(WIFI_PASSWORD_ADDRESS, WIFI_PW_BUFFER_MAX);   
//   /* Serial.print("Password load from EEPROM: ");
//   Serial.println(load_password); */

//   password = load_password.c_str();
//   /* Serial.println("Value password after convert: ");
//   Serial.println(password); */
// }

bool Check_Admin_User(const char* user_login, const char* password_login){
	//read data from EEPROM
}

void test(int& x){
	x = 123;
}

int Menu_Init_Log(){

	int mode;
	Serial.println();
	
	for (int i = 0; i < 3; ++i)
	{
		Serial.println(menu_init[i]);
	}
	while (!Serial.available()) {};

	char select = Serial.read();

	if ('1' == select){
		// Serial.print("User select option 1: ");
		// Serial.print(select);
		mode = CONFIG;
		// Serial.print("Return g_init_mode = ");
		// Serial.println(mode);
		return mode;
	}
	else if ('2' == select)
	{
		// Serial.print("User select option 2: ");
		// Serial.print(select);
		mode = EXECUTE;
		// Serial.print("Return g_init_mode = ");
		// Serial.println(mode);
		return mode;
	}
}

int Menu_Config_Mode_Log(){
	for (int i = 0; i < 3; i++)
	{
		Serial.println(menu_config_mode[i]);
	}

	/* while (!Serial.available()) {};

	int select = (int)Serial.read();
	switch select:
	case 1:
		
	case 2: */
		
}

int Menu_Config_Device_Log(){
	for (int i = 0; i < 4; i++)
	{
		Serial.println(menu_config_device[i]);
	}

	/* while (!Serial.available()) {};

	int select = (int)Serial.read();
	switch select:
	case 1:
		
	case 2:

	case 3: */
		
}