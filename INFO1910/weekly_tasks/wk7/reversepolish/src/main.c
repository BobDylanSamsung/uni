#include "main.h"

int main(int argc, char** argv)
{
	FILE* operations = fopen("operations.rp", "r");
	char buf[128];

	int total, num1, num2 = 0;
	char first[1];
	char command[8] = {'\0'};

	int (*function_ptr)(int, int);

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
			// total = num1 + num2;
			// printf("ADDING %d and %d gets %d\n", num1, num2, total);
			printf("%c\n", command[0]);
			function_ptr = add;
		}
		if('M' == command[0])
		{
			printf("%c\n", command[0]);
			// total = num1 - num2;
			// printf("SUBTRACTING %d and %d gets %d\n", num1, num2, total);
			function_ptr = sub;
		}
		if('D' == command[0])
		{
			printf("%c\n", command[0]);
			// total = num1/num2;
			// printf("DIVIDING %d and %d gets %d\n", num1, num2, total);
			function_ptr = quo;
		}
		if('T' == command[0])
		{
			printf("%c\n", command[0]);
			// total = num1 * num2;
			// printf("MULTIPLYING %d and %d gets %d\n", num1, num2, total);
			function_ptr = mul;
		}
		total = function_ptr(num1, num2);
	}
	printf("%d\n", total);
	return 0;
}

int add(int num1, int num2)
{
	printf("add %d and %d gets %d\n", num1, num2, num1+num2);
	return num1+num2;
}

int sub(int num1, int num2)
{
	printf("sub %d and %d gets %d\n", num1, num2, num1-num2);
	return num1-num2;
}

int mul(int num1, int num2)
{
	printf("mul %d and %d gets %d\n", num1, num2, num1*num2);
	return num1*num2;
}

int quo(int num1, int num2)
{
	printf("quo %d and %d gets %d\n", num1, num2, num1/num2);
	return(num1/num2);
}
