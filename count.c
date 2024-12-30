/* Zach Anderson
 * lab1
 * 4/5/2023
 * counting words */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 30

void count(char *);

int main(int argc, char *argv[]){
	
	if(argc == 1){			//check if file exists
		printf("Error");
		return 1;
	}

	count(argv[1]);
	
}

void count(char *file){
	
	FILE *fp; 			//create pointer to navigate file
	fp = fopen(file, "r");
	int counter = 0;
	char word[MAX_WORD_LENGTH];
		
	if(fp == NULL){			//check if file pointer is pointing at something
		printf("cant open file");
		return;
	}
	
	while(fscanf(fp, "%s", word) == 1){	//counts number of words
		counter++;
	}
	printf("%d words", counter);
	fclose(fp);
	
}
	
	
 
