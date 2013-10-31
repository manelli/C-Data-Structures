#define LNR 1 /* Left, Node, Right */
#define RNL 1 /* Right, Node, Left */
#define LRN 1 /* Left, Right, Node */

stuct btnode_type
{
	struct btnode_type *left;
	struct btnode_type *right;
	char *item;
}

struct BINARYTREE
{
	struct btnode_type *root;		/* Root of tree  		*/
	struct btnode_type *current_node;	/* Current node 		*/
	int itemlength;				/* Size of item in node 	*/
	int trav_direction;			/* Direction of traversal	*/
	int (*less)(void);			/* Two functions ...		*/
	int (*eq)(void);			/* to compare items		*/
};
