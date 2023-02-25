#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

#include "comp2017_2022_dll.h"

// STAFF function
static void free_list(struct node *list);


struct node * list_unique(struct node *list, struct node **removed, int *removed_count)
{
    if (list == NULL)
        return list;
    if (list->next == NULL)
        return list;

    struct node* checked = list;
    int count = 0;
    while (checked != NULL)
    {
        struct node* cursor = checked->next;
        while (cursor != NULL)
        {
            if (!strcmp(checked->id, cursor->id))
            {
                removed[count] = cursor;
                count++;
                cursor->prev->next = cursor->next;
                if (cursor->next != NULL)
                {
                    cursor->next->prev = cursor->prev;
                }
            }
            cursor = cursor->next;
        }
        checked = checked->next;
    }
    *removed_count = count;
    return list;
}


void test_1() {
    struct node *a = (struct node*)malloc(sizeof(struct node)); 
    struct node *b = (struct node*)malloc(sizeof(struct node));
    struct node *c = (struct node*)malloc(sizeof(struct node));
    struct node *d = (struct node*)malloc(sizeof(struct node));
    struct node *e = (struct node*)malloc(sizeof(struct node));
    struct node *f = (struct node*)malloc(sizeof(struct node));
    struct node *g = (struct node*)malloc(sizeof(struct node));

    a->prev = NULL; a->id = strdup("A"); a->next = b;
    b->prev = a; b->id = strdup("B"); b->next = c;
    c->prev = b; c->id = strdup("D"); c->next = d;
    d->prev = c; d->id = strdup("A"); d->next = e;
    e->prev = d; e->id = strdup("B"); e->next = f;
    f->prev = e; f->id = strdup("B"); f->next = g;
    g->prev = f; g->id = strdup("C"); g->next = NULL;

    struct node **removed = (struct node **)malloc(sizeof(struct node*) * 7);
    memset(removed, 0x00, sizeof(struct node*) * 7);
    
    int removed_count = 0;

    struct node *unique = list_unique(a, removed, &removed_count);

    assert(unique != NULL);

    assert(unique == a); unique = unique->next;
    assert(unique == b); unique = unique->next;
    assert(unique == c); unique = unique->next;
    assert(unique == g); unique = unique->next;
    assert(unique == NULL);

    assert(removed_count == 3);
    assert(removed[0] == d); // 2nd A
    assert(removed[1] == e); // 2nd B
    assert(removed[2] == f); // 3rd B

    // clean up
    free(removed);
    free_list(a);
}

int student_main(int argc, char **argv)
{
    test_1();
    return 0;
}


/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #157470
{
    return student_main(argc, argv);
}

// standard linked list free for an entire list and its associated memory
// this does not solve the memory leaks issues, it merely cleans up all memory
// it is optional for you to implement this for your own testing
static void free_list(struct node *list) {
    ;
}
