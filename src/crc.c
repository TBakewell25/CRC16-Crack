#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "../utils/crc.h"
#include "../libcrc/include/checksum.h"
#include "../utils/IO.h"
char* printable ="\"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; 

volatile bool flag = false;
pthread_mutex_t lock;

unsigned int generateChecksum(char* text){
	size_t len;
	unsigned int checksum;

	len = strlen(text);

	checksum = crc_16(text, len);
	return checksum;
}
void testCombos(char* input, char* ascii, int inputlen, int curr, int max, int target, args* passed){
	int i;

	if (curr == max){
		passed->result = NULL;
		return;
	}

	for (i = 0; i < 96; i++){
		input[inputlen + curr] = ascii[i];	
		if (generateChecksum(input) == target){
			passed->result = true;
			return;
		}
		testCombos(input, ascii, inputlen, curr+1, max, target, passed);
		
		if (passed->result == true) {
            		return;  // Propagate the success back up	
		}
	}
}

void* crackSum(void* arguments){
	args* passed;	
	char* text;
	unsigned int target, len;
	int inputlen;

	passed = (args*) arguments;
	
	target = passed->target;
	len = passed->thread;
	
	text = (char*) malloc(strlen(passed->fileText)+len+1);
	strcpy(text, passed->fileText);

	inputlen = strlen(text);

	passed->result = NULL;

	while(flag == false){
		if (generateChecksum(text) == target)
			break;
		
		testCombos(text, printable, inputlen, 0, len, target, passed);
		
		if (passed->result != NULL){	
			pthread_mutex_lock(&lock);	
			flag = true;
			writeFile("Output.txt", text);	
			free(passed);			
			pthread_mutex_unlock(&lock);
		}
		if (passed->result == NULL){
			free(passed);
			return NULL;
		}
	}	
	return NULL;
}
		
	
		

void matchSums(char* inputText, unsigned int target){
	char* textToAdd;
	int i;
	pthread_t thread[10];
	args* array[10];	
	
	pthread_mutex_init(&lock, NULL);	
	
	textToAdd = "wahoowa";
	strcat(inputText, textToAdd);
	
	for (i = 0; i < 10; i++){
		array[i] = malloc(sizeof(args));
		array[i]->fileText = inputText;
		array[i]->target = target;
		array[i]->thread = i+1;
		
		pthread_create(&thread[i], NULL, &crackSum, array[i]);	
		pthread_join(thread[i], NULL);

	}

	pthread_mutex_destroy(&lock);
	
	return;
}

