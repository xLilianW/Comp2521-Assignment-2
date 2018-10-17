// Base code from week 9 Lab, editted for assignment

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "BSTree.h"

#define TRUE    1
#define FALSE   0

// outgoing hyperlink
struct listNode {
    char *URL;
    double pageWeight;
    Outgoing next;
} 

// graph representation 
typedef struct GraphRep {
	int    nV;          // #URLs
	char **URLs;         // stores which url is at each index
	Outgoing  *connections; // list representation of outgoing links
	BSTree invertedIndex;   // inverted index of word frequencies
} GraphRep;

int findURLIndex (Graph g, Outgoing node) {
    int i = 0;
    while (g->URLs[i] != NULL) {
        if (strcmp(URLs[i], node->URL) == 0){
            return i;
        }
    }
    return -1;
}


// create an empty graph
Graph newGraph(int nV, char ** urls)
{
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; 
	for (i=0; i < nV; i++) {
	    new->URLs[i] = strdup(urls[i]);
	}
	new->connections = malloc(nV*sizeof(listNode));
	assert(new->edges != 0);
    new->invertedIndex = NULL;

	return new;
}

struct listNode *newNode(char *url) {
    listNode *new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->next = NULL;
    return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find the number of nodes in the graph
int numNodes(Graph g) {
    if (g == NULL) 
        return 0;
    else 
        return g->nV;
}
