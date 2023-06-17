#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define BYTE_OFFSET(type, location, i) (*((type)(location + i)))

int hills_multi_var_function(const void* location);

int main()
{
	char* formatstring = "%d %d %d %d";

    //Define new buffer and find number of dimensions

	char newstring[128] = {'\0'};
	int dim = 4;
	//int attempt[4] = {1,2,3,4}

	/*
	for (int x = 0; x < strlen(formatstring); x++)
	{
		switch (formatstring[x])
		{
			case ' ': 
				strncpy(newstring, ' ', 1)

			case 'd':
				strcpy(newstring, s)
		}
		if (formatstring[x] == '%')
		{
			dim += 1;
		}
	}
	*/
	va_list attempt = {1,2,3,4};
	va_start(attempt, dim);
	vsprintf(newstring, formatstring, attempt);
	va_end(attempt);
	printf("%s\n", newstring);


	hills_multi_var_function(newstring);
	return 0;
}

int hills_multi_var_function(const void* location)
{

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


