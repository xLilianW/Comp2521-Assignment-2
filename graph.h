// Base code from week 9 Lab, editted for assignment

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// graph representation is hidden
typedef struct GraphRep *Graph;
typedef listNode *Outgoing;
typedef listNode *Page;

// operations on graphs
Graph newGraph(int nV);
void dropGraph(Graph);
Graph makeGraph(int, int**);
void showGraph(Graph, char **);


#endif
