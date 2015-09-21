//constant
#ifndef constant_h
#define constant_h

const std::string ACCOUNT_TYPE_CURRENT("current");
const int ACCOUNT_TYPE_CURRENT_CODE = 0x01;
const std::string ACCOUNT_TYPE_FIXED("fixed");
const int ACCOUNT_TYPE_FIXED_CODE = 0x02;
const std::string ACCOUNT_TYPE_BOTH("both");
const int ACCOUNT_TYPE_BOTH_CODE = 0x03;
const int MENU = 0x1;
const int INPUT = 0x2;
const int CREATION = 0x4;
const int QUERY = 0x8;
const int EDIT = 0x10;
const int DELETE = 0x20;
const int INVALID_OPERATION = 0x8000;
const int MONTH_DAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//UNIX/Linux/OS X
#define CLEAN "clear"
#define CLEAR std::cin.seekg(0, std::ios::end)
//Windows
//#define CLEAN "cls"
//#define CLEAR std::cin.sync()

#endif
