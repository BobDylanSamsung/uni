#ifndef FARM_H
#define FARM_H

#include <stdlib.h>
#include <time.h>

#include "animal.h"

struct resources
{
	size_t milk;
	size_t wool;
	size_t eggs;
	size_t pork;
};

void workday(struct animal* farm, struct resources* res);

#endif
