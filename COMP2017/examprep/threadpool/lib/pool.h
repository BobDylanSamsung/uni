#ifndef POOL_H
#define POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

#define QUEUE_SZ 100
#define _POSIX_C_SOURCE 199309L


typedef struct _workitem {
	void* (*action)(void*);
	void* arg;
} workitem_t;

typedef struct _threadpool {
	pthread_mutex_t lock;
	pthread_cond_t alert;

	pthread_t* thread_ids;
	size_t num_threads;

	workitem_t* queue;
	size_t head;
	size_t tail;

	size_t queued;

	bool shutdown;

} threadpool_t;


threadpool_t* threadpool_init(size_t num_threads);


void threadpool_destroy(threadpool_t* pool);


void *thread_work(void* arg);

void queue_work(threadpool_t* pool, void (*action), void* args);

#endif