#include <stdlib.h>
#include <stdio.h>
#include "../utils/crc.h"
#include "../utils/IO.h"
#include "../utils/convert.h"
#include<unistd.h>

int main(int argc, char** argv){
	char *inputFile, *text, *outputFile, *hacked, *hex;
	unsigned int targetSum, checksum;

	if (argc > 3 || argc < 2){
		printf("Incorrect number of args");
		return -1;
	}
	inputFile = argv[1];
	text = readFile(inputFile);
	checksum = generateChecksum(text);
	hex = intToHex(checksum);
	
	if (argc == 3){
		targetSum = hexToInt(argv[2]);
	
		matchSums(text, targetSum);
	}
	
	return 0;
}
