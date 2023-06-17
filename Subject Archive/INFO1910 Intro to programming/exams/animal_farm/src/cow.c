#include "cow.h"

animal_t cow_constructor(int efficiency)
{

    animal_t cow;
    cow.legs = 4;
    cow.sound = "moo";
    cow.efficiency = efficiency;
    cow.exclaim = cow_exclaim;
    cow.work = cow_work;
    return cow;
}


void cow_exclaim(animal_t* cow)
{
    exclaim(cow);
    return;
}

void cow_work(animal_t* cow, resources_t* res)
{
    res->veal += cow->efficiency;
    return;
}