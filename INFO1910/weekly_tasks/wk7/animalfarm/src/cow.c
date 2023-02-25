#include "cow.h"

struct animal cow_constructor(int efficiency) 
{
	struct animal cow;

	cow.legs = 4;
	cow.sound = "moo";
	cow.efficiency = efficiency;
	cow.exclaim = cow_exclaim;
	cow.work = cow_work;

	return cow;
}

void cow_exclaim(struct animal* cow)
{
	printf("%s\n", cow->sound);
	return;
}

void cow_work(struct animal* cow, struct resources* res)
{
	res->milk += cow->efficiency;
	return;
}