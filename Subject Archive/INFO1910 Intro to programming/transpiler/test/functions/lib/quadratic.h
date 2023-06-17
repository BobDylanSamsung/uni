#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "linear.h"

float quadratic_eq(float num){
    num = linear_eq(num);
    float y = (num*num +2*num -3.7)/ 2.9;
    return y;
}

#endif