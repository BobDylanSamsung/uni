#include <stdio.h>

int add_2(int x);

int main(){
    int x = 5;
    x = add_2(x);
    printf("%d\n", x);
    return 0;
}

int add_2(int x){
    x = x + 2;
    return x;
}