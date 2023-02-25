#ifndef HEN_H
#define HEN_H

#include "animal.h"


struct animal hen_constructor(int efficiency);

void hen_exclaim(struct animal* hen);

void hen_work(struct animal* hen, struct resources* res);

#endif
