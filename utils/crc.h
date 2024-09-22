#ifndef CRC_H
#define CRC_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	char* fileText;
	unsigned int target;
	unsigned int thread;
	bool result;
} args;


unsigned int generateChecksum(char* text);

void testCombos(char* input, char* ascii, int inputlen, int curr, int max, int target, args* passed);

void* crackSum(void* args);

void matchSums(char* inputText, unsigned int target);


#endif
