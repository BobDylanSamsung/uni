#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool AND(int a, int b);

bool AND(int a, int b) {
	bool match = true;
	int dig = 0b00000001;
	int length = log(a)/log(2)+1;
	printf("%d\n", length); 
	for (int n = 1; n < 9; ++n){
		//printf("%d\n", dig);
		//printf("%d\n", a);
		//printf("%d\n", b);
		if((a&dig)!=(b&dig)) {
			match = false;
			//printf("execute\n");
		}
		dig <<= 1;
	}
	return match;
}

int main(){
	bool match = AND(0b10100100, 0b10101010);
	if(match) {
		printf("Match\n");
	}
	else {
		printf("Different\n");
	}
	return 0;
}