#include <stdio.h>
/*
* mem_swap
* Swaps the memory between the two specified integer pointers
* :: int* a :: The first pointer to swap
* :: int* b :: The second pointer to swap
* Returns nothing, swaps occur in place
*/
void mem_swap(int* a, int * b);

int main() {
	int a = 5;
	int b = 7;

	printf("%d %d\n", a, b);

	mem_swap(&a,&b);

	printf("%d %d\n",a, b);
}

void mem_swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}