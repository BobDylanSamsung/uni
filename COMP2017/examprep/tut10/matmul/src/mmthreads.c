#include "matrix.h"

int main(void) {
	// Construct the matrices
	int* a = generate_random_matrix();
	int* b = generate_random_matrix();
	
	// Compute the result
	int* r = multiply(a, b);
	
	puts("done");
	display(r);
	free(a);
	free(b);
	free(r);
	return 0;
}

int* generate_random_matrix(void) {
	// Ensure the width is a power of 2
	assert(((WIDTH - 1) & WIDTH) == 0);
	int* result = malloc(WIDTH * WIDTH * sizeof(int));
	for (size_t y = 0; y < WIDTH; ++y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			result[IDX(x, y)] = rand();
		}
	}
	return result;
}


// Displays a matrix.
void display(const int* matrix) {
	for (size_t y = 0; y < WIDTH; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			printf("%4d ", matrix[IDX(x, y)]);
		}
	printf("\n");
	}
}

int* multiply(int* a, int* b)
{
	pthread_t thread_ids[WIDTH];
	args_t thread_args[WIDTH];
	int* r = malloc(WIDTH * WIDTH * sizeof(int));
	for (int i = 0; i < WIDTH; i++)
	{
		thread_args[i].r = r;
		thread_args[i].a = a;
		thread_args[i].b = b;
		thread_args[i].row = i;
		if (pthread_create(thread_ids + i, NULL, compute_row, thread_args+i) != 0) {
			perror("cant create thread");
		}
	}
	return r;
}

void* compute_row(void* args)
{
	args_t* arg = (args_t*) args;
	for(int i = 0; i < WIDTH; i++)
	{
		compute_entry(
			arg->r, 
			arg->a, 
			arg->b, 
			i, 
			arg->row);
	}
	return NULL;
}

//computes the yx entry in r where r = ab
void compute_entry(int* r, int* a, int* b, int x, int y)
{
	int result = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		result += a[IDX(i, y)] * b[IDX(x, i)];
	}

	r[IDX(x,y)] = result;
}