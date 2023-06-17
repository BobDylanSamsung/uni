#ifndef ANIMAL_H
#define ANIMAL_H

#include <stdio.h>

#include "farm.h"

struct animal
{
	size_t legs;
	char* sound;
	int efficiency;
	void (*exclaim)(struct animal*);
	void (*work)(struct animal*, struct resources*);
};

#endif
