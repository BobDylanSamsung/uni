#include "merge_sort.h"

int main() 
{
	srand(time(NULL));

	int* arr = random_array(ARRAY_LEN);

	
	
	display(arr, ARRAY_LEN);
	
	int* sorted_array = merge_sort(arr);

	display(sorted_array, ARRAY_LEN);


	free(arr);
	free(sorted_array);

	return 0;
}

void display(int* arr, int len)
{
	printf("[ ");
	for(int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("]");
}

int* random_array(int n)
{
	int* arr = malloc(sizeof(int) * n);

	for(int i = 0; i < n; i++)
	{
		arr[i] = rand() % MAX_INT;
	}

	return arr;
}

int* merge_sort(int* arr)
{
	threadpool_t* pool = threadpool_init(QUEUE_SZ);
	int* sorted_array = malloc(sizeof(int) * ARRAY_LEN);
	merge_t args = {
		pool,
		arr,
		0,
		ARRAY_LEN,
		sorted_array
	};

	if(sem_init(&(args.complete), 0, 0) != 0){
		perror("Cant initialize semaphore");
		return NULL;
	}

	queue_work(pool, thread_merge_sort, (void*) &args);

	sem_wait(&(args.complete));

	return sorted_array;

}




void* thread_merge_sort(void* arg)
{
	merge_t* args = (merge_t*) arg;
	threadpool_t* pool = args->pool;
	int* arr = args->arr;
	int start = args->start;
	int end = args->end;
	int* sorted = args->sorted;
	sem_t complete = args->complete;
	//int depth = args->depth;

	printf("\n%d %d\n\n", start, end);
	if (start + 1 == end){
		//base case
		printf("basecase %d\n", arr[start]);
		sorted[0] = arr[start];
		if(sem_post(&complete) != 0)
		{
			perror("Unable to post semaphore");
		}
		return NULL;
	}

	int middle = (start + end) / 2;

	int* left = malloc(sizeof(int) * (middle - start));
	int* right = malloc(sizeof(int) * (end - middle));

	merge_t left_args = {
		pool,
		arr,
		start,
		middle,
		left
	};

	if(sem_init(&(left_args.complete), 0, 0) != 0){
		perror("Cant initialize semaphore");
		return NULL;
	}

	merge_t right_args = {
		pool,
		arr,
		middle,
		end,
		right
	};


	if(sem_init(&(right_args.complete), 0, 0) != 0){
		perror("Cant initialize semaphore");
		return NULL;
	}


	queue_work(pool, thread_merge_sort, (void*) &left_args);
	queue_work(pool, thread_merge_sort, (void*) &right_args);

	sem_wait(&left_args.complete);
	sem_wait(&right_args.complete);

	printf("DONE");

	int l = 0;
	int r = 0;

	printf("sorting from %d to %d\n", start, end);
	for(int i = 0; i < end - start; i++)
	{
		if(l == middle - start){
			sorted[i] = right[r];
			r++;
		}

		else if(r == end - middle)
		{
			sorted[i] = left[l];
			l++;
		}

		else if (left[l] < right[r])
		{
			sorted[i] = left[l];
			l++;
		}

		else
		{
			sorted[i] = right[r];
			r++;
		}
		printf("%d ", sorted[i]);
	}

	display(sorted, end - start);

	printf("\n");

	free(left);
	free(right);

	if(sem_post(&complete) != 0)
	{
		perror("Unable to post semaphore");
	}
	return NULL;
}