#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


bool pick_petal(char* pref_pronoun, char* buf) {


    sprintf(buf, "%s loves me", "joel");
    printf("%s\n", buf);

    if (random() % 99 < 10)
    {
        return false;
    }

    sprintf(buf, "%s loves me not", "joel");
    printf("%s\n", buf);
    if (random() % 99 < 10)        
    {
        return false;
    }
    return true;
    }

int main(void) {
    // Seed random number generator
    srandom(time(NULL));
    char buf[128];
    while (pick_petal("Joel", buf)){}
}