// Base code from week 9 Lab, editted for assignment

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct GraphRep *Graph;
typedef struct graphListNode *Outgoing;
typedef struct graphListNode *GraphPage;

// Graph operations
Graph newGraph(int, char **);
void freeGraph(Graph);
struct graphListNode *newNode(char *);
void showGraph(Graph);
void addGraphConnection(Graph, int, Outgoing);

// Functions to retrieve graph/node info, as the graph rep is hidden
int numNodes(Graph);
int findURLIndex (Graph, Outgoing);
GraphPage getPage(Graph, int);
void setPageWeight(GraphPage, double);
double getPageWeight(GraphPage);
char *getURL(GraphPage);

// Functions for pagerank calculations
double calcPageRank(Graph, GraphPage, double);
int countInLinks(Graph g, GraphPage url);
int isInLink(Graph g, GraphPage u, GraphPage v);
double inLinkPopularity(Graph, GraphPage, GraphPage);
double outLinkPopularity(Graph, GraphPage, GraphPage);
int countOutLinks(Graph, int);

#endif
