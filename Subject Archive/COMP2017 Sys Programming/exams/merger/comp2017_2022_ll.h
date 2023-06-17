#ifndef comp2017_2022_ll_h
#define comp2017_2022_ll_h

struct node {
    const char *id;

    struct node *next;
};

extern struct node * merge_lists(struct node *a, struct node *b);


#endif