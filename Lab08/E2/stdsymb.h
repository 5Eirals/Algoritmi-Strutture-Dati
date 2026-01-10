#ifndef STDSYMB_H
#define STDSYMB_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 63

typedef char* str;
typedef enum { false, true } bool;
typedef struct vertex_s {
    str id;
    str subnet;
} vertex;

#endif //STDSYMB_H
