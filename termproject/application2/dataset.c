//Zach Anderson
//Term Project
//Application2
//This is the main function for application 2, in which I use a hash table to manage information about college students

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "table.h"

#define EMPTY 0
#define DELETED 1
#define FILLED 2


static int findID(SET *sp, int ID, bool *found);

static int hash(int ID);

typedef struct set {
	int count;
	int length;
	int *data;
	char* flags;
} SET;

                    
static int hash(int ID) {
	return (ID * 32771) % 3001;
}
                         
SET *createDataSet(int maxElts) {
//Creates the data struct
	int i;
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
        sp->flags = malloc(sizeof(char)*maxElts);
	sp->data = malloc(sizeof(int)*maxElts);
        assert(sp->data != NULL);
       	for(i = 0; i < sp->length; i++) {
        	sp->flags[i] = EMPTY;
	}
        printf("Data structure has been created\n");
	return sp;
}

void destroyDataSet(SET *sp) {
//Frees all allocated data 
	assert(sp != NULL);
        free(sp->flags);
        free(sp->data);
        free(sp);
	printf("Data Freed\n");
}

void addID(SET *sp, int ID){
//Inserts an ID into the set pointed to by sp
	printf("Inserted student ID: %d, at position %d\n",sp->count+1, ID, hash(ID) % sp->length);
	assert(sp != NULL);                                                     bool found = false;
	int num;
	num = findID(sp, ID, &found);
	if(found == false){
		sp->data[num] = ID;
		sp->count++;
		sp->flags[num] = FILLED;
		printf("Sucessful Insert\n");
	}
	else{
		printf("Unsuessful Insert\n");
	}
}

void removeID(SET *sp, int ID) {
//Removes an ID that is in the set
    printf("Deleting Student ID:%d\n", ID);
    assert(sp!=NULL);
    bool found = false;
    int num; 
    num = findID(sp, ID, &found);
    if (found == true) {
        sp->flags[num] = DELETED;
        sp->count--;
        printf("Succesfully deleted student\n");
    } 
    else{
	 printf("Unsuccesfully deleted student\n");
    }
}

int searchID(SET *sp, int ID) {
//Searches and returns an ID from the set
    assert(sp!=NULL);
    bool found = false;
    int num 
    num = findID(sp, ID, &found);
    if(found == true) {
        return sp->data[num];
    } 
    else{
	return -1;
    }
} 

static int findID(SET *sp, int ID, bool *found) {
//Returns location either for putting in or removing an ID in the set
    printf("Searching for ID: %d\n", ID);
    assert(sp!=NULL);
    int num; 
    num = hash(ID) % sp->length;
    int firstDeleted = -1;
    while (sp->flags[num] != EMPTY) {     
    	if(sp->flags[num] == DELETED){
		if(firstDeleted == -1){
			firstDeleted = num;
		}
	}
	else if(sp->flags[num] == FILLED){
		if(sp->data[num] == ID){
			*found = true;
			printf("Student %d found\n", ID);
			return num;
		}
	}
	printf("Position %d has been taken, searching for %d\n", num, ((num+1) % sp->length));
	num = (num+1) % sp->length;
     }
	if(firstDeleted == -1){	
		return num;
	}
	else{
		return firstDeleted;
	}
}	                                                                                                                                                                                                                                                                                                                               
