#include "tree.h"

int main(int argc, char** argv) 
{
	bst_t* bst = bst_init();

	bst->insert(bst, 5);
	bst->insert(bst, 6);
	bst->insert(bst, 2);
	bst->insert(bst, 4);
	bst->insert(bst, 1);
	bst->insert(bst, 10);

	printf("%d\n", bst->contains(bst, 4));
	printf("%d\n", bst->contains(bst, 77));
	printf("%d\n", bst->contains(bst, 2));
	printf("%d\n", bst->contains(bst, 9));

	bst->destroy(bst);
	return 0;
}

bst_t* bst_init()
{
	bst_t* bst = malloc(sizeof(bst_t));
	bst->insert = bst_insert;
	bst->contains = bst_exists;
	bst->destroy = bst_destroy;
	bst->node_destroy = node_destroy;
	bst->root = NULL;
	return bst;	
}

void bst_insert(bst_t* bst, int val) 
{
	node_t* node = malloc(sizeof(node_t));

	node->val = val;
	node->left = NULL;
	node->right = NULL;

	node_t* cursor = bst->root;
	if (NULL == cursor)
	{
		bst->root = node;
		return;
	}

	printf("val is %d\n", val);
	while (NULL != cursor)
	{
		if (cursor->val > val)
		{
			printf("left of %d\n", cursor->val);
			if (NULL == cursor->left)
			{
				printf("placing left\n");
				cursor->left = node;
				return;
			}
			cursor = cursor->left;
		}

		else 
		{
			printf("right of %d\n", cursor->val);
			if (NULL == cursor->right)
			{
				printf("placing right\n");
				cursor->right = node;
				return;
			}
			cursor = cursor->right;
		}
	}

	printf("ERROR INSERTING\n");
}

int bst_exists(bst_t* bst, int target) 
{
	node_t* cursor = bst->root;

	while (NULL != cursor) 
	{
		if(target == cursor->val)
			return 1;

		else if (target > cursor->val)
			cursor = cursor->right;

		else
			cursor = cursor->left;
	}

	return 0;
}

void bst_destroy(bst_t* bst)
{
	node_destroy(bst->root);
	free(bst);
}

void node_destroy(node_t* node)
{
	if (NULL == node)
		return;
	node_destroy(node->left);
	node_destroy(node->right);
	free(node);
}