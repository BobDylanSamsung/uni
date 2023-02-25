#include "pool.h"

threadpool_t* threadpool_init(size_t num_threads){
	if (num_threads < 0)
		return NULL;

	threadpool_t* tp = malloc(sizeof(threadpool_t));
	tp->num_threads = num_threads;
	tp->head = 0;
	tp->tail = 0;
	tp->queued = 0;

	tp->thread_ids = malloc(sizeof(pthread_t) * num_threads);
	tp->queue = malloc(sizeof(workitem_t) * QUEUE_SZ);

	tp->shutdown = false;

	if(pthread_mutex_init(&(tp->lock), NULL) != 0){
		perror("Cant initialize mutex");
		threadpool_destroy(tp);
		return NULL;
	}

	if(pthread_cond_init(&(tp->alert), NULL) != 0){
		perror("Cant initialize condition variable");
		threadpool_destroy(tp);
		return NULL;
	}

	for(int i = 0; i < num_threads; i++)
	{
		if(pthread_create(tp->thread_ids + i, NULL, thread_work, (void*) tp) != 0)
		{
			perror("Unable to start threads");
			threadpool_destroy(tp);
			return NULL;
		}
	}

	return tp;
}

void* thread_work(void* arg)
{
	threadpool_t* pool = (threadpool_t*) arg;
	workitem_t task;

	while(!pool->shutdown)
	{
		//if there is no work wait until there is work to do
		if(pool->queued == 0)
		{
			pthread_mutex_lock(&(pool->lock));
			pthread_cond_wait(&(pool->alert), &(pool->lock));
			pthread_mutex_unlock(&(pool->lock));
		}

		else
		{
			pthread_mutex_lock(&(pool->lock));

			task.action = pool->queue[pool->head].action;
			task.arg = pool->queue[pool->head].arg;
			pool->head = (pool->head + 1) % QUEUE_SZ;
			pool->queued--;
			pthread_mutex_unlock(&(pool->lock));


			(*(task.action))(task.arg);
		}
	}

	pthread_exit(NULL);
	return NULL;
}

void queue_work(threadpool_t* pool, void (*action), void* args)
{
	if (pool == NULL || action == NULL)
		return;

	pthread_mutex_lock(&(pool->lock));

	int next = (pool->tail + 1) % QUEUE_SZ;

	if (pool->queued == QUEUE_SZ){
		perror("Queue is full");
		return;
	} 

	pool->queue[pool->tail].action = action;
	pool->queue[pool->tail].arg = args;

	pool->tail = next;
	pool->queued++;

	pthread_cond_signal(&(pool->alert));

	pthread_mutex_unlock(&(pool->lock));
}

void threadpool_destroy(threadpool_t* pool)
{
	if(pool == NULL)
		return;

	pthread_mutex_lock(&(pool->lock));

	pool->shutdown = true;

	pthread_mutex_unlock(&(pool->lock));

	pthread_cond_broadcast(&(pool->alert));

	for(int i = 0; i < pool->num_threads; i++)
	{
		if(pthread_join(pool->thread_ids[i], NULL) != 0)
		{
			perror("Unable to join threads");
		}
	}

	free(pool->thread_ids);
	free(pool->queue);
	pthread_mutex_destroy(&(pool->lock));
	pthread_cond_destroy(&(pool->alert));

	free(pool);

	return;
}

