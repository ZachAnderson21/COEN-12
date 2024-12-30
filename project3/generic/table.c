/* Zach Anderson
 * project3 - generic
 * 4/12/23
 * Defines a struct and searches, adds, deletes, and finds elements through different data files. 
 * */



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2


struct list{
	int total;
	int size;
	void **info;
	char *flags;
	int (*compare)();
	unsigned (*hash)();
};

typedef struct list LIST;


static int search(LIST *p, void *elt, bool *found);


LIST *createSet(int maxElts, int (*compare)(), unsigned(*hash)()){
//  return a pointer to a new set with a maximum capacity of maxElts
//  Runtime: O(n) 
	
	LIST *p;
	int i;
	
	p = malloc(sizeof(LIST));
	assert(p != NULL);
	p -> total = 0;
	p -> info = malloc(sizeof(void*)*maxElts);
	p -> size = maxElts;
	p -> flags = malloc(sizeof(char*)*maxElts);
	p -> compare = compare;
	p -> hash = hash;

	for(i = 0; i < maxElts; i++){
		p -> flags[i] = EMPTY;
	}
	assert(p -> info != NULL);
	return p;
}
		
void destroySet(LIST *p){
//  deallocate memory associated with the set pointed to by p
//  Runtime: O(1)
	
	free(p -> info);
	free(p -> flags);
	free(p);
}

int numElements(LIST *p){
// return the number of elements in the set pointed to by p
// Runtime: O(1)
	assert(p != NULL);
	return p -> total;
}
	
void addElement(LIST *p, void *elt){
//  add elt to the set pointed to by p
//  Runtime: O(n)
	
	assert(p != NULL && elt != NULL);
	bool searched;
	int index;
	index = search(p, elt, &searched);
	
	if(searched == false){
		p -> info[index] = elt;
		p -> flags[index] = FILLED;
		p -> total++;
	}

}
void removeElement(LIST *p, void *elt){
// remove elt from the set pointed to by p
// Runtime: O(n)
	
	assert(p != NULL && elt != NULL);
	bool searched;
	int index;
	index = search(p, elt, &searched);
	if(searched == true){
		p->flags[index] = DELETED;
		p -> total--;
	}
}
char *findElement(LIST *p, void *elt){
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
// allocate and return an array of elements in the set pointed to by p
// Runtime: O(n)

	assert(p != NULL);
	int i;
	char **arr;
	int last = 0;
	arr = malloc(sizeof(void*)*p->total);
	for(i = 0; i < p->size; i++){
		if(p->flags[i] == FILLED){
			arr[last] = p->info[i];
			last++;
		}
	}
	return arr;
}

static int search(LIST *p, void *elt, bool *found){
//performs a binary search
//Runtime: O(n)
	
	int head = (*p -> hash)(elt)%p->size;
	int i;
	int locn;
	int deletedlocn = -1;
	
	
	for(i = 0; i < p->size; i++){
		locn = (head + i)%p->size;
		if(p->flags[locn] == FILLED){
			if((p->compare)(p->info[locn],elt) == 0){
				*found = true;
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
