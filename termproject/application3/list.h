#ifndef LIST_H
#define LIST_H

typedef struct list LIST;

typedef struct node NODE;

extern LIST *createDataSet();

extern void destroyDataSet(LIST *p);

extern int searchAge(LIST *p, int age);

extern int searchID(LIST *p, int id);

extern void insertion(LIST *p, int id, int age);

extern void deletion(LIST *p, int id);

extern int maxAgeGap(LIST *p);

#endif
