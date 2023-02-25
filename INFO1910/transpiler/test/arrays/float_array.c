#include <stdio.h>

int main()
{
    float asdf[6] = {3.14,2.718,4.20,500,1.618, 9};

    for(int i = 5; i > -1 ; i--)
    {
        printf("%f\n", asdf[i]);
    }

    return 0;
}