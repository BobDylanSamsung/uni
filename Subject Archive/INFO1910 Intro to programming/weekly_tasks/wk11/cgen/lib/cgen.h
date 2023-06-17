#ifndef CGEN_H
#define CGEN_H


#include <stdio.h>
#include <stdlib.h>

struct generator {
    int a;
    int b;
    int c;
    int d;
    int e;
    int (*next)();
    int (*call)();
    int id;
};

struct generator make_struct(int* values);
int squares(int x);
int next(struct generator* gen);


#endif