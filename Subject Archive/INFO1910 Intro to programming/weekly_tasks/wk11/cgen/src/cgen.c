#include "cgen.h"

int main()
{
    int range[5] = {1,2,3,4,5};
    struct generator gena = make_struct(range);
    printf("%d\n", gena.next(&gena));
    printf("%d\n", gena.next(&gena));
    printf("%d\n", gena.next(&gena));
    printf("%d\n", gena.next(&gena));
    printf("%d\n", gena.next(&gena));
    printf("%d\n", gena.next(&gena));
    printf("%d\n", gena.next(&gena));
    return 0;



}

struct generator make_struct(int* values){
    struct generator gena;
    gena.a = *values;
    gena.b = values[1];
    gena.c = values[2];
    gena.d = values[3];
    gena.e = values[4];


    gena.call = squares;
    gena.next = next;
    gena.id = 0;
    return gena;
}

int squares(int x){return x*x;}

int next(struct generator* gen)
{
    if (gen->id > 4)
    {
        fprintf(stderr, "generator exhausted. StopIteration\n");
        exit(0);
    }
    gen->id += 1;
    switch (gen->id-1){
        case 0: return gen->call(gen->a);
        case 1: return gen->call(gen->b);
        case 2: return gen->call(gen->c);
        case 3: return gen->call(gen->d);
        case 4: return gen->call(gen->e);
    }
    return -1;
}