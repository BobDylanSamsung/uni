#ifndef MERGE_H
#define MERGE_H


#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "pool.h"

#define ARRAY_LEN 16
#define MAX_INT 1000

typedef struct _merge_args {
	threadpool_t* pool;
	int* arr;
	int start;
	int end;
	int* sorted;
	sem_t complete;

} merge_t;


void display(int* arr, int len);

int* random_array(int n);

int* merge_sort(int* arr);

void* thread_merge_sort(void* arg);


#endif

/*
merge_t left_args;
	left_args.arr = arr;
	left_args.start = start;
	left_args.end = middle;
	left_args.sorted = left;

	if(pthread_cond_init(&(left_args.complete), NULL) != 0){
		perror("Cant initialize condition variable");
		threadpool_destroy(tp);
		return NULL;
	}

	merge_t right_args;
	right_args.arr = arr;
	right_args.start = middle + 1;
	right_args.end = end;
	right_args.sorted = right;

	if(pthread_cond_init(&(right_args.complete), NULL) != 0){
		perror("Cant initialize condition variable");
		threadpool_destroy(tp);
		return NULL;
	}
*/