#include <stdio.h>
#include <string.h>

int main()
{
	char* format = "%d %d %d %d";


	//get dimension of input
	int dim = 0;

	for (int x = 0; x < strlen(format); x++)
	{
		if (format[x] == '%')
		{
			dim += 1;
		}
	}

	//get attempt coordinates
	int attempt[4] = {1,2,3,4};


	//format buffer 
	int index = 0;

	int count = 0;

	char tempstr[128] = {'\0'};

	int numint = 0, numfloat = 0;

	//int offset = 0;

	char buffer[128];
	memset(buffer, ' ', 128);

	for (int x = 0; x < strlen(format); x++)
	{
		strncat(tempstr,format+index,1);
		if (format[index] == ('d'|'f'|'c'))
		{
			printf("%d\n", index);
			sprintf((buffer+index), tempstr, attempt[count]);
			index += strlen(tempstr);
			memset(tempstr, 0, 128);

			count += 1;

			switch (format[index])
			{
				case 'd':
					numint += 1;
				case 'f':
					numfloat += 1;
			}
			//offset = numint*4 + numfloat*8 - (numint + numfloat);
		}
	}



	printf("%s\n", buffer);



	sprintf(buffer, format, 7);

	printf("%s\n", buffer);

	sprintf(buffer, format, 8);

	printf("%s\n", buffer);

	printf("\n");

	return 0;
}