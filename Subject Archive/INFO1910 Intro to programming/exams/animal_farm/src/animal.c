#include "animal.h"


void exclaim(animal_t* species)
{
    printf("%s\n", species->sound);
    return;
}

void work (animal_t* species, resources_t* res)
{
    species->work(species, res);
    return;
}

void animal_constructor(farm_t* farm, int i, int spot)
{
    farm->animals[spot] = farm->constructors[i](farm);
    return;
}