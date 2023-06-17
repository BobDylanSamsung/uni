#ifndef HEN_H
#define HEN_H

#include "animal.h"
#include "resources.h"


animal_t hen_constructor(int efficiency);

void hen_exclaim(animal_t* hen);

void hen_work(animal_t* hen, resources_t* res);


#endif