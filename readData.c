#include <stdio.h>
#include <stdlib,h>
#include "graph.h"

char *collectData(void){
    FILE *collection = fopen("collection.txt", "r");
    char **urls;
    int i = 0;
    
    // make a list of URLS
    while (fscanf(collection, " %s", urls[i]) == 1) {
        i++;
    }
    
    Graph g = newGraph(i, urls);
    
        //make empty graph
        //open file (add .txt)
        //update graph by adding node and outgoing links
}
