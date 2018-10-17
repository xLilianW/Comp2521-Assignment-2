// Base code from week 9 Lab, editted for assignment

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "BSTree.h"

// graph representation is hidden
typedef struct GraphRep *Graph;
typedef struct listNode *Outgoing;
typedef struct listNode *Page;

// operations on graphs
Graph newGraph(int, char **);
struct listNode *newNode(char *);
void addGraphConnection(Graph, int, Outgoing);
void dropGraph(Graph);
void showGraph(Graph, char **);

// find the number of nodes in a graph
int numNodes(Graph);
// get the inverted index
BSTree getInvertedIndex(Graph);
#endif
