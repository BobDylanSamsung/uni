#include "lib/linear.h"

int main()
{
    int x             =  7;

    x = linear_eq(             x);

    printf("%d\n",            x);

    return                0;
}

int linear_eq(int x){return 3*x-1;}