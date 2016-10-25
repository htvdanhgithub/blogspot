#ifndef LOGGER_H
#define LOGGER_H
#include "..\Common\Common.h"

#ifdef DEBUG    //Macros are usually in all capital letters.
#define LOG(enable, ...)     \
do { \
	if(enable) \
	{ \
		char buffer[64]; \
		sprintf(buffer, __VA_ARGS__); \
		Serial.print(buffer); \
	} \
} while(0);
#else
  #define LOG(...)     //now defines a blank line
#endif

#endif // LOGGER_H