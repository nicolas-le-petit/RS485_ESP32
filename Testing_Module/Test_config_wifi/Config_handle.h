#include "Arduino.h"

const String Greeting = "Hello world";

// const char* user_login;
// const char* password_login;
// extern int g_init_mode;

enum INIT_MODE
{
  CONFIG = 0,
  EXECUTE = 1,
};

int Menu_Init_Log();
//void test(int& x);