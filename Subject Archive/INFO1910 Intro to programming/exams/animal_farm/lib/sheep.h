#ifndef SHEEP_H
#define SHEEP_H

#include "animal.h"
#include "resources.h"


animal_t sheep_constructor(int efficiency);

void sheep_exclaim(animal_t* sheep);

void sheep_work(animal_t* sheep, resources_t* res);


#endif