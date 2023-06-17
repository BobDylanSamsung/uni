#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Invalid inputs\n");
		return 0;
	}

	int len_1 = strlen(argv[1]);
	int len_2 = strlen(argv[2]);
	int location = atoi(argv[3]);

	char* target = argv[1];
	char* insert = argv[2];

	if (location > len_1)
	{
		printf("Target is beyond the ength ofthe string\n");
	}
	else if (location + len_2 > len_1)
	{
		printf("Not  enough space in target string\n");
	}
	else
	{
		for (int x = 0; x < len_2; x++)
		{
			target[location+x] = insert[x];
		}
		printf("%s\n", target);
	}
	return 0;
}