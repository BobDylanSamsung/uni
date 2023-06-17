#include <stdio.h>

int my_strlen(const char* s){
	int count = 0;
	while (0 != *(s+count)){
		count++;
	}
	return count;
}

int substring(const char* line, const char* substr){
	for(int count = 0; count <= my_strlen(line)- my_strlen(substr); count++){
		int i = 0;
		while( (i <= my_strlen(substr)) & (*(line + count + i) == *(substr + i)) ){
			if(i == my_strlen(substr)){
				return count;
			}
			i++;
		}
	}
	return -1;
	
}

int main(){
	printf("%d\n", substring("monkey", "cat"));
}