#include <stdio.h>

int main()
{
    int x = 0;
    while (x < 5)
    {

        int y = 0;

        while (y < 2)
        {

            printf("Hello\n");

            x += 1;
            y += 1;
        }

        x += 1;
    } 

	return 0;
}
