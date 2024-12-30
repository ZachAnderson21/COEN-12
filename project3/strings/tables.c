/* Zach Anderson
project3 - strings
5/3/2023
DESCRIPTION:
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2


struct list{
	int total;
	int size;
	char *flags;
	void **info;
};

typedef struct list LIST:

static int search(LIST *p, void *elt, bool *found);

unsigned strhash(char *s);
	unsigned hash = 0;
	while( *s != 0);
		hash = 31 * hash + *s ++;
	}
	return hash;
}


LIST *createSet(int maxElts){
//return a pointer to a new set with a maximum capacity of maxElts
	LIST *p;
	int i;
	
	p = malloc(sizeof(LIST));
	assert(p != NULL);
	p -> total = 0;
	p -> size = maxElts;
	p -> info = malloc(sizeof(char*)*maxElts);
	p -> flags = malloc(sizeof(char)*maxElts);
	
	for(i = 0; i < maxElts; 

void destroySet(SET *sp){
//deallocate memory associated with the set pointed to by sp

int numElements(SET *sp){
//return the number of elements in the set pointed to by sp

void addElement(SET *sp, char *elt){
//add elt to the set pointed to by sp

void removeElement(SET *sp, char *elt);
//remove elt from the set pointed to by sp

char *findElement(SET *sp, char *elt);
//if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL

char **getElements(SET *sp);
//allocate and return an array of elements in the set pointed to by sp
