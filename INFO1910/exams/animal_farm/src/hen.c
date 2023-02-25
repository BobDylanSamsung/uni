#include "hen.h"

animal_t hen_constructor(int efficiency)
{
    animal_t hen;
    hen.legs = 2;
    hen.sound = "bak bak";
    hen.efficiency = efficiency;
    hen.exclaim = hen_exclaim;
    hen.work = hen_work;
    return hen;
}


void hen_exclaim(animal_t* hen)
{
    exclaim(hen);
    return;
}

void hen_work(animal_t* hen, resources_t* res)
{
    res->eggs += hen->efficiency;
    return;
}