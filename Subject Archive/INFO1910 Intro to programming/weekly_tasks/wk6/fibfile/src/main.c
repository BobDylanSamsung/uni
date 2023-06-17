#include "main.h"

int main(int argc, char** argv)
{
	int len = atoi(argv[1]);
	int prev = 0, cur = 1, temp;
	FILE* fibfile = fopen("fib.txt", "w+");
	fprintf(fibfile, "%d\n%d\n", 0, 1);
	len -= 2;

	for (int i = 0; i < len; i++)
	{
		temp = cur;
		cur += prev;
		prev = temp;
		fprintf(fibfile, "%d\n", cur);
	}
	fclose(fibfile);

	return 0;
}
