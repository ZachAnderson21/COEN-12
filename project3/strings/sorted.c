/* Zach Anderson
 * Lab2 - Sorted 
 * 4/12/23
 * Sorted file that uses different functions to go through different sets of data. The sorted list is more efficient than the unsorted.
 * */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>



struct list{
	int total_words;
	int size;
	char **words;
};

typedef struct list LIST;


static int search(LIST *p, char *elt, bool *found);


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
// Runtime: O(n)
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
	int i;
	assert(p != NULL && elt != NULL);
	bool searched;
	int index;
	index = search(p, elt, &searched);
	if(searched == false){
		for(i = p->total_words; i > index; i--){
			p->words[i] = p->words[i-1];
		}
		p->words[index] = strdup(elt);
		p->total_words++;
	}
}

void removeElement(LIST *p, char *elt){
// remove elt from the set pointed to by p
// Runtime: O(n)
	int i;
	bool searched;
	int index;
	index = search(p, elt, &searched);
	assert(p != NULL && elt != NULL);
	if(searched == true){
		free(p->words[index]);
		for(i = index + 1; i < p -> total_words; i++){
			p->words[i-1] = p->words[i];
		}
		p->total_words--;
	}
}

char *findElement(LIST *p, char *elt){
//  if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
//  Runtime: O(logn)
	assert(p != NULL && elt != NULL);
	bool searched;
	int index;
	index = search(p, elt, &searched);
	if(searched == true){
		return elt;
	}
	else{
		return NULL;
	}
}

char **getElements(LIST *p){
// allocate and return an array of elements in the set pointed to by sp
// Runtime:O(n)
	int i;
	assert(p != NULL);
	char **arr;
	arr = malloc(sizeof(char*)*p -> total_words);
	for(i = 0; i < p->total_words;i++){
		arr[i] = strdup(p->words[i]);
	}
	return arr;
}

static int search(LIST *p, char *elt, bool *found){
//Performs a binary search and uses boundaries such as high and low to sort the list.  
//Runtime: O(log n)
	int low, high, mid, diff;
	low = 0;
	high = p->total_words-1;

	while(low<=high){
		mid = (low + high)/2;
		diff = strcmp(elt, p->words[mid]);
		if(diff < 0){
			high = mid -1;
		}
		else if(diff > 0){
			low = mid + 1;
		}
		else{
			*found = true;
			return mid;
		}
	}
	*found = false;
	return low;
}
