#include <stdio.h>
#include <string.h>

size_t free_strlen(char* str) {
    size_t i = 0;

    while (*(str + i) != '\0')
    {
        i++;
    }

    return i;    
}


int main(void) {
    char* str = "Hello World!\n";
    for (int i = 0; i < free_strlen(str); i++) {
        putchar(str[i]);
    }
    printf("%d\n", free_strlen(str) == strlen(str));
    return 0;
}