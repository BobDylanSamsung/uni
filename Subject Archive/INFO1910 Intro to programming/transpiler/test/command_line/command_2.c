#include <stdio.h>
#include <stdlib.h>

int product(int x, int y);

int main(int argc, char** argv){
    int num1 = atoi(argv[1]), num2 = atoi(argv[2]);
    int res = product(num1,num2);
    printf("%d %d\n", num1,num2);
    printf("%d\n", res);
    return 0;
}

int product(int x, int y){return x*y;}
