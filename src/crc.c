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
/*
char* generate_combinations(char *current, int length, int position, const int target){
	if (position == length) 
		return NULL;

	char letter[1];
	for (int i = 0; i < CHAR_COUNT; i++){
		letter[0]  = (char)(MIN_ASCII + i);
			strcat(current, letter);

		if (target == generateChecksum(current))
			printf("\n%s\n", current);
			return current; 

			generate_combinations(current, length, position + 1, target);
	}
}*/

char* testCombinations(char* baseString, int targetChecksum, int len){
	char combination[len + 1];
	char* ret;
	combination[len] = '\0'; // Null-terminate the combination string
	char testString[len + strlen(baseString) + 1]; // String to hold base + combination

	for (long long i = 0; i < (long long)pow(94, len); i++){
	    long long num = i;
	    for (int j = 0; j < len; j++){
	        combination[len - 1 - j] = (num % 94) + 32;
	        num /= 94;
	    }

	    snprintf(testString, sizeof(testString), "%s%s", baseString, combination);

	    int checksum = generateChecksum(testString);

	    if (checksum == targetChecksum){
		ret = malloc(sizeof(combination));	
		ret = combination;
	        return ret; // Exit after finding the first match
	    }
	}
}

void* crackSum(void* arguments){
	args* passed;	
	char* text, ascii[1], *tmp;
	unsigned int target, len;
	int iterator, letter, i, j;

	 passed = (args*) arguments;

	text = passed->fileText;
	target = passed->target;
	len = passed->thread;


	iterator = 1;
	
	while(!flag){
		if (generateChecksum(text) == target)
			break;
		tmp = testCombinations(text, target, len);
		pthread_mutex_lock(&lock);	
		
		flag = true;
		strcat(text, tmp);	
		passed->fileText = text;
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
	
	textToAdd = "wahoo";
	strcat(inputText, textToAdd);
	
	for (i = 0; i < 10; i++){
		array[i] = malloc(sizeof(args));
		array[i]->fileText = inputText;
		array[i]->target = target;
		array[i]->thread = array[i]->thread + i + 1;
		
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

