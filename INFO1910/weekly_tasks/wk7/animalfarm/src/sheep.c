#include "sheep.h"

struct animal sheep_constructor(int efficiency)
{
	struct animal sheep;

	sheep.legs = 4;
	sheep.sound = "baa";
	sheep.efficiency = efficiency;
	sheep.exclaim = sheep_exclaim;
	sheep.work = sheep_work;

	return sheep;
}

void sheep_exclaim(struct animal* sheep)
{
	printf("%s\n", sheep->sound);
	return;
}

void sheep_work(struct animal* sheep, struct resources* res)
{
	res->wool += sheep->efficiency;
	return;
}