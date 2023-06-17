#include <stdio.h>

int my_strlen(const char* s){
	int count = 0;
	while (0 != *(s+count)){
		count++;
	}
	return count;
}

int main(){
	printf("%d\n", my_strlen("Hello"));
	printf("%d\n", my_strlen(""));
	printf("%d\n", my_strlen("123456789"));
	return 0;
}