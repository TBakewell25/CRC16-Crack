#include <stdlib.h>
#include <stdio.h>
#include "../utils/crc.h"
#include "../utils/IO.h"
#include<unistd.h>

int main(int argc, char** argv){
	char *inputFile, *text, *outputFile, *hacked;
	unsigned int targetSum, checksum;

	if (argc > 3 || argc < 2){
		printf("Incorrect number of args");
		return -1;
	}
	inputFile = argv[1];
	text = readFile(inputFile);
	checksum = generateChecksum(text);

	if (argc == 3){
		targetSum = atoi(argv[2]);
		hacked = matchSums(text, targetSum);
		writeFile(inputFile, hacked);
	}
	
	return 0;
}
