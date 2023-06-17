#ifndef MM_H
#define MM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#define WIDTH 4
#define IDX(x, y) ((y) * WIDTH + (x))



typedef struct args {
	int* r;
	int* a;
	int* b;
	int row;
} args_t;

int* generate_random_matrix(void);

void display(const int* matrix);

int* multiply(int* a, int* b);

void* compute_row(void* args);

void compute_entry(int* r, int* a, int* b, int x, int y);


#endif