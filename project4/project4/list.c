//Zach Anderson
//Lab4
//In this lab we create a data storage system


#include <assert.h>
#include <stdlib.h>
#include "list.h"

struct list{
	int total;
	struct node *head;
	int(*compare)();
};


struct node{
	void *info;
	struct node *next;
	struct node *prev;
};

typedef struct node NODE;


LIST *createList(int (*compare)()){
//return a pointer to a new list using compare as its comparison function, which may be NULL
//Runtime: O(1)	
	LIST *p;
	p = malloc(sizeof(LIST));
	assert(p != NULL);
	p->head = malloc(sizeof(struct node));
	p -> head -> next = p -> head;
	p -> head -> prev = p -> head;
	p -> total = 0;
	p -> compare = compare;
	return p;
}
		
void destroyList(LIST *p){
//deallocate memory associated with the list pointed to by lp
//Runtime: O(n)	
	assert(p !=NULL);
	while(p -> total > 0){
		removeLast(p);
	}
}

int numItems(LIST *p){
//return the number of items in the list pointed to by lp
//Runtime: O(1)
	assert(p != NULL);
	return p -> total;
}

void addFirst(LIST *p, void *item){
//add item as the first item in the list pointed to by lp	
//Runtime: O(n)	
	struct node *New = malloc(sizeof(struct node));
	New -> info = item;
	New -> next = p->head->next; 
	p-> head -> next = New;
	New -> prev = p -> head;
	New -> next -> prev = New;
	p -> total++;
}
	

void addLast(LIST *p, void *item){
//add item as the last item in the list pointed to by lp
//Runtime: O(1)
	struct node *New = malloc(sizeof(struct node));
	New -> info = item;
	New -> next = p -> head;
	New -> prev = p -> head -> prev;
	p -> head -> prev = New;
	New -> prev -> next = New;
	p -> total ++;
}	
	
void *removeFirst(LIST *p){
//remove and return the first item in the list pointed to by lp ; the list must not be empty
//Runtime: O(1)
	assert(p -> total > 0);
	struct node *Nodeb = p -> head -> next;
	void *data = Nodeb -> info;
	p -> head -> next = Nodeb -> next;
	Nodeb -> next -> prev = p -> head;
	free(Nodeb);
	p -> total--;
	return data;
} 
	
void *removeLast(LIST *p){
//remove and return the last item in the list pointed to by lp ; the list must not be empty
//Runtime: O(1)
	assert(p -> total > 0);
	struct node *last = p -> head -> prev;
        void *lastdata = last -> info;
        last -> prev -> next = p -> head;
	p -> head -> prev = last -> prev;
        free(last);
        p -> total--;
        return lastdata;
}

void *getFirst(LIST *p){
//return, but do not remove, the first item in the list pointed to by lp ; the list must not be empty
//Runtime: O(1)	
	assert(p -> count > 0);
	return p -> head -> next -> info;
}

void *getLast(LIST *p){
//return, but do not remove, the last item in the list pointed to by lp ; the list must not be empty
//Runtime: O(1)
	assert(p-> total>0);
	return p -> head -> prev -> info;
}

	
void removeItem(LIST *p, void *item){
//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
//Runtime: O(n)
	assert(p -> compare != NULL && p -> total > 0 && item != NULL);
	int i;
	struct node *Nodea = p -> head -> next;
	for(i = 0; i < p-> total; i++){
		if(p -> compare(Nodea -> info,item)==0){
			Nodea -> prev -> next = Nodea -> next;
			Nodea -> next -> prev = Nodea -> prev;
			free(Nodea);
			p -> total--;
			break;
		}
		else{
			Nodea = Nodea -> next;
		}
	}
}



void *findItem(LIST *p, void *item){
//if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the com-
//parison function must not be NULL
//Runtime: O(n)	
	assert(p -> compare != NULL);
	assert(item != NULL);
	int i;
	struct node *Nodea = p -> head -> next;
	for(i = 0; i < p -> total; i++){
		if(p -> compare(Nodea -> info, item)==0){
			return Nodea -> info;
		}
		Nodea = Nodea -> next;
	}
	return NULL;
}


void *getItems(LIST *p){
//allocate and return an array of items in the list pointed to by lp
//Runtime: O(n)	
	int i;
	void **arr;
	arr = malloc(sizeof(void*)*p->total);
	struct node *Nodea = p -> head -> next;
	for(i = 0; i < p->total; i++){
		arr[i] = Nodea -> info;
		Nodea = Nodea -> next;
	}
	return arr;
}


