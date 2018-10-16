#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "Queue.h"

typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
	int value;
	BSTLink left, right;
} BSTNode;

// make a new node containing a value
static
BSTLink newBSTNode(int v)
{
	BSTLink new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->value = v;
	new->left = new->right = NULL;
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	free(t);
}

// display a BSTree
void showBSTree(BSTree t)
{
	void doShowBSTree(BSTree); // see later
	doShowBSTree(t);
}

// display BSTree root node
void showBSTreeNode(BSTree t)
{
	if (t == NULL) return;
	printf("%d ", t->value);
}

// print values in infix order
void BSTreeInfix(BSTree t)
{
	if (t == NULL) return;
	BSTreeInfix(t->left);
	showBSTreeNode(t);
	BSTreeInfix(t->right);
}

// print values in prefix order
void BSTreePrefix(BSTree t)
{
	if (t == NULL) return;
	showBSTreeNode(t);
	BSTreePrefix(t->left);
	BSTreePrefix(t->right);
}

// print values in postfix order
void BSTreePostfix(BSTree t)
{
	if (t == NULL) return;
	BSTreePostfix(t->left);
	BSTreePostfix(t->right);
	showBSTreeNode(t);
}

// print values in level-order
void BSTreeLevelOrder(BSTree t)
{
    if (t == NULL) {
        return;
    }
    
    Queue q = newQueue();
    QueueJoin(q, t);
    Item node;
    
    while (!QueueIsEmpty(q)) {
        node = QueueLeave(q);

        showBSTreeNode(node);

        if (node->left != NULL) {
            QueueJoin(q, node->left);
        }
        if (node->right != NULL) {
            QueueJoin(q, node->right);
        }
    }
}

// count #nodes in BSTree
int BSTreeNumNodes(BSTree t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNumNodes(t->left)
	             + BSTreeNumNodes(t->right);
}

// count #leaves in BSTree
int BSTreeNumLeaves(BSTree t)
{
	if (t == NULL) {
	    return 0;
	}
	else if (t->left == NULL && t->right == NULL) {
	    return 1;
	}
	else {
	    return BSTreeNumLeaves(t->left) + BSTreeNumLeaves(t->right);
	}
}

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, int v)
{
	if (t == NULL)
		return newBSTNode(v);
	else if (v < t->value)
		t->left = BSTreeInsert(t->left, v);
	else if (v > t->value)
		t->right = BSTreeInsert(t->right, v);
	else // (v == t->value)
		/* don't insert duplicates */;
	return t;
}

// check whether a value is in a BSTree
int BSTreeFind(BSTree t, int v)
{
	if (t == NULL)
		return 0;
	else if (v < t->value)
		return BSTreeFind(t->left, v);
	else if (v > t->value)
		return BSTreeFind(t->right, v);
	else // (v == t->value)
		return 1;
}

// delete root of tree
static
BSTree deleteRoot(BSTree t)
{
	// if no subtrees, tree empty after delete
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}
	// if only right subtree, make it the new root
	else if (t->left == NULL && t->right != NULL) {
		BSTree hold = t->right;
        free(t);
		return hold;
	}
	// if only left subtree, make it the new root
	else if (t->left != NULL && t->right == NULL) {
        BSTree hold = t->left;
		free(t);
		return hold;
	}
	// else (t->left != NULL && t->right != NULL)
	// so has two subtrees
	// - find inorder successor
	// - move its value to root
	// - delete inorder successor node
	BSTLink parent = t;
	BSTLink succ = t->right; // not null!
	while (succ->left != NULL) {
		parent = succ;
		succ = succ->left;
	}
	t->value = succ->value;
	free(succ);
	if (parent == t)
		parent->right = succ->right;
	else
		parent->left = succ->right;
	return t;
}

// delete a value from a BSTree
BSTree BSTreeDelete(BSTree t, int v)
{
	if (t == NULL)
		return NULL;
	else if (v < t->value)
		t->left = BSTreeDelete(t->left, v);
	else if (v > t->value)
		t->right = BSTreeDelete(t->right, v);
	else // (v == t->value)
		t = deleteRoot(t);
	return t;
}
