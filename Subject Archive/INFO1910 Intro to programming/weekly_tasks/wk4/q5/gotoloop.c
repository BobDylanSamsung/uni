#include "gotoloop.h"

int main(int argc, char** argv) 
{
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
	int nums[] = {num1, num2};
	int result = addup(nums);
	printf("%d\n", result);
}

int addup(int* bounds) 
{
	int x = *bounds + 1;

	int sum = 0;

	LOOP: //label

	if (x < *(bounds+1))
	{
		sum += x;

		x++;

		goto LOOP;
	}

	return sum;
}