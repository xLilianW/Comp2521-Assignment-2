#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "c99.h"

// Page containing a url
typedef struct BSTListNode {
    char *URL;
    BSTPage next;
} BSTListNode;

// Node in the BST
typedef struct BSTNode {
	char *word;
	BSTPage BSTPageList;
	BSTLink left, right;
} BSTNode;

// Create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// Make a new node containing a word
static
BSTLink newBSTNode(char *word)
{
	BSTLink new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->word = strdup(word);
	new->BSTPageList = NULL;
	new->left = new->right = NULL;
	return new;
}

// Make a new BSTPage
static
BSTPage newBSTPage(char *url) {
    BSTPage new = malloc(sizeof(BSTListNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->next = NULL;
    return new;
}

// Free memory associated with BSTree
void freeBSTree(BSTree t)
{
	if (t == NULL) return;
	freeBSTree(t->left);
	freeBSTree(t->right);
	
	free(t->word);
	BSTPage curr = t->BSTPageList, next;
	while (curr != NULL) {
	    free(curr->URL);
	    next = curr->next;
	    free(curr);
	    curr = next;
	}
	free(t);
}

// Print values in infix order, from lab 10
void BSTreeInfix(BSTree t, FILE *out)
{
	if (t == NULL) return;
	BSTreeInfix(t->left, out);
	showBSTNodeBSTPages(t, out);
	BSTreeInfix(t->right, out);
}

// Print the pages associated with a BSTnode
void showBSTNodeBSTPages(BSTLink node, FILE *out) {
    fprintf(out, "%s ", node->word);
    BSTPage curr = node->BSTPageList;
    while (curr != NULL) {
        fprintf(out, " %s", curr->URL);
        curr = curr->next;
    }
    fprintf(out, "\n");
}

// Insert a new word into a BSTree
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

// Add a BSTPage to a words BSTPageList
void BSTAddBSTPage(char *url, BSTLink node) {
    BSTPage newPage = newBSTPage(url);
    BSTPage curr = node->BSTPageList;
    // New listhead
    if (curr == NULL || strcmp(newPage->URL, curr->URL) < 0) { 
        newPage->next = curr; 
        node->BSTPageList = newPage;
        return;
    } 
    else { 
        // Find the newpage position
        if (strcmp(curr->URL, newPage->URL) == 0) return; // no duplicates
        while (curr->next != NULL && strcmp(curr->next->URL, newPage->URL) < 0) {
            curr = curr->next;
        } 
        if (curr->next != NULL && strcmp(curr->next->URL, newPage->URL) == 0) return; // no duplicates

        newPage->next = curr->next; 
        curr->next = newPage; 
    } 
}

// Find the node containing a particular word
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

