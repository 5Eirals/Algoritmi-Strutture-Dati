#ifndef ST_H
#define ST_H

#include "edge.h"


typedef struct st_s *ST;


ST STinit();
void STfree(ST st);
void STinsert(ST st, vertex val);
void STprint(FILE *f, ST st);
int STsize(ST st);
int STsearch(ST st, str val);
str STgetValue(ST st, int key);
void STdelete(ST st, int key);

#endif
