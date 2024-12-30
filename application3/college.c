//Zach Anderson
//6/7/2023
//term project
//Application3
//Main function for application3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define NUM_STUDENTS 1000

int main(){
	srand(time(NULL));
	LIST *p = createDataSet();
	int id;
	int age;
	int i;
	int increment;
	id = 0;
	for(i = 0; i < NUM_STUDENTS;i++){
		age = (rand() % 13) + 18;
		increment = (rand() % 2) + 1;
		id += increment;
		insertion(p, id, age);
	}
	printf("Insertion has been completed\n");
	int randID;
	randID = (rand() % (2000)) + 1;
	searchAge(p, age);
	if(searchID(p, randID) != -1) deletion(p, randID);
	maxAgeGap(p);
	destroyDataSet(p);
	return 0;
}
