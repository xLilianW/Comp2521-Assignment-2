// BSTree.h ... char *erface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTNode *BSTree;
typedef struct BSTNode *BSTNode;

// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);
// display a BSTree
void showBSTree(BSTree);
// display BSTree root node
void showBSTreeNode(BSTree);

// count #nodes in BSTree
char * BSTreeNumNodes(BSTree);
// count #leaves in BSTree
char * BSTreeNumLeaves(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, char *);
// insert a page char *o the pageList of a word
void BSTAddPage(char *, BSTNode);
// find a word in the tree
BSTNode BSTreeFind(BSTree, char *);
// delete a value from a BSTree
BSTree BSTreeDelete(BSTree, char *);

#endif
