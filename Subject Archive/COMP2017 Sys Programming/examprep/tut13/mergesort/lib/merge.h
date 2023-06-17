#ifndef MERGE_H
#define MERGE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

#define MAX_INT 1000
#define ARRAY_LEN 128

typedef struct _merge_info {
	pthread_mutex_t lock;
	int max_threads;
	int current_threads;
} merge_t;

typedef struct _thread_args {
	merge_t* merge_data;
	int* arr;
	int start;
	int end;
} args_t;

void display(int* arr, int len);

int* random_array(int n);

int* seq_merge(int* arr, int start, int end);

int* merge_arrays(int* left, int l_len, int* right, int r_len);

void* parallel_merge(void* arguments);

#endif