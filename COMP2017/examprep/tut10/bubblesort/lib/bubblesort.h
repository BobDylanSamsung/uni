#ifndef BUBBLE_H
#define BUBBLE_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100

typedef struct args {
	pthread_mutex_t* mutexes;
	int* arr;
} args_t;

int* random_array();

void display(int* arr);

void bubblesort(int* arr);

void* worker(void* arg);


#endif