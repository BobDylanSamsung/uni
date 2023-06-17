#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
	char y[5] = argv[1];
	char *z = argv[2];
	printf("y is %c\t z is %c\n", *y, *z);
	//printf("the product is %d\n", (y*z));
	return 0;
}