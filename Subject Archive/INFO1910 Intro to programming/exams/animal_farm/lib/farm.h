#ifndef FARM_H
#define FARM_H


typedef struct farm farm_t;


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "cow.h"
#include "sheep.h"
#include "hen.h"
#include "pig.h"
#include "resources.h"


struct farm {
    animal_t* animals;
    animal_t (*constructors[4])();
    resources_t resources;
    void (*construct)(); 
    void (*exclaim)();
    void (*work)();
    void (*stockhold)();
};

void initialise_farm(farm_t* farm, animal_t* animals);

void farm_exclaim(farm_t* farm);

void farm_work(farm_t* farm);

void farm_stockhold(farm_t* farm);



#endif