#include <stdio.h>

char* strncpy(char* dest, const char* src, size_t n);

int main()
{
	char dest[10] = {"\0"};
	strncpy(dest, "Hello world", 10);
	printf("%s\n", dest);
}

char* strncpy(char* dest, const char* src, size_t n)
{
	int i = 0;
	while ((i<n) & (src[i] != "\0"))
	// & (src[i] != "\0")
	{
		//printf("%c\n", src[i]);
		*(dest+i) = *(src+i);
		i++;
	}
	//*(dest+i+1) = "\0";
}