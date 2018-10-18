
// BSTree.h ... char *erface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H


typedef struct BSTNode *BSTree;
typedef struct BSTNode *BSTLink;
typedef struct BSTListNode *Page;

// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);
// print the BST in infix order
void BSTreeInfix(BSTree t);

// count #nodes in BSTree
int BSTreeNumNodes(BSTree);
// count #leaves in BSTree
int BSTreeNumLeaves(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, char *);
// insert a page char *o the pageList of a word
void BSTAddPage(char *, BSTLink );
// find a word in the tree
struct BSTNode *BSTreeFind(BSTree, char *);
// delete a value from a BSTree
BSTree BSTreeDelete(BSTree, char *);

#endif
