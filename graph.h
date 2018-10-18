// Base code from week 9 Lab, editted for assignment

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "BSTree.h"

// graph representation is hidden
typedef struct GraphRep *Graph;
typedef struct graphListNode *Outgoing;

// operations on graphs
Graph newGraph(int, char **);
struct graphListNode *newNode(char *);
void addGraphConnection(Graph, int, Outgoing);
void dropGraph(Graph);

// find the number of nodes in a graph
int numNodes(Graph);
#endif
