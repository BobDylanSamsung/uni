#include "lib/main.h"

int main(int argc, char** argv){
    int length = atoi(argv[1]);
    float golden_ratio = fibonacci(length);
    float_print(golden_ratio);
    return 0;
}