
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define BYTE_OFFSET(type, location, i) (*((type)(location + i)))

int hills_multi_var_function(const void* location);

int main()
{
	char* format = "%d %d %d %d";
	int attempt[4] = {11,2,33,45};
	char array[128];
	memset(array, 0, 128);
	void* buffer = array;
	int count = 0;
	int numint = 0, numfloat = 0, offset = 0, numchar = 0;

	for (int x = 0; x < strlen(format); x++)
	{
		printf("%c\n", format[x]);
		if (format[x] == ' ')
		{
			printf("run\n");
			*(char*)(buffer+offset) = ' ';
			numchar +=1;
		}
		else if (format[x] == 'd')
		{
			printf("run1\n");
			*(int*)(buffer+offset) = attempt[count];
			count += 1;
			numint += 1;
		}
		else if (format[x] == 'c')
		{
			*(char*)(buffer+offset) = (char)attempt[count];
			count += 1;
			numchar += 1;
		}
		else if (format[x] == 'f')
		{
			*(float*)(buffer+offset) = (float)attempt[count];
			count += 1;
			numfloat += 1;
		}
		offset = numchar + 4*numint + 8*numfloat;
	}

	hills_multi_var_function(buffer);
	return 0;
}

int hills_multi_var_function(const void* location)
{
	printf("%p\n", location);
    // Extract the integer from the buffer
    // Null checks were performed in the wrapper

    int a = BYTE_OFFSET(int*, location, (sizeof(int) + 1) * 0);
    int b = BYTE_OFFSET(int*, location, (sizeof(int) + 1) * 1);
    int c = BYTE_OFFSET(int*, location, (sizeof(int) + 1) * 2);
    int d = BYTE_OFFSET(int*, location, (sizeof(int) + 1) * 3);

    printf("%d\t %d\t %d\t %d\n", a, b, c, d);

    int val = - 0.3 * (a - 81) * (a - 26) - 0.3 * (b + 70) * (b + 83) - 0.3 * (c + 16) * (c - 27) - 0.3 * (d + 200) * (d + 250); 

    printf("%d\n", val);
    return val;
}