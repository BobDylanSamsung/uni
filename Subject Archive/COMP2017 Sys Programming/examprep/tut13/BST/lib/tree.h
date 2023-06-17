#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct node node_t;
typedef struct bst bst_t;

struct node {
	int val;
	node_t* left;
	node_t* right;
};

struct bst {
	node_t* root;
	void (*insert)(bst_t* bst, int val);
	int (*contains)(bst_t* bst, int target);
	void (*destroy)(bst_t* bst);
	void (*node_destroy)(node_t* node);
};

bst_t* bst_init();

void bst_insert(bst_t* root, int val);

int bst_exists(bst_t* root, int target);

void bst_destroy(bst_t* bst);

void node_destroy(node_t* node);


#endif