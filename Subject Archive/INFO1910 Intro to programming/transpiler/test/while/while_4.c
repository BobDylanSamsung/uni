#include <stdio.h>

int main()
{
    int asdf = 20;

    while(asdf != 10)
    {
        asdf = asdf - 1;
        int x = asdf/4;
        printf("x i %d",x);
        printf("asdf is %d\n", asdf);
    }
    return 0;
}