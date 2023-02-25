#include <stdio.h>

int main() {
    char buffer[1024];

    FILE* file = fopen("hello.txt", "r");

    while (NULL !=fgets(buffer, 1024, file))
    {
        char* asdf;
        fscanf(file, "%s", buffer);
        printf("%s\n", buffer);
    }

    fclose(file);

    return 0;
}