// Base code from week 9 Lab, editted for assignment

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

#define TRUE    1
#define FALSE   0

// outgoing hyperlink
typedef struct graphListNode {
    char *URL;
    double pageWeight;
    Outgoing next;
} graphListNode;

// graph representation 
typedef struct GraphRep {
	int    nV;          // #URLs
	char **URLs;         // stores which url is at each index
	Outgoing  *connections; // list representation of outgoing links
} GraphRep;

int findURLIndex (Graph g, Outgoing node) {
    int i = 0;
    while (g->URLs[i] != NULL) {
        if (strcmp(g->URLs[i], node->URL) == 0){
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
	int i = 0;
	for (i=0; i < nV; i++) {
	    new->URLs[i] = strdup(urls[i]);
	}
	new->connections = malloc(nV*sizeof(graphListNode));
	assert(new->connections != 0);

	return new;
}

graphListNode *newNode(char *url) {
    graphListNode *new = malloc(sizeof(graphListNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->next = NULL;
    return new;
}

void addGraphConnection(Graph g, int src, Outgoing dest) {
    if (g->connections[src] == NULL) {
        g->connections[src] = dest;
    }
    else {
        // append dest to end of list
        Outgoing curr = g->connections[src];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = dest;
    }
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// find the number of nodes in the graph
int numNodes(Graph g) {
    if (g == NULL) 
        return 0;
    else 
        return g->nV;
}
