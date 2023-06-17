#include <stdio.h>
#include <stdlib.h>

void fib(int length);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("not enough inputs\n");
		return 0;
	}
	else if (argc > 2)
	{
		printf("too many inputs\n");
		return 0;
	}

	int len = atoi(argv[1]);

	fib(len);

	return 0; 
}

void fib(int length)
{
	double current = 0;
	double next = 1;
	int count = 2;
	double temp;

	printf("%f\t %f\t", current, next);

	LOOP: //label

	temp = next;

	next += current;

	current = temp;

	printf("%f\t", next);

	count ++;

	if (count < length)
	{
		goto LOOP;
	}
	printf("Golden ratio is: %f\n", (float)next/current);
}