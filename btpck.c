#include <stdio.h>
#include "btdef.h"

static struct BINARYTREE *cbt; /* Current Binary Tree */

/* Use this macro as moveitem(from, to) */
#define moveitem(A,B) movmem(A,B,cbt->itemlength)

/* Set tree currency */
void bt_settree(struct BINARYTREE *newtree)
{
	cbt = newtree;
}

/* Allocate space for new node */
static struct btnode_type *create_node(void)
{
	char *malloc();
	struct btnode_type *newnode;

	newnode = (struct btnode_type *)malloc(sizeof(struct btnode_type));
	newnode->item = malloc(cbt->itemlength);
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}


void bt_init(*btless(), *bteq(), int btdirect, int btsize)
{
/*	int(*btless)();	 Function to see if item 1 is less than item 2  */
/*	int (*bteq)();	 Function to see if item 1 equals item 2	*/
/*	int btdirect;	 Set the traversal direction 			*/
/*	int btsize;							*/

	cbt->root = NULL;
	cbt->current_node = NULL;
	cbt->less = btless;
	cbt->eq = bteq;
	cbt->trav_direction = btdirect;
	cbt->itemlength = btsize;
}

/* Initialize binary tree for the first time */
static void init_tree(char *item)
{
	struct btnode_type *newnode;
	static struct btnode_type *create_node();

	newnode = create_node();
	moveitem(item, newnode->item);
	cbt->current_node = cbt->root = newnode;
}

/* Sets current node pointer to the tree root */
void bt_setroot(void)
{
	cbt->current_node = cbt->root;
}

/* Returns address of an item */
char *bt_examine(void)
{
	return cbt->current_node->item;
}

/* Adds new item to a tree */
void bt_add(char *newitem)
{
	struct btnode_type *node, *newnode;
	static struct btnode_type *create_node();
	struct btnode_type **adto; /* Which pointer to extended */
	static init_tree();

	/* If tree is brand new, add to current node */
	node = cbt->current_node;
	if(node == NULL)
	{
		init_tree(newitem);
		return;
	}

	/* Determine direction to add to */
	if((*cbt->less)(newitem, node->item) ||
	   (*cbt->eq)  (newitem, node->item))
	{
		addto = &(node->left);
	}
	else
	{
		addto = &(node->right);
	}

	/* If tree in that direction is null, add new node there */
	if(*addto == NULL)
	{
		newnode = create_node();
		moveitem(newitem, newnode->item);
		*addto = newnode;
		bt_setroot();
		return;
	}
	
	/* Otherwise continue search at that subtree */
	cbt->current_node = *addto;
	bt_add(newitem);
}

static void traverse(int (*donode)(), struct btnode_type *node)
{
	struct btnode_type **first, **second;

	/* Determine traversal order */
	switch(cbt->trav_direction)
	{
		case LNR:
			first = &(node->left);
			second = &(node->right);
			break;
		case RNL:
			first = &(node->right);
			second = &(node->left);
			break;
	}

	/* Apply donode */
	if(*first != NULL)
	{
		traverse(donode, *first);
		(*donode)(node->item);
	}
	if(*second != NULL)
		traverse(donode, *second);
}

void bt_traverse(int (*donode)())
{
	static traverse();
	traverse(donode, cbt->current_node);
}
