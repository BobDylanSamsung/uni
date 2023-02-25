#include <stdio.h>

int add_1(int x){
    return x + 1;
}


int main()
{
    int x = 4;
    x = add_1(x);
    printf("%d\n", x);
    return 0;
}