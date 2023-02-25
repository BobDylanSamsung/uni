#include <stdio.h>
#include <stdlib.h>

void fib(int n, int* num1, int* num2);

int main(int argc, char** argv) 
{
	if (argc > 2)
	{
		printf("Too many inputs\n");
		return 0;
	}
	else if (argc < 2)
	{
		printf("Too few inputs\n");
		return 0;
	}
	int len = atoi(argv[1]);
	if (len)
	{
		int prev = 0;
		int cur = 1;
		int* num1 = &(prev);
		int* num2 = &(cur);
		fib(len, num1, num2);
		printf("num2 as int: %d\t num2 as float: %f\n num1 as int: %d\n",*num2, (float)*num2, *num1);

		float gr = (float)*num2/(*num1);
		printf("Golden ratio for length is %f\n", gr);
	}
	return 0;

}

void fib(int len, int* num1, int* num2) 
{
	int prev = 0;
	int cur = 1;
	printf("0\t");
	for (int x = 0; x < (len-1); x++)
	{
		printf("%d\t", cur);
		int temp = prev;
		prev = cur;
		cur = prev + temp;
	}
	printf("\n");
	*num1 = (prev);
	*num2 = (cur);

	return;
}
