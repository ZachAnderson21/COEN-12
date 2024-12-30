//Zach Anderson
//6/7/2023
//term project
//Application3
//I used linked lists to go about managing all kinds of data about various college students 


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node{
	int age;
	int id;
	struct node *next;
	struct node *prev;
} NODE;

typedef struct list{
	int min;
	int max;
	int count;
	NODE *head;
} LIST;

LIST *createDataSet(){
//Creates the list
	LIST *p = malloc(sizeof(LIST));
	assert(p != NULL);
        p->count = 0;
        p->min = 30;
	p->max = 18;
        p->head = malloc(sizeof(NODE));
        p->head->next = p->head;
        p->head->prev = p->head;
        p->head->age = -1;
        printf("Data structure has been created\n");
        return p;3
}
void destroyDataSet(LIST *p){
//frees all allocated data
	assert(p != NULL);
	NODE* temp1 = p->head;
        NODE* temp2 = p->head;
        do{
        	temp2 = temp1->next;
        	free(temp1);
        	temp1 = temp2;
        } 
	while(temp1 != p->head);
    		free(p);
    		printf("The data has been freed\n");
}

int searchAge(LIST *p, int age){
//searches for people at a specific age
	assert(p != NULL);
        NODE* temp = p->head->next;
        printf("Searching for age: %d\n", age);
        int i;
        int found; 
	found = 0;
        for(i = 0; i < p->count; i++) {
        	if(temp->age == age) {
                	printf("Student of age %d found. ID:%d\n", age, temp->id);
                        found = 1;
       		}
        temp = temp->next;
        }
        if(found != 0){
		printf("Search has been completed\n");
    	}
	else{
		printf("Search completed, no student of sge:%d was found.\n", age);
        }
	return -1;
}

int searchID(LIST *p, int id){
//search the list to find a matching ID 
	assert(p != NULL);
        NODE* temp = p->head->next;
        printf("Searching for ID: %d.\n", id);
        int i;
        for(i = 0; i < p->count; i++) {
        	if(temp->id == id) {
                	printf("Student of ID %d found. There age is:%d\n", id, temp->age);
                 	return temp->id;
        }
        temp = temp->next;
    }
    printf("Search was unsuccessful, student was not found\n");
    return -1;
}

void insertion(LIST *p, int id, int age){
//inserts an item into the list (Specifically at the back.)
	assert(p != NULL);
        NODE* temp = malloc(sizeof(NODE));
        temp->age = age;
        temp->id = id;
        if(age > p->max){
		p->max = age;
	}
    	else if (age < p->min){ 
		p->min = age;
	}
        else;
        printf("Inserting student %d, ID:%d, Age:%d\n", p->count+1, id, age);
        temp->next = p->head;
        temp->prev = p->head->prev;
        p->head->prev->next = temp;
        p->head->prev = temp;
        p->count++;
        printf("Student insert was successful\n");
	
}

void deletion(LIST *p, int id){
//deletes an item from the list
	assert(p != NULL);
	int i;
        NODE* temp = p->head->next;
        printf("Deleting student ID:%d\n", id);
        for(i = 0; i < p->count; i++) {
        	if(temp->id == id) {
                	temp->next->prev = temp->prev;
            		temp->prev->next = temp->next;
            		free(temp);
            		p->count--;
           		printf("Student deletion was successful\n");
            		return;
        }
        temp = temp->next;
    }
    printf("Student deletion was unsuccessful\n");
}

int maxAgeGap(LIST *p){
//finds the max age gap
	assert(p != NULL);
	printf("The max age gap is %d\n",(p->max - p->min));
	return p->max-p->min;
}
