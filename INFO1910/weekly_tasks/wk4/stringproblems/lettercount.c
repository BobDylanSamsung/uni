#include <stdio.h>
#include <string.h>

void lettercount(const char* str, int* letters, size_t n);

int main()
{
	char str[] = "the quick brown fox jumps over the lazy dog";
	size_t n = strlen(str);
	int letters[256] = {0};
	lettercount(str, letters, n);
	for (int i = 0; i<256; i++)
	{
		if (letters[i])
		{
			printf("Count for %c is %d\n", (char)i, letters[i]);
		}
	}
}

void lettercount(const char* str, int* letters, size_t n)
{
	for (int i = 1; i < n; i++)
	{
		int num = (int)*(str+i);
		++ letters[num];
	}
	return;
}