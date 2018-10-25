// Base code from week 9 Lab, editted for assignment

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "c99.h"

#define TRUE    1
#define FALSE   0

// Node in the graph, for the list rep
typedef struct graphListNode {
    char *URL;
    double pageWeight;
    Outgoing next;
} graphListNode;

// Graph representation 
typedef struct GraphRep {
	int nV;                     // #URLs
    graphListNode **URLs;       // list of URLs at their mapped index
	Outgoing  *connections;     // list representation of outgoing links
} GraphRep;

// Create an empty graph
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

// Clean up a graph
void freeGraph(Graph g) {
    if (g == NULL) return;
    int i;
    for (i=0; i < g->nV; i++) {
        free(g->URLs[i]->URL);
        free(g->URLs[i]);
    }
    free(g->URLs);
    graphListNode *curr, *next;
    for (i=0; i < g->nV; i++) {
        curr = g->connections[i];
        while (curr != NULL) {
            free(curr->URL);
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(g->connections);
}

// Create a new list node
graphListNode *newNode(char *url) {
    graphListNode *new = malloc(sizeof(graphListNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->next = NULL;
    return new;
}

// Add an outgoing url for a url
void addGraphConnection(Graph g, int src, Outgoing dest) {
    // ignore self loops
    if (strcmp(g->URLs[src]->URL, dest->URL) == 0) return;
     
    // First dest for the src
    if (g->connections[src] == NULL) {
        g->connections[src] = dest;
    }
    else {
        // Append dest to end of list
        Outgoing curr = g->connections[src];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = dest;
    }
}

// Find the number of nodes in the graph
int numNodes(Graph g) {
    if (g == NULL) 
        return 0;
    else 
        return g->nV;
}

// Returns index for page of URL
int findURLIndex (Graph g, Outgoing node) {
    int i = 0;
    while (g->URLs[i] != NULL) {
        if (strcmp(g->URLs[i]->URL, node->URL) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

// Returns page with index i
GraphPage getPage(Graph g, int i){
    if(i < numNodes(g)){
        return g->URLs[i];
    }
    return NULL;
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

// For testing, prints each url with their outgoing links
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
