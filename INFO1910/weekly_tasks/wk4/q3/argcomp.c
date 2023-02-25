#include <stdio.h>

int main(int argc, char** argv) 
{
	if ((4 < argc) & (argc !=8))
	{
		printf("condition 1\n");
	}
	else if ((4 > argc) & (argc !=2))
	{
		printf("condition 2\n");
	}
	else if (4 == argc)
	{
		printf("condition 3\n");
	}
	else if (8 == argc)
	{
		printf("condition 4\n");
	}
	else if (2 == argc)
	{
		printf("condition 5\n");
	}
	else
	{
		printf("condition 6\n");
	}

	return 0;
}