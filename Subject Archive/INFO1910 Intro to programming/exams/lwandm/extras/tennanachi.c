#include <stdio.h>
#include <stdlib.h>

... tennanachi(... n) {
    // TODO: implement tennanachi(n) with reasonable types
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    unsigned n = strtol(argv[1], NULL, 10);
    printf("Tennanachi(%u) = %llu\n", n, tennanachi(n));
    return 0;
}
