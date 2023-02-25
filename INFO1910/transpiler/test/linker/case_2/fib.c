#include "lib/fib.h"

float fibonacci (int length){
    float prev = 0;
    float cur = 1;
    length -= 2;

    printf("%.0f\t", prev);
    printf("%.0f\t", cur);
    while (length > 0)
    {
        int temp = cur;
        cur += prev;
        prev = temp;
        length = length -1;
        printf("%.0f\t", cur);
    }

    printf("\n");

    float gr = cur/prev;

    return gr;
}