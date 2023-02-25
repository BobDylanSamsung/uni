#include "summation.h"

int main() {
	char buffer[128];
	int total = 0;

	FILE* fibfile = fopen("fib.txt", "r");

	while (NULL != fgets(buffer, 128, fibfile))
	{
		int x;
		sscanf(buffer, "%d", &x);
		total += x;
		printf("run\n");
	}

	fclose(fibfile);

	printf("Totaal is %d\n", total);
	return 0;
}