#include "../utils/convert.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hexToInt(char* hex){
	int result;

	result = strtol(hex, NULL, 16);
	return result;
}	

char* intToHex(int num){
	char *hex;

	hex = malloc(sizeof(char) * 10);

	sprintf(hex, "%x", num);
	return hex;
}
	

