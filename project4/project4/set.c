// Zach Anderson
// 5/21/2023
// Lab 4
//
  
	
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#define AVG_LENGTH 20



struct set{
	int total;
	int size;
	int (*compare)();
	LIST **lists;
	unsigned(*hash)();
};

typedef struct set SET;
	
SET *createSet(int maxElts,int (*compare)(), unsigned (*hash)()){
//Runtime O(n)
//This function declares a set then allocates memory
	SET *p;
	p = malloc(sizeof(SET));
	assert(p != NULL);
	p -> total = 0;
	p -> size = maxElts/AVG_LENGTH;
	p -> lists = malloc(sizeof(void*)*p -> size);
	p -> compare = compare;
	p -> hash = hash;
	int i;
	for(i = 0; i < p -> size; i++){
		p -> lists[i] = createList(compare);
	}
	assert(p -> lists != NULL);
	return p;
}

void destroySet(SET *p){
//Runtime: O(n)
//deallocate memory associated with the list pointed to by p
	assert(p != NULL);
	free(p -> lists);
	free(p);
}

int numElements(SET *p){
//return the number of items in the list pointed to by p
//Runtime: O(n)
	assert(p != NULL);
	return p->total;
}


void addElement(SET *p, void *elt){
//add item as the first item in the list pointed to by p
//Runtime: O(n)
	assert(p != NULL && elt != NULL);
	int index;
	index = (*p -> hash)(elt)%p->size;
	if(findItem(p->lists[index],elt) == NULL){
		addFirst(p->lists[index],elt);
		p -> total++;
	}
}

void removeElement(SET *p, void *elt){
//Removes elements from the list
//Runtime O(n)
	assert(p != NULL && elt != NULL);
	int index;
	index = (*p->hash)(elt)%p->size;
	if(findItem(p-> lists[index],elt)!=NULL){
		removeItem(p->lists[index],elt);
		p -> total--;
	}
}

void *findElement(SET *p, void *elt){
//returns the element if found, if not returns NULL
//Runtime: O(n)
	assert(p != NULL && elt != NULL);
	int index;
	index = (*p -> hash)(elt) % p -> size;
	return findItem(p -> lists[index],elt);
}

void *getElements(SET *p){
//Returns a copy of the arrar for the user
//Runtime: O(n^2)
	assert(p != NULL);
	void **arr;
	int count = 0;
	int i;
	int j;
	arr = malloc(sizeof(void*)* p -> total);
	for(i = 0; i < p -> size; i++){
		void **array = getItems(p -> lists[i]);
		for(j = 0; j < numItems(p -> lists[i]); j++){
			arr[count] = array[j];
			count++;
		}
	}
	return arr;
}


