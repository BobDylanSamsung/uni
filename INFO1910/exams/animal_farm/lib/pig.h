#ifndef PIG_H
#define PIG_H

#include "animal.h"
#include "resources.h"


animal_t pig_constructor(int efficiency);

void pig_exclaim(animal_t* pig);

void pig_work(animal_t* pig, resources_t* res);


#endif