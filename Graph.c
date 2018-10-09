#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "url.h"

typedef struct GraphRep {
	int   nV;
	URL   *head;            // array of URLS
	int   **edges;          // adjacency matrix
} GraphRep;

Graph newGraph() {
    Graph g = malloc(sizeof(Graph));
    
    FILE *collection = fopen("collection.txt", "r");
    
    
    return g;
}
