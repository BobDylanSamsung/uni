#include <stdio.h>

int main() 
{
    char* _do_not_use = "oWHl !elordl";
    unsigned _do_not_use_two[] = {2, 6, 3, 11, 0, 4, 1, 8, 9, 7, 10, 5};
    char* point_me_string_literal = _do_not_use;
    unsigned* point_me_offset = _do_not_use_two;


    for(int i = 0; i < 12; i++)
    {
        int index = point_me_offset[i];
        printf("%c", *(point_me_string_literal + index));
    }
    printf("\n");
    return 0;

}