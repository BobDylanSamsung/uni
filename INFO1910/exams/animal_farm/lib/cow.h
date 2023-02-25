#ifndef COW_H
#define COW_H

#include "animal.h"
#include "resources.h"

typedef struct animal_struct animal_t;


animal_t cow_constructor(int efficiency);

void cow_exclaim(animal_t* cow);

void cow_work(animal_t* cow, resources_t* res);


#endif