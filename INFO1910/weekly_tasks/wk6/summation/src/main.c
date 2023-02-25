#include "main.h"

int main() {
	char buffer[128];
	int total = 0;
	/*do
	{
		fgets(buffer, 128, stdin);
		printf("%s\n", buffer);
		//total += num;
	} */
	while (NULL != fgets(buffer, 128, stdin))
	{
		total += atoi(buffer);
	}
	printf("Totaal is %d\n", total);
	return 0;
}