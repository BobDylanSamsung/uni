#ifndef COW_H
#define COW_H

#include "animal.h"

struct animal cow_constructor(int efficiency);

void cow_exclaim(struct animal* cow);

void cow_work(struct animal* cow, struct resources* res);

#endif