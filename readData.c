#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "BSTree.h"

Graph collectOutgoingURLs () {
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
        
        fscanf(urlFile, "%*[^\n]\n", NULL); // skip #start section 1
        
        char *outgoingURL[BUF_SIZ];
        Outgoing prev;
        fscanf(urlFile, " %s", outgoingURL);
        // Update graph by adding node and outgoing links
        for (int j = 0; strcmp(outgoingURL, "#end") != 0; j++) { 
            Outgoing hyperlink = newNode(outgoingURL);
            if (j==0) {
                g->connections[i] = hyperlink;
                prev = hyperlink;
            }
            else {
                prev->next = hyperlink;
                prev = hyperlink;
            }
            fscanf(urlFile, " %s", outgoingURL);    // Scan in outgoing URLs
        }
        
        // add section 2 to inver
        g->invertedIndex = updateInvertedIndex(g->invertedIndex, urlFile, urls[i]);
        fclose(urlFile);
    }
    
    
    return g; 
}

// update invertedIndex according to section 2 of a url file
BSTree updateInvertedIndex(BSTree invertedIndex, FILE *urlFile, char *url) {
    fscanf(text, "%*[^\n]\n%*[^\n]\n", NULL,NULL); // skip to text in section 2
    int i;
    char *word[BUF_SIZ];
    fscanf(urlFile, " %s", word);
    
    for (i = 0; strcmp(word, "#end") != 0; i++) {
        invertedIndex = BSTreeInsert(invertedIndex, word);
        BSTNode node = BSTreeFind(invertedIndex, word);
        BSTAddPage(url, node);
    }
    
    return invertedIndex;
}



