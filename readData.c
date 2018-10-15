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
    
    Graph g = newGraph(i, urls);    // Make empty graph
    for(int i = 0; i < g->nV; i++){
        char *fileName = strcat(urls[i], ".txt");   // Open url file
        FILE *urlFile = fopen(fileName, "r");
        fscanf(urlFile, "%*[^\n]\n", NULL);
        char *outgoingURL
        fscanf(collection, " %s", outgoingURL);
        for (int j = 0; strcmp(outgoingURL, "#end") != 0; j++) {
            fscanf(collection, " %s", outgoingURL);
            urls[j]
        }
    }
         
        
        //update graph by adding node and outgoing links
}
