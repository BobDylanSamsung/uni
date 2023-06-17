#include "hen.h"

struct animal hen_constructor(int efficiency)
{
	struct animal hen;

	hen.legs = 2;
	hen.sound = "bak bak";
	hen.efficiency = efficiency;
	hen.exclaim = hen_exclaim;
	hen.work = hen_work;

	return hen;
}

void hen_exclaim(struct animal* hen)
{
	printf("%s\n", hen->sound);
	return;
}

void hen_work(struct animal* hen, struct resources* res)
{
	res->eggs += hen->efficiency;
	return;
}