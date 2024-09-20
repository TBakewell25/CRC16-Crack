#ifndef CRC_H
#define CRC_H
#include <stdlib.h>

typedef struct{
	char* fileText;
	unsigned int target;
	unsigned int thread;
} args;


unsigned int generateChecksum(char* text);

void* crackSum(void* args);

char* matchSums(char* inputText, unsigned int target);


#endif
