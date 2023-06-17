#include "main.h"

int main(int argc, char** argv)
{
	FILE* operations = fopen("operations.rp", "r");
	char buf[128];

	int total, num1, num2 = 0;
	char first[1];
	char command[8] = {'\0'};

	while (NULL != fgets(buf, 128, operations))
	{
		sscanf(buf, "%s %d %s", first, &num2, command);
		if ((char)*first != '%')
		{
			num1 = atoi(first);
		}
		else
		{
			num1 = total;
		}


		if('A' == command[0])
		{
			total = num1 + num2;
			printf("ADDING %d and %d gets %d\n", num1, num2, total);
		}
		if('M' == command[0])
		{
			total = num1 - num2;
			printf("SUBTRACTING %d and %d gets %d\n", num1, num2, total);
		}
		if('D' == command[0])
		{
			total = num1/num2;
			printf("DIVIDING %d and %d gets %d\n", num1, num2, total);
		}
		if('T' == command[0])
		{
			total = num1 * num2;
			printf("MULTIPLYING %d and %d gets %d\n", num1, num2, total);
		}
	}
	printf("%d\n", total);
	return 0;
}
