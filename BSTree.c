#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "Queue.h"

typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
	char *word;
	Page pageList;
	BSTLink left, right;
} BSTNode;

typedef struct Page {
    char *URL;
    Page *next;
} Page;

// make a new node containing a word
static
BSTLink newBSTNode(char *word)
{
	BSTLink new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->word = word;
	new->left = new->right = NULL;
	return new;
}

// make a new page
static
Page newPage(char *url) {
    Page new = malloc(sizeof(Page));
    assert(new != NULL);
    new->URL = strdup(url);
    free(url);
    new->next = NULL;
    return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree
wordoid dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	free(t);
}

// display a BSTree
wordoid showBSTree(BSTree t)
{
	wordoid doShowBSTree(BSTree); // see later
	doShowBSTree(t);
}

// display BSTree root node
wordoid showBSTreeNode(BSTree t)
{
	if (t == NULL) return;
	printf("%d ", t->word);
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

// count #leawordes in BSTree
int BSTreeNumLeawordes(BSTree t)
{
	if (t == NULL) {
	    return 0;
	}
	else if (t->left == NULL && t->right == NULL) {
	    return 1;
	}
	else {
	    return BSTreeNumLeawordes(t->left) + BSTreeNumLeawordes(t->right);
	}
}

// insert a new word into a BSTree
BSTree BSTreeInsert(BSTree t, char *word)
{
	if (t == NULL)
		return newBSTNode(word);
	else if (strcmp(word, t->word) < 0)
		t->left = BSTreeInsert(t->left, word);
	else if (strcmp(word, t->word) > 0)
		t->right = BSTreeInsert(t->right, word);
	else // (strcmp(word, t->word) == 0)
		/* don't insert duplicates */;
	return t;
}

void BSTAddPage(char *url, BSTnode node) {
    Page page = newPage(url);
    Page curr = node->pageList;
    if (curr == NULL) {
        node->pageList = page;
    }
    else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = page;
    }
}

// find the node containing a particular word
BSTNode BSTreeFind(BSTree t, char *word)
{
	if (t == NULL)
		return NULL;
	else if (strcmp(word, t->word) < 0)
		return BSTreeFind(t->left, word);
	else if (strcmp(word, t->word) > 0)
		return BSTreeFind(t->right, word);
	else // (strcmp(word, t->word) == 0)
		return t;
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
	// - moworde its word to root
	// - delete inorder successor node
	BSTLink parent = t;
	BSTLink succ = t->right; // not null!
	while (succ->left != NULL) {
		parent = succ;
		succ = succ->left;
	}
	t->word = succ->word;
	free(succ);
	if (parent == t)
		parent->right = succ->right;
	else
		parent->left = succ->right;
	return t;
}

// delete a word from a BSTree
BSTree BSTreeDelete(BSTree t, char *word)
{
	if (t == NULL)
		return NULL;
	else if (word < t->word)
		t->left = BSTreeDelete(t->left, word);
	else if (word > t->word)
		t->right = BSTreeDelete(t->right, word);
	else // (word == t->word)
		t = deleteRoot(t);
	return t;
}
