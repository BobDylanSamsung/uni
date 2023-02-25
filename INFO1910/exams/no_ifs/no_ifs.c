#include <stdio.h>

int no_ifs(int a, int b, int c);


int main()
{
    
    int inputs[3];
    scanf("%d %d %d", inputs, inputs + 1, inputs + 2);
    
    // Call the no_ifs function and print the result
    int result = no_ifs(inputs[0], inputs[1], inputs[2]);
    printf("%d\n", result);
    
    // Returns 0
    return 0;
}


/*
 * no_ifs
 * A function that performs some sample switches without if statements
 *
 * If all three arguments are identical, then return 0
 * If all three arguments are different, then return the product of the arguments
 * If one arguments differs from the other two, return the value of the differing argument
 *
 * :: int a :: The first input
 * :: int b :: The second input
 * :: int c :: The third input
 *
 * Returns the integer that results from the above logic
 */
int no_ifs(int a, int b, int c)
{
    int all3 = (a == b) * (a == c);

    int same2 = 1 == ((a == b) + (a == c) + (b == c));

    int different = (a != b) & (b != c) & (a != c);

    int result = same2 * (a^b^c) + different * (a * b * c);

    //(!(a&b) + !(a&c) + b!(&c))*a*b*c + a
    //printf("%d\n", result);

    //printf("%d\n" !(a^))
    return result;
}