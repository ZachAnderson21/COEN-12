#ifndef TABLE_H
#define TABLE_H

typedef struct set SET;

extern SET *createDataSet(int MaxElts);

extern void destroyDataSet(SET *p);

extern int numElements(SET *p);

extern void addID(SET *p, int ID);

extern void removeID(SET *p, int ID);

extern int searchID(SET *p, int ID);

#endif
