#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	int count = 0;
	for (int x = 1; x < argc; x++)
	{
		count += strlen(argv[x]);
	}

	printf("Number of bytes is: %d\n", count);

	return 0;
}