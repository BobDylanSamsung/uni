#include "lib/quadratic.h"

int main(){
    float x = quadratic_eq(4);
    printf("%f\n", x);
    return 0;
}

int linear_eq(int s){return 4*s - 11;}