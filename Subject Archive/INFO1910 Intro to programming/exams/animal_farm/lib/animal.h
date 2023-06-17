#ifndef ANIMAL_H
#define ANIMAL_H

typedef struct animal_struct animal_t;


#include "resources.h"
#include "farm.h"
#include <stdlib.h>
#include <stdio.h>


struct animal_struct {
    size_t legs;
    char * sound;
    int efficiency;
    void (*exclaim)(animal_t*);
    void (*work)(animal_t*, resources_t*);
};

void exclaim(animal_t* species);

void work(animal_t* species, resources_t* resources);

void animal_constructor(farm_t* farm, int i, int spot);

#endif