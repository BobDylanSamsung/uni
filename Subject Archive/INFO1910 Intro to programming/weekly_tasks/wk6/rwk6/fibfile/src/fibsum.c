#include "fibsum.h"


int main()
{
	FILE* fibfile = fopen("fib.txt", "r");

	char buffer[128];
	int total = 0, cur;
	do 
	{
		sscanf(buffer, "%d\n", &cur);
		total += cur;
		printf("%d\n", cur);
	}while(NULL != fgets(buffer, 128, fibfile));

	printf("total is %d\n", total);
	return 0;
}