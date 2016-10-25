#ifndef LOGGER_H
#define LOGGER_H
#include "..\Common\Common.h"

#ifdef DEBUG    //Macros are usually in all capital letters.
#define LOG(enable, ...)     \
do { \
	if(enable) \
	{ \
		char buffer[64] = "\0"; \
		sprintf(buffer, __VA_ARGS__); \
		if(strlen(buffer) >= 64) \
		{ \
			Serial.print("ERROR: Invalid log len\r\n"); \
		} \
		Serial.print(buffer); \
	} \
} while(0);
#else
  #define LOG(...)     //now defines a blank line
#endif

#endif // LOGGER_H