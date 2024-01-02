#ifndef LOG_H
#define LOG_H

#include <stdbool.h>

enum LOGIN{
	INCORRECT,
	CORRECT
};

bool log_in(char* login, char* pass);
void log_out();
bool is_loged(char* pseudo);

#endif
