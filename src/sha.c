#include "../utils/sha.h"
#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>

char* calcSHA(char* input){
	char* buff;

	buff = (char*) malloc(sizeof(SHA256_DIGEST_LENGTH));
	SHA256(input, strlen(input), buff);

	return buff;
}

