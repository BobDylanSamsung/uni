#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

bool pick_petal(const char* pref_pronoun, char* buf) {
    //TODO: Code goes here - write output to buf, return false if no output left
}

int main(void) {
    srandom(time(NULL));
    char buf[128];
    while (pick_petal("It", buf)) 
        printf("%s\n", buf);
}
