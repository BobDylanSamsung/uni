#include "sheep.h"

animal_t sheep_constructor(int efficiency)
{
    animal_t sheep;
    sheep.legs = 4;
    sheep.sound = "BAaaaaa";
    sheep.efficiency = efficiency;
    sheep.exclaim = sheep_exclaim;
    sheep.work = sheep_work;
    return sheep;
}


void sheep_exclaim(animal_t* sheep)
{
    exclaim(sheep);
    return;
}

void sheep_work(animal_t* sheep, resources_t* res)
{
    res->pork += sheep->efficiency;
    return;
}