#include "farm.h"

int main()
{
    farm_t farm;

    animal_t animals[128];

    initialise_farm(&farm, animals);

    srandom(time(NULL));

    for (int i; i < 128; i++)
    {
        farm.construct(&farm, random() % 4, i);
    }

    farm.exclaim(&farm);

    farm.work(&farm);

    farm.stockhold();

    return 0;
}

void initialise_farm(farm_t* farm, animal_t animals[128])
{
    farm->animals = animals;

    farm->resources = make_resources();

    animal_t (*constructors[4])() = {cow_constructor,hen_constructor, sheep_constructor, pig_constructor};
    for (int i =0; i < 4; i++)
    {
        farm->constructors[i] = constructors[i];
    }

    farm->construct = animal_constructor;
    farm->exclaim = farm_exclaim;
    farm->work = farm_work;
    farm->stockhold = farm_stockhold;
    return;
}

void farm_exclaim(farm_t* farm)
{
    for(int i = 0; i < 128; i++)
    {
        farm->animals[i].exclaim(&(farm->animals[i]));
    }
    return;
}

void farm_work(farm_t* farm)
{
    for (int i = 0; i < 128; i++)
    {
        farm->animals[i].work(&(farm->animals[i]), &(farm->resources));
    }
    return;
}

void farm_stockhold(farm_t* farm)
{
    printf("Pork is: %lu\n", farm->resources.pork);
    printf("Veal is: %lu\n", farm->resources.veal);
    printf("Eggs is: %lu\n", farm->resources.eggs);
    printf("Wool is: %lu\n", farm->resources.wool);
    return;
}