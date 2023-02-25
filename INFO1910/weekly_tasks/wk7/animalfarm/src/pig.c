#include "pig.h"

struct animal pig_constructor(int efficiency) 
{

	struct animal pig;

	pig.legs = 4;
	pig.sound = "oink";
	pig.efficiency = efficiency;
	pig.exclaim = pig_exclaim;
	pig.work = pig_work;

	return pig;
}

void pig_exclaim(struct animal* pig)
{
	printf("%s\n", pig->sound);
	return;
}

void pig_work(struct animal* pig, struct resources* res)
{
	res->pork += pig->efficiency;
	return;
}