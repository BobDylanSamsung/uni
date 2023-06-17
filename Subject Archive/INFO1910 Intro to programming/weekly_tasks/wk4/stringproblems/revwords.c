#include <stdio.h>
#include <string.h>

void revorder(const char* str, char* newstring, size_t n);

int main()
{
	char str[] = "dogs and cats";
	//"Eat ass smoke grass sled fast";
	size_t n = strlen(str);
	char newstring[13] = {'\0'};
	revorder(str, newstring, n);
	printf("%s\n", newstring);
}

void revorder(const char* str, char* newstring, size_t n)
{
	//int offset = 0;
	//printf("")
	int offset = n-1;
	for (int i = n-1; i >= 0; i--)
	{
		//printf("%d\t %d\t %c\n", (int)n, i, str[i]);
		if (str[i] == ' '|i==0)
		{
			
			
			//while (n-i>offset-i)
			for (int x = 1; x <= offset -i; x++)
			{
				//printf("run2\n");
				newstring[n-offset+x-2] = str[i+x];
				newstring[n-offset+x-1] = ' ';
				printf("%d, %c\t %d, %c\n", (int)n-offset+x-2, newstring[n-offset+x] , i+x, str[i+x]);
			}
			//newstring[offset - i] = ' ';
			offset = (int)strlen(newstring);

			//offset = i-1;

		} 
	}
	newstring[n] = '\0';
	printf("%s\n", newstring);
	return;
}