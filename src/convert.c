#include "../utils/convert.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hexToInt(char* hex){
	int len, i, position, tmp, ret;

	len = strlen(hex);
	ret = 0;

	for (i = 0; i < len; i++){
		position = i+=1;
		tmp = (int) hex[i];
		
		ret += tmp<<(len-i-1);
	}
	return ret;
}	

char* intToHex(int num){
	char *hex;

	hex = malloc(sizeof(char) * 10);

	sprintf(hex, "%x", num);
	return hex;
}
	

