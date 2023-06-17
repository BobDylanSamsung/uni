#include "merge.h"

int main()
{
	srand(time(NULL));

	int* a = random_array(ARRAY_LEN);
	display(a, ARRAY_LEN);
	// int* sorted_a = seq_merge(a, 0, ARRAY_LEN);

	merge_t* merge_data = malloc(sizeof(merge_t));
	pthread_mutex_init(&(merge_data->lock), NULL);
	merge_data->current_threads = 0;
	merge_data->max_threads = 10;

	args_t args = {merge_data, a, 0, ARRAY_LEN};

	int* sorted_a = parallel_merge(&args);

	display(sorted_a, ARRAY_LEN);
	free(a);
	free(sorted_a);
}

void display(int* arr, int len)
{
	printf("[ ");
	for(int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("]\n");
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

void* parallel_merge(void* arguments)
{
	args_t* args = (args_t*) arguments;
	merge_t* merge_data = args->merge_data;
	int* arr = args->arr;
	int start = args->start;
	int end = args->end;

	pthread_mutex_lock(&(merge_data->lock));
	if (merge_data->current_threads == merge_data->max_threads)
	{
		pthread_mutex_unlock(&(merge_data->lock));
		//revert to sequential merge
		return seq_merge(arr, start, end);
	}

	else
	{
		if(end - start == 1)
		{
			int* ret = malloc(sizeof(int));
			*ret = arr[start];
			return ret;
		}

		int middle = (start + end)/2;
		merge_data->current_threads += 2;
		pthread_mutex_unlock(&(merge_data->lock));
		args_t left_args = {merge_data, arr, start, middle};
		args_t right_args = {merge_data, arr, middle, end};
		
		pthread_t left_thread, right_thread;
		void* sorted_left;
		void* sorted_right;
		pthread_create(&left_thread, NULL, parallel_merge, (void*) &left_args);
		pthread_create(&right_thread, NULL, parallel_merge, (void*) &right_args);
		pthread_join(left_thread, sorted_left);
		pthread_join(right_thread, sorted_right);
		int* sorted = merge_arrays(
			(int*) sorted_left,
			middle - start,
			(int*) sorted_right,
			end - middle);

		free(sorted_left);
		free(sorted_right);
		display(sorted, end - start);
		return (void*) sorted;
	}
}


int* seq_merge(int* arr, int start, int end)
{
	if(end - start == 1)
	{
		int* ret = malloc(sizeof(int));
		*ret = arr[start];
		return ret;
	}

	else
	{
		int middle = (start + end)/2;

		int* sorted_left = seq_merge(arr, start, middle);
		int* sorted_right = seq_merge(arr, middle, end);

		int* sorted = merge_arrays(
			sorted_left,
			middle - start, 
			sorted_right,
			end - middle
			);

		free(sorted_left);
		free(sorted_right);

		return sorted;
	}
}

int* merge_arrays(int* left, int l_len, int* right, int r_len)
{
	int* sorted = malloc(sizeof(int) * (l_len + r_len));

	int r = 0;
	int l = 0;

	for(int i = 0; i < l_len + r_len; i++)
	{
		if(l == l_len){
			sorted[i] = right[r];
			r++;
		}

		else if(r == r_len)
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
	}
	return sorted;
}
