#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Invalid input\n");
		return 0;
	}

	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);

	char operator = argv[3][0];

	printf("%c\n", operator);

	switch(operator)
	{
		case '+':
			printf("%d\n", num1+num2);
			break;

		case '-': 
			printf("%d\n", num1-num2);
			break;

		case '*':
			printf("%d\n", num1*num2);
			break;

		case '/':
			printf("%f\n", (float)num1/num2);
			break;

		default:
			printf("invalid operator\n");
	}

	return 0;
}