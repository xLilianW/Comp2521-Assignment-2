
// BSTree.h ... char *erface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H


typedef struct BSTNode *BSTree;
typedef struct BSTNode *BSTLink;
typedef struct BSTListNode *BSTPage;

// Tree operations
BSTree newBSTree();
void freeBSTree(BSTree);
void BSTreeInfix(BSTree, FILE *);
void showBSTNodeBSTPages(BSTLink, FILE *);

// Node operations
BSTree BSTreeInsert(BSTree, char *);
void BSTAddBSTPage(char *, BSTLink );
struct BSTNode *BSTreeFind(BSTree, char *);

#endif
