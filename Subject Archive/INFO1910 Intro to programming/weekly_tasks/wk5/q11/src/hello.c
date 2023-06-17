#include "hello.h"

char* hello(char* greeting)
{
	srand(time(0));
	int x = rand();
	x = x % 3;
	switch (x)
	{
		case(0):
			strcpy(greeting, "Sled fast");
			break;
		case(1):
			strcpy(greeting, "Eat ass");
			break;
		case(2):
			strcpy(greeting, "Smoke grass");
			break;
	}
	return greeting;
}
