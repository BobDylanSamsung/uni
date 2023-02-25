#include "palindrome.h"

int main()
{
    int num1 = 100, num2 = 100, largest = 0, factor1, factor2;

    while(num1 < 1000)
    {
        while (num2 < 1000)
        {
            int result = num1 * num2;

            if ((result > largest) & check_pal(result))
            {
                largest = result;
                factor1 = num1;
                factor2 = num2;
            }

            num2++;
        }
        num1++;
        num2 = num1 + 1;
    }

    printf("%d times %d gives %d\n", factor1, factor2, largest);

    return 0;
}

int check_pal(int num)
{
    char string[128];
    sprintf(string, "%d", num);

    int pal = 1, len = strlen(string);
    for(int i = 0; i < len; i++)
    {
        if(string[i] != string[len-i-1])
        {
            pal = 0;
        }
    }
    return pal;
}