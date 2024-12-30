/* Zach Anderson
 * project3 - strings 
 * 5/7/2023
 * A file that defines a struct and then uses a variety of functions such as create, destroy, find, and get; that go through a data file
 * */



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2



struct list{
	int total;
	int size;
	char **info;
	char *flags;
};

typedef struct list LIST;


static int search(LIST *p, char *elt, bool *found);

unsigned strhash(char *s){
//This function gives a hash value for each word
//Runtime: O(1)

	unsigned hash = 0;
	while(*s != 0){
		hash = 31 * hash + *s ++;
	}
	return hash;
}
LIST *createSet(int maxElts){
//  return a pointer to a new set with a maximum capacity of maxElts
//  Runtime: O(n)

	LIST *p;
	int i;
	
	p = malloc(sizeof(LIST));
	assert(p != NULL);
	p -> total = 0;
	p -> size = maxElts;
	p -> info = malloc(sizeof(char*)*maxElts);
	p -> flags = malloc(sizeof(char)*maxElts);
	
	for(i = 0; i < maxElts; i++){
		p -> flags[i] = EMPTY;
	}
	assert(p -> info != NULL);
	return p;
}

		
void destroySet(LIST *p){
//  deallocate memory associated with the set pointed to by p
// Runtime: O(n)

	int i;
	for(i = 0; i < p -> size; i++){
		if(p -> flags[i] == FILLED){
			free(p -> info[i]);
		}
	}
	free(p -> flags);
	free(p -> info);
	free(p);
}

int numElements(LIST *p){
// return the number of elements in the set pointed to by p
// Runtime: O(1)
	
	assert(p != NULL);
	return p -> total;
}
	
void addElement(LIST *p, char *elt){
//  add elt to the set pointed to by p
//  Runtime: O(n)

	assert(p != NULL && elt != NULL);
	bool searched;
	int index;
	index = search(p, elt, &searched);
	if(searched == false){
		p -> info[index] = strdup(elt);
		p -> flags[index] = FILLED;
		p -> total++;
	}
}

void removeElement(LIST *p, char *elt){
// remove elt from the set pointed to by p
// Runtime: O(n)

	bool searched;
	int index;
	index = search(p, elt, &searched);
	assert(p != NULL && elt != NULL);
	if(searched == true){
		free(p->info[index]);
		p -> flags[index] = DELETED;
		p->total--;
	}
}

char *findElement(LIST *p, char *elt){
//  if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
//  Runtime: O(n)
	assert(p != NULL && elt != NULL);
	bool searched;
	int index;
	index = search(p, elt, &searched);
	if(searched == true){
		return p -> info[index];
	}
	else{
		return NULL;
	}
}

char **getElements(LIST *p){
// allocate and return an array of elements in the set pointed to by sp
// Runtime:O(n)
	
	assert(p != NULL);
	int i;
	char **arr;
	int last = 0;
	arr = malloc(sizeof(char*)*p -> total);
	for(i = 0; i < p -> size;i++){
		if(p -> flags[i] == FILLED){
			arr[last] = strdup(p->info[i]);
			last ++;
		}
	}
	return arr;
}

static int search(LIST *p, char *elt, bool *found){
//Performs a binary search and uses boundaries such as high and low to sort the list.  
//Runtime: O(n)
	int head = strhash(elt)%p->size;
	int i;
	int locn;
	int deletedlocn = -1;
	
	for(i = 0; i < p->size; i++){
		locn = (head+i)%p->size;
		if(p->flags[locn] == FILLED){
			if(strcmp(p->info[locn],elt) == 0){
				*found = true ;
				return locn;
			}
		}
		else if(p->flags[locn] == DELETED){
			if(deletedlocn == -1){
				deletedlocn = locn;	
			}
		}
		else{
			break;
		}
	}
	*found = false;
	if(deletedlocn == -1){
		return locn;
	}
	return deletedlocn;
}

