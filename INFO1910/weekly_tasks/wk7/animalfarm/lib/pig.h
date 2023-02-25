#ifndef PIG_H
#define PIG_H

#include "animal.h"

struct animal pig_constructor(int efficiency);

void pig_exclaim(struct animal* pig);

void pig_work(struct animal* pig, struct resources* res);

#endif