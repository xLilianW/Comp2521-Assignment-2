#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"

typedef struct BSTListNode {
    char *URL;
    Page next;
} BSTListNode;

typedef struct BSTNode {
	char *word;
	Page pageList;
	BSTLink left, right;
} BSTNode;

// make a new node containing a word
static
BSTLink newBSTNode(char *word)
{
	BSTLink new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->word = strdup(word);
	new->pageList = NULL;
	new->left = new->right = NULL;
	return new;
}

// make a new page
static
Page newBSTPage(char *url) {
    Page new = malloc(sizeof(BSTListNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->next = NULL;
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

// print values in infix order, from lab 10
void BSTreeInfix(BSTree t, FILE *out)
{
	if (t == NULL) return;
	BSTreeInfix(t->left, out);
	showBSTNodePages(t, out);
	BSTreeInfix(t->right, out);
}

void showBSTNodePages(BSTLink node, FILE *out) {
    fprintf(out, "%s ", node->word);
    Page curr = node->pageList;
    while (curr != NULL) {
        fprintf(out, " %s", curr->URL);
        curr = curr->next;
    }
    fprintf(out, "\n");
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
	else // (word == t->word)
		/* don't insert duplicates */;
	return t;
}

// add a page to a words pageLi
void BSTAddPage(char *url, BSTLink node) {
    Page newPage = newBSTPage(url);
    Page curr = node->pageList;
    if (curr == NULL) {
        node->pageList = newPage;
    }
    else {
        if (strcmp(curr->URL, url) == 0) return;
        while (curr->next != NULL) {
            if (strcmp(curr->URL, url) == 0) return;
            curr = curr->next;
        }
        curr->next = newPage;
    }
}

// find the node containing a particular word
BSTNode *BSTreeFind(BSTree t, char *word)
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

/*
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
*/
