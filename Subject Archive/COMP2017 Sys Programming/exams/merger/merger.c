#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

#include "comp2017_2022_ll.h"

void print_list(struct node* cursor)
{
    printf("Printing\n");
    int count = 0;
    while (NULL != cursor && count < 10)
    {
        printf("%s\n", cursor->id);
        cursor = cursor->next;
        count++;
    }
}

struct node * merge_lists(struct node *a, struct node *b)
{
    if ((NULL == a) && (NULL == b))
    {
        return NULL;
    } 

    if (NULL == a)
        return b;

    if (NULL == b)
        return a;

    // print_list(a);
    // print_list(b);

    struct node* a_cursor = a;
    struct node* b_cursor = b;
    struct node* cursor = a_cursor;
    int at_a = 1;
    struct node* temp = a_cursor;    

    while (NULL != cursor->next)
    {
        temp = cursor->next;
        // printf("cursor: %s\n", cursor->id);
        // printf("a_cursor: %s\n", a_cursor->id);
        // printf("b_cursor: %s\n", b_cursor->id);
        // printf("temp: %s\n\n", temp->id);


        if (at_a)
        {
            cursor->next = b_cursor;
            a_cursor = temp;
            // temp = a_cursor->next;
            // a_cursor->next = b_cursor;
            at_a = 0;
        }
        else
        {
            cursor->next = a_cursor;
            b_cursor = temp;
            // temp = b_cursor->next;
            // b_cursor->next = a_cursor;
            // b_cursor = temp;
            at_a = 1;
        }
        cursor = cursor->next;
    } 

    if (a_cursor == NULL && b_cursor == NULL)
    {
        return a;
    }

    if (at_a)
    {
        cursor->next = b_cursor;
    }
    else
    {
        cursor->next = a_cursor;
    }
    // print_list(a);

    return a;
}

void test_1() {
    struct node *a = (struct node*)malloc(sizeof(struct node)); 
    struct node *b = (struct node*)malloc(sizeof(struct node));
    struct node *c = (struct node*)malloc(sizeof(struct node));

    struct node *d = (struct node*)malloc(sizeof(struct node));
    struct node *e = (struct node*)malloc(sizeof(struct node));
    struct node *f = (struct node*)malloc(sizeof(struct node));

    a->id = "A"; a->next = b;
    b->id = "B"; b->next = c;
    c->id = "C"; c->next = NULL;

    d->id = "D"; d->next = e;
    e->id = "E"; e->next = f;
    f->id = "F"; f->next = NULL;
    
    struct node *merged = merge_lists(a, d);

    assert(merged != NULL);

    assert(merged == a); merged=merged->next;
    assert(merged == d); merged=merged->next;
    assert(merged == b); merged=merged->next;
    assert(merged == e); merged=merged->next;
    assert(merged == c); merged=merged->next;
    assert(merged == f); merged=merged->next; 
    assert(merged == NULL);
}

int student_main(int argc, char **argv)
{
    test_1();
    return 0;
}


/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #157469
{
    return student_main(argc, argv);
}
