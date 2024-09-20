#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/IO.h"

char* readFile(char* path){
	char *text, tmp[50];
	FILE* stream;
	stream = fopen(path, "r");
	
	text = (char*) malloc(sizeof(char));
	if (stream == NULL){
		printf("ERROR: cannot open file for reading");
		return NULL;
	}

	while(fgets(tmp, 50, stream) != NULL){
		text = realloc(text, sizeof(tmp));
		strcat(text, tmp);
	}

	fclose(stream);
	return text;
}

void writeFile(char* path, char* txt){
	FILE* stream;
	size_t len;


	stream = fopen(path, "w");
	len = strlen(txt);

	if (stream == NULL){
		printf("ERROR: cannot open file for writing");
		return;
	}

	fprintf(stream, txt);
	fclose(stream);
	free(txt);
	return;
}
