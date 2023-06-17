#include <stdio.h>

int main()
{
    char* _do_not_use = "Hello World!";
    char** point_me_right = &_do_not_use;

    printf("%s\n", *point_me_right);
}