#include "bubblesort.h"

int main() {

	for(int i = 0; i < 10; i++)
	{
		int* a = random_array();
		display(a);
		bubblesort(a);
		display(a);

		free(a);

	}
		return 0;
}

int* random_array() {
	int* arr = malloc(LEN * sizeof(int));

	for (int i = 0; i < LEN; i++)
	{
		arr[i] = rand() % 10000;
	}

	return arr;
}

void display(int* arr)
{
	printf("[");
	for (int i = 0; i < LEN; i++)
	{
		if (i != 0)
			printf(",");
		printf(" %d", arr[i]);
	}
	printf(" ]\n");
}

void bubblesort(int* arr)
{
	pthread_t thread_ids[LEN];
	pthread_mutex_t mutexes[LEN] = {PTHREAD_MUTEX_INITIALIZER};
	args_t* args = malloc(sizeof(args_t));
	args->mutexes = mutexes;
	args->arr = arr;

	for (int i = 0; i < LEN; i++)
	{
		pthread_create(thread_ids + i, NULL, worker, args);
	}

	for (size_t i = 0; i < LEN; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	free(args);
}

void* worker(void* arg)
{

	int* arr = ((args_t*)arg)->arr;
	pthread_mutex_t* mutexes = ((args_t*)arg)->mutexes;

	for(int i = 0; i < LEN - 1; i++)
	{
		if(arr[i] > arr[i+1])
		{
			int order[] = {0, 1, -1};
			int start[] = {0, 2, 1};
			if (i == 0)
			{
				pthread_mutex_lock(mutexes);
				pthread_mutex_lock(mutexes + 1);
			}

			else
			{
				for (int j = 0; j < 3; j++)
				{
					int index = i + order[(start[i % 3] + j) % 3];
					//printf("locking mutex %d", index);
					pthread_mutex_lock(mutexes + index);
				}
			}

			if (arr[i] > arr[i + 1])
			{
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}

			if (i == 0)
			{
				pthread_mutex_unlock(mutexes);
				pthread_mutex_unlock(mutexes + 1);
			}

			else
			{
				for (int j = 0; j < 3; j++)
				{
					int index = i + order[(start[i % 3] + j) % 3];
					//printf("unlocking mutex %d", index);
					pthread_mutex_unlock(mutexes + index);
				}
			}

		}
	}
	return NULL;
}