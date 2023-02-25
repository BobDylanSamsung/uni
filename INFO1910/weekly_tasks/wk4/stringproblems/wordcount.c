#include <stdio.h>
#include <string.h>

int wordcount(const char* str, size_t n);

int main()
{
	char str[] = "  This is  a sentance  ";
	size_t n = strlen(str);
	int count = wordcount(str, n);
	printf("%d\n", count);
}

int wordcount(const char* str, size_t n)
{
	int count = 0;
	for (int i = 1; i < n-1; i++)
	{
		printf("test %d uses %c is %d\n", i, *(str+i), (*(str+i) == ' '));
		if ((*(str+i) == ' ')&(*(str + i-1) != ' ')&(*(str+i+1) != ' '))
		{
			count ++;
		}
	}

	return count+1;
}