#ifndef comp2017_2022_dll_h
#define comp2017_2022_dll_h

struct node {
    char *id;

    struct node *next;
    struct node *prev;
};

extern struct node * list_unique(struct node *list, struct node **removed, int *removed_count);

#endif