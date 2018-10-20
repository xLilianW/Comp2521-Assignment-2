// Base code from week 9 Lab, editted for assignment

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// graph representation is hidden
typedef struct GraphRep *Graph;
typedef struct graphListNode *Outgoing;
typedef struct graphListNode *GraphPage;

// operations on graphs
Graph newGraph(int, char **);
struct graphListNode *newNode(char *);
void addGraphConnection(Graph, int, Outgoing);
void dropGraph(Graph);

// find the number of nodes in a graph
int numNodes(Graph);
void showGraph(Graph);
void setPageWeight(GraphPage);
double getPageWeight(GraphPage, double);
char *getURL(GraphPage);
#endif
