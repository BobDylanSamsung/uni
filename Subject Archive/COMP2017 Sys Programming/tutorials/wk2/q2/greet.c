#include <stdio.h>

int main(int argc, char** argv){
	char* name[20];
	printf("What is your name?: ");
	scanf("%s", name);
	printf("%s %s\n", argv[1], name);
	return 0;
}


