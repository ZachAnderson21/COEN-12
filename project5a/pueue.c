//Zach Anderson
//project5
//5/26/2023
//pqueue.c
//This lab defines the pqueue struct and all other function that are needed for the Huffman Coding

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "pqueue.h"
#define START_LENGTH 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)


struct pqueue{
	int total; 
	int size; 
	int **info;
	int (*compare)();
};

PQ *createQueue(int(*compare)()){
//return a pointer to a new priority queue using compare as its comparison function
//Runtime: O(1)
	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq -> total= 0;
	pq -> size = START_LENGTH;
	pq -> info = malloc(sizeof(void*)*START_LENGTH);
	pq -> compare = compare;
	assert(compare != NULL);
	return pq;
}
	
void destroyQueue(PQ *pq){
//deallocate memory associated with the priority queue pointed to by pq
//Runtime: O(n)
	int i;
	i = 0;
	for(i; i < pq->total; i++){
		free(pq->info[i]);
	}
	free(pq->info);
	free(pq);
}

int numEntries(PQ *pq){
//return the number of entries in the priority queue pointed to by pq
//Runtime: O(1)
	return pq->total;
}

void addEntry(PQ *pq, void *entry){
//add enrty to the priority queue pointed to by pq
//Runtime: O(log n)
	assert(pq != NULL && entry != NULL);
	if(pq->total == pq->size){
		pq->info = realloc(pq->info, sizeof(void*)*pq->size*2);
		pq-> size = pq -> size*2;
	}
	pq -> info[pq->total] = entry;
	int index;
	index = pq -> total;
	while(pq -> compare(pq->info[index], pq->info[p(index)]) < 0){
		void *temp = pq->info[p(index)];
		pq->info[p(index)] = pq -> info[index];
		pq->info[index] = temp;
		index = p(index);
	}
	pq->total++;
}

void *removeEntry(PQ *pq){
//remove and return the smallest entry from the priority queue pointed to by pq
	void *root = pq->info[0];
	int index = 0, smallestIndex = 0;
	pq -> info[index] = pq->info[pq->total-1];
	pq->total--;
	while (l(index)<(pq->total)){
		smallestIndex = l(index);
		if(r(index) < pq->total){
			if(pq->compare(pq->info[l(index)], pq-> info[r(index)])<0){
				smallestIndex = l(index);
			}
			else{
				smallestIndex = r(index);
			}
		}
		if(pq -> compare(pq->info[smallestIndex], pq->info[index])<0){	
			void* temp = pq->info[smallestIndex];
			pq->info[smallestIndex] = pq->info[index];
			pq->info[index] = temp;
			index = smallestIndex;
		}
		else{
			break;
		}
	}
	return root;
}
			




