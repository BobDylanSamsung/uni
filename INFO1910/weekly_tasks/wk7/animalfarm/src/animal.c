#include "animal.h"

void exclaim(struct animal* species)
{
	species->exclaim(species);
	return;
}

void work(struct animal* species, struct resources* res)
{
	species->work(species, res);
	return;
}