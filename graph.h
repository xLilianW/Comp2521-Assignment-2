// Base code from week 9 Lab, editted for assignment

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// graph representation is hidden
typedef struct GraphRep *Graph;
typedef struct listNode *Outgoing;
typedef struct listNode *Page;

// operations on graphs
Graph newGraph(int, char **);
struct listNode *newNode(char *url);
void dropGraph(Graph);
void showGraph(Graph, char **);

// find the number of nodes in a graph
int numNodes(Graph);

#endif
