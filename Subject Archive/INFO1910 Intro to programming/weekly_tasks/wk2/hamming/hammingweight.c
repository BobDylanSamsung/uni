#include <stdio.h>

int binaryprint(int n);

int main() {
	int x = 0b10111101010;
	int w = 0b1;
	int count = 0;
	while (w<x) {
		//printf("w: %d\n", (int)w);
		//printf("x: %d\n", (int)x);
		//binaryprint(w);
		//binaryprint(x);
		//int a = x&w;
		//printf("%d\n",a);
		if (!!(x&w) == 1) {
			count += 1;
			//printf("DONE\n");
		}
		w <<= 1;
		
	}
	printf("%d\n", (int)count);
	return 0;
}

int binaryprint(int n) {
	while (n) {
		if (n & 1)
			printf("1");
		else
			printf("0");

		n >>= 1;
	}
	printf("\n");
	return 0;
}

