// Base code from week 9 Lab, editted for assignment

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

#define TRUE    1
#define FALSE   0

typedef struct graphListNode {
    char *URL;
    double pageWeight;
    Outgoing next;
} graphListNode;

// graph representation 
typedef struct GraphRep {
	int    nV;          // #URLs
    graphListNode **URLs;        // list of URLs at their mapped index
	Outgoing  *connections; // list representation of outgoing links
} GraphRep;

int findURLIndex (Graph g, Outgoing node) {
    int i = 0;
    while (g->URLs[i] != NULL) {
        if (strcmp(g->URLs[i]->URL, node->URL) == 0){
            return i;
        }
    }
    return -1;
}

// create an empty graph
Graph newGraph(int nV, char **urls)
{
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; 
	int i = 0;
	
	new->URLs = malloc(nV*sizeof(graphListNode));
    assert(new->URLs != 0);
	for (i=0; i < nV; i++) {
	    new->URLs[i] = malloc(sizeof(graphListNode));
	    assert(new->URLs[i] != 0);
	    new->URLs[i] = newNode(urls[i]);
	}
	
	new->connections = malloc(nV*sizeof(graphListNode));
	assert(new->connections != 0);
	for (i=0; i < nV; i++) {
	    new->connections[i] = NULL;
	}


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

// Returns page with index i
GraphPage getPage(Graph g, int i){
    //TODO check if returns null when page doesnt exist
    return g->connections[i];
}

// Changes page weight to w
void setPageWeight(GraphPage p, double w){
    p->pageWeight = w;
}

// Returns page weight
double getPageWeight(GraphPage p){
    return p->pageWeight;
}

// Returns url of page
char *getURL(GraphPage p){
    return p->URL;
}

//FIXME FOR TESTING, remove after
void showGraph(Graph g) {
    int i;
    Outgoing curr = NULL; 
    for (i=0; i < g->nV; i++) {
        printf("%s:", g->URLs[i]->URL);
        curr = g->connections[i];
        while (curr != NULL) {
            printf(" %s", curr->URL);
            curr = curr->next;
        }
        printf("\n");
    }
}
