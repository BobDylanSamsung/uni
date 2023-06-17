#ifndef RESOURCES_H
#define RESOURCES_H

typedef struct resources_struct resources_t;

#include <stdlib.h>

resources_t make_resources();

struct resources_struct 
{
    size_t pork;
    size_t veal;
    size_t wool;
    size_t eggs;
};

#endif