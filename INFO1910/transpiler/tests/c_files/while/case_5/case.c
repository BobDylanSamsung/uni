#include <stdio.h>

int main()
{
    int x = 10;
    int y;
    while (y = x - 3)
    {
        printf("%d\n", y);
        x -= 1;
    } 

	return 0;
}
