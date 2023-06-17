#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc < 4) {
		printf("Not enough arguments\n");
		return 0;
	}

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	char *z = argv[3];
	//printf("x is %d\t y is %d\t operator is %c\n",
	//	x, y, *z);
	int num;
	//int num = x - y;
	//printf("%d\n", num);

	if (*z == '/') {
		//printf("run 1 %c\n", *z);
		float num;
		num = (float)x/y;
		printf("%f\n", num);
	}
	else {
		if (*z == '+') {
			//printf("run 2 %c\n", *z);
			num = x + y;
		}

		if (*z == '-') {
			//printf("run 3 %c\n", *z);
			num = x - y;
		}

		if (*z == 'c') {
			//printf("run 4 %c\n", *z);
			num = x * y;
		}
		printf("%d\n", num);
	}
	return 0; 
}