#include <stdio.h>

int main() {
	char array = ['a', 'b', 'c', 'd', '\0'];
	int i = 0;
	while (*(array + i) != '\0'){
		printf("i: %d\tchar is %c\tvalue is %d\n",
			i, *(array+i), *(array+i));
		i++;
	}
}