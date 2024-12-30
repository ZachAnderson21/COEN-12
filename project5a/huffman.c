//Zach Anderson
//5/26/2023
//Project5
//Huffman Code
//This function takes a file, and assigns each character of that file its very own binary number using a huffman tree. 




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "pqueue.h"
#include "pack.h"

#define NODE struct node

static int nodeCmp(NODE *, NODE *);
struct pqueue{
	int total;
	int size;
	int **info;
	int (*compare)();
};

int main (int argc, char *argv[]){
//Runtime: O(n)
//Sorts characters into a huffman tree and then assigns them there very own value, by counting the number of occurences of each character and then creating the tree
	FILE *p;
	int counts[257];
	NODE *leaves[257];	
	int i;
	char temp;
	for(i = 0; i<257; i++){
		counts[i] = 0;
		leaves[i] = NULL;
	}
	if(argc != 3){
		printf("Wrong number of files\n");
		return 0;
	}
	if((p=fopen(argv[1], "r")) == NULL){
		printf("No file name\n");
		return -1;
	}
//step 1: counts number of times each character in file appears
	while(fscanf(p,"%c", &temp)==1){
		counts[(int)temp]++;
	}
	fclose(p);
//step 2: create binary tree 
	PQ *pq = createQueue(nodeCmp);
	for(i = 0; i<257; i++){
		if(counts[i] > 0 || i == 256){
			leaves[i] = malloc(sizeof(NODE));
			leaves[i] -> count = counts[i];
			leaves[i] -> parent = NULL;
			addEntry(pq, leaves[i]);
		}
	}
	leaves[256] = malloc(sizeof(NODE));
	leaves[256] -> count = 0;
	leaves[256] -> parent = NULL;
	addEntry(pq,leaves[256]);
//step 3: counts number of entries and calculates sum
	while(numEntries(pq) > 1){
		NODE *child1;
		NODE *child2;
		NODE *temp_root = malloc(sizeof(NODE));
		assert(temp_root != NULL);
		child1 = removeEntry(pq);
		child2 = removeEntry(pq);
		temp_root -> parent=NULL;
		child1 -> parent= temp_root;
		child2-> parent = temp_root;
		temp_root->count = (child1->count + child2->count);
		addEntry(pq,temp_root);
	}
//step 4: uses the huffman tree and from that assignes each bit a specific bit pattern
	
	NODE *temp_node;
	for(i = 0; i<257; i++){
		if(leaves[i] != NULL){
			temp_node = leaves[i];
			int counter;
			counter = 0;
			while(temp_node -> parent != NULL){
				counter++;
				temp_node = temp_node->parent;
			}
			int count = counter*counts[i];
			if(isprint(i) == 0){
				printf("%03o: %d x %d bits = %d bits\n", i, counts[i], counter, count);
			}
			else{
				printf("'%c': %d x %d = %d bits\n",i,counts[i],counter, count);
			}
		}
	}
	pack(argv[1],argv[2],leaves);
	printf("end \n");
	return 0;
}

static int nodeCmp(NODE *a, NODE *b){
//Compares two nodes(a and b) and returns a number off that 
//Runtime: O(1)
	assert(a != NULL && b != NULL);
	if(a->count > b->count){
		return 1;
	}
	else if(a->count < b->count){
		return -1;
	}
	else{
		return 0;
	}
}		
