#include <stdio.h>

int main(int argc, char** argv){
	char buf[100];
	while(1){
		fgets(buf, 100, stdin);
		printf("%s", buf);
	}
	return 0;
}

