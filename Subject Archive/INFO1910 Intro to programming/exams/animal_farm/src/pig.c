#include "pig.h"

animal_t pig_constructor(int efficiency)
{
    animal_t pig;
    pig.legs = 4;
    pig.sound = "OINK";
    pig.efficiency = efficiency;
    pig.exclaim = pig_exclaim;
    pig.work = pig_work;
    return pig;
}


void pig_exclaim(animal_t* pig)
{
    exclaim(pig);
    return;
}

void pig_work(animal_t* pig, resources_t* res)
{
    res->pork += pig->efficiency;
    return;
}