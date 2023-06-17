#include "rom_num.h"

int main()
{
    int num, len = 0;

    printf("Enter Number: \n");
    scanf("%d", &num);

    printf("%d is:\t", num);
    char roman[128];


    while(num > 0)
    {
        if (num >= 1000)
        {
            num -= 1000;
            roman[len] = 'M';
        }

        else if (num >= 900)
        {
            num -= 900;
            roman[len] = 'C';
            len += 1;
            roman [len] = 'M';
        }        

        else if (num >= 500)
        {
            num -= 500;
            roman[len] = 'D';
        }

        else if (num >= 400)
        {
            num -= 400;
            roman[len] = 'C';
            len += 1;
            roman [len] = 'D';
        }

        else if (num >= 100)
        {
            num -= 100;
            roman[len] = 'C';
        }

        else if (num >= 90)
        {
            num -= 90;
            roman[len] = 'X';
            len += 1;
            roman [len] = 'C';
        }

        else if (num >= 50)
        {
            num -= 50;
            roman [len] = 'L';
        }

        else if (num >= 40)
        {
            num -= 40;
            roman[len] = 'X';
            len += 1;
            roman [len] = 'L';
        }

        else if (num >= 10)
        {
            num -= 10;
            roman[len] = 'X';
        }

        else if (num >= 9)
        {
            num -= 9;
            roman[len] = 'I';
            len += 1;
            roman [len] = 'X';
        }

        else if (num >= 5)
        {
            num -= 5;
            roman[len] = 'V';
        }

        else if (num >= 4)
        {
            num -= 4;
            roman[len] = 'I';
            len += 1;
            roman [len] = 'V';
        }

        else if (num >= 1)
        {
            num -= 1;
            roman[len] = 'I';
        }

        len += 1;
    }

    printf("%s\n", roman);

    return 0;
}    
