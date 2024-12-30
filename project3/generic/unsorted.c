/* Zach Anderson
 * Lab2-unsorted 
 * 4/12/23
 * unsorted file that defines a struct, and then uses different functions to run through a data set of words. The file has multiple attributes including, searching, creating, and destroying.
 * */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



struct list{
	int total_words;
	int size;
	char **words;
};

typedef struct list LIST;


static int search(LIST *p, char *elt);


LIST *createSet(int maxElts){
//  return a pointer to a new set with a maximum capacity of maxElts
//  Runtime: O(1) 
	LIST *p;
	p = malloc(sizeof(LIST));
	assert(p != NULL);
	p -> total_words = 0;
	p -> size = maxElts;
	p -> words = malloc(sizeof(char*)*maxElts);
	assert(p -> words != NULL);
	return p;
}
		
void destroySet(LIST *p){
//  deallocate memory associated with the set pointed to by p
//  Runtime: O(n)
	int i;
	for(i = 0; i < p -> total_words; i++){
		free(p -> words[i]);
	}
	free(p -> words);
	free(p);
}


int numElements(LIST *p){
// return the number of elements in the set pointed to by p
// Runtime: O(1)
	assert(p != NULL);
	return p -> total_words;
}
	
void addElement(LIST *p, char *elt){
//  add elt to the set pointed to by p
//  Runtime: O(n)
	if(search(p, elt) == -1){
		p -> words[p -> total_words]=strdup(elt);
		p -> total_words++;
	}
}
void removeElement(LIST *p, char *elt){
// remove elt from the set pointed to by p
// Runtime: O(n)
	int index = search(p, elt);
	if(index != -1){
		free(p->words[index]);
		p -> words[index] = p->words[p -> total_words-1];
		p -> words[p -> total_words-1] = NULL;
		p -> total_words--;
	}
}
char *findElement(LIST *p, char *elt){
//  if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
//  Runtime: O(n)
	int i;
	for(i = 0; i < p -> total_words; i++){
		if(strcmp(p -> words[i],elt)==0){
			return elt;
		}
	}
	return NULL;
}

char **getElements(LIST *p){
// allocate and return an array of elements in the set pointed to by sp
// Runtime: O(n)
	char **arr;
	arr = malloc(sizeof(char*)*p -> total_words);
	memcpy(arr, p-> words, sizeof(char*)*p -> total_words);
	return arr;
}

static int search(LIST *p, char *elt){
//performs a binary search
//Runtime: O(n)
	int i;
	for(i = 0; i < p-> total_words; i++){
		if(strcmp(p -> words[i], elt)==0){
			return i;
		}
	}
	return -1;
}
