#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "../utils/crc.h"
#include "../libcrc/include/checksum.h"

char* printable =" \"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; 
volatile bool flag = false;
pthread_mutex_t lock;

unsigned int generateChecksum(char* text){
	size_t len;
	unsigned int checksum;

	len = strlen(text);

	checksum = crc_16(text, len);
	return checksum;
}
char* testCombos(char* input, char* ascii, int inputlen, int curr, int max, int target){
	int i;
	size_t len;

	len = strlen(ascii);
	if (curr == max)
		return NULL;

	for (i = 0; i < len; i++){
		input[inputlen + curr] = ascii[i];	
		
		if (generateChecksum(input) == target){
			return input;
		}
		testCombos(input, ascii, inputlen, curr+1, max, target);
	}
}

void* crackSum(void* arguments){
	args* passed;	
	char* text, ascii[1], *tmp, *new;
	unsigned int target, len;
	int iterator, letter, i, j, inputlen;

	passed = (args*) arguments;
	
	text = (char*) malloc(sizeof(passed->fileText));
	strcpy(text, passed->fileText);

	target = passed->target;
	len = passed->thread;

	tmp = malloc(strlen(text) + len + 1);

	inputlen = strlen(text);

	iterator = 1;
	
	while(flag == false){
		if (generateChecksum(text) == target)
			break;
		tmp = realloc(text, strlen(text) + 1 + sizeof(char) * len);
		new = testCombos(tmp, printable, inputlen, 0, len, target);
		
		pthread_mutex_lock(&lock);	
		printf("thread %d found it!", len);		
		flag = true;
		passed->fileText = tmp;
		pthread_mutex_unlock(&lock);

	}	
	return NULL;
}
		
	
		

char* matchSums(char* inputText, unsigned int target){
	char* textToAdd;
	args *arguments;
	int i, j;
	pthread_t thread[10];

	args* array[10];	
	pthread_mutex_init(&lock, NULL);	
	
	textToAdd = "w";
	strcat(inputText, textToAdd);
	
	for (i = 0; i < 10; i++){
		array[i] = malloc(sizeof(args));
		array[i]->fileText = inputText;
		array[i]->target = target;
		array[i]->thread = i+1;
		
		pthread_create(&thread[i], NULL, &crackSum, array[i]);	
	}

//	for (j = 0; j < 10; j++){
//		pthread_join(thread[i], NULL);
//	}

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	pthread_join(thread[3], NULL);
	pthread_join(thread[4], NULL);
	pthread_join(thread[5], NULL);
	pthread_join(thread[6], NULL);
	pthread_join(thread[7], NULL);
	pthread_join(thread[8], NULL);
	pthread_join(thread[9], NULL);

	pthread_mutex_destroy(&lock);
	
	return inputText;
}

