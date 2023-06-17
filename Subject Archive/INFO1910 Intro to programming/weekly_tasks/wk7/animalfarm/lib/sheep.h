#ifndef SHEEP_H
#define SHEEP_H

#include "animal.h"
#include "farm.h"

struct animal sheep_constructor(int efficiency); 

void sheep_exclaim(struct animal* sheep);

void sheep_work(struct animal* sheep, struct resources* res);

#endif
