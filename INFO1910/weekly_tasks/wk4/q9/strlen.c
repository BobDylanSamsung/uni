#include <stdio.h>
#include <string.h>

int forlen(char* str);

int whilelen(char* str);

int dowhilelen(char* str);

int main()
{
	char str[] = "Eat as smoke grass sled fast";
	int length = strlen(str);

	printf("expected length is\t %d\n", length);

	printf("while length is\t %d\n", whilelen(str));

	printf("for length is\t %d\n", forlen(str));

	printf("do while length is\t %d\n", dowhilelen(str));

	return 0;
}

int forlen(char* str)
{
	int len = 0;
	for (int x = 0; str[x] != '\0'; x++)
	{
		len++;
	}
	return (len);
}

int whilelen(char* str)
{
	int x = 0;
	while (str[x] != '\0')
	{
		x++;
	}
	return x;
}

int dowhilelen(char* str)
{
	int x = 0;
	do
	{
		x++;
	} while (str[x] !='\0');
	return x;
}