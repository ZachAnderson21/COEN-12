//Zach Anderson
//6/7/2023
//Term Project
//Application2 main function


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "table.h"

#define NUM_STUDENTS 3000

int main(){
	int i;
	int age;
	int id;
	int increment;
	id = 0;

	srand(time(NULL));
	SET *p = createDataSet(NUM_STUDENTS);
	for(i = 0; i < 1000; i++){
		age = (rand() % 13) + 18;
		increment = (rand() % 2) + 1;
		id += increment;
		addID(p, id);
	}
	printf("Insert has been completed\n");
	int randID;
	randID = (rand() % 3001) + 1;
	removeID (p, randID);
	destroyDataSet(p);
	return 0;
}


