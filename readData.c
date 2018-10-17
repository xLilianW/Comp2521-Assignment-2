#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"

int collectURLs(char *urls[BUFSIZ]);
void lowercase(char *word);
void removePunctuation(char *word);

Graph collectOutgoingURLs () {    
    char *urls[BUFSIZ];
    int i, j, nURLs = collectURLs(urls);
    
    Graph g = newGraph(nURLs, urls);    // Make empty graph
    for(i = 0; i < numNodes(g); i++){
        char *fileName = strcat(urls[i], ".txt");   // Open each url file
        FILE *urlFile = fopen(fileName, "r");
        
        fscanf(urlFile, "%*[^\n]\n", NULL); // skip #start section 1
        
        char outgoingURL[BUFSIZ];
        fscanf(urlFile, " %s", outgoingURL);
        // Update graph by adding node and outgoing links
        for (j = 0; strcmp(outgoingURL, "#end") != 0; j++) { 
            Outgoing hyperlink = newNode(outgoingURL);
            addGraphConnection(g, i, hyperlink);
            fscanf(urlFile, " %s", outgoingURL);    // Scan in outgoing URLs
        }
        
        fclose(urlFile);
    }
     
    return g; 
}

// update invertedIndex according to section 2 of a url file
BSTree collectInvertedIndex() {
    char *urls[BUFSIZ];
    BSTree invertedIndex = newBSTree();
    int i, j, nURLs = collectURLs(urls);
    
    
    char word[BUFSIZ];
    for (i = 0; i < nURLs; i++) {
        char *fileName = strcat(urls[i], ".txt");   // Open each url file
        FILE *urlFile = fopen(fileName, "r");
        
        fscanf(urlFile, "%*[^#]#%*[^#]#%*[^#]#%*[^\n]\n", NULL, NULL, NULL, NULL); // skip to section 2
        
        char word[BUFSIZ];
        fscanf(urlFile, " %s", word);
        
        // process words in section 2
        for (j = 0; strcmp(word, "#end") != 0; j++) {
            // normalise the string
            lowercase(word);
            removePunctuation(word);
            
            // add word and url to BST
            BSTreeInsert(invertedIndex, word);
            BSTLink node = BSTreeFind(invertedIndex, word);
            BSTAddPage(urls[i], node);
        }
        fclose(urlFile);
    }
    
    return invertedIndex;
}

// extract list of urls from collection.txt
int collectURLs(char *urls[BUFSIZ]) {
    FILE *collection = fopen("test.txt", "r"); //FIXME make it collection.txt
    int i = 0;
    
    // make a list of URLS
    while (fscanf(collection, " %s", urls[i]) == 1) {
        i++;
    }
    
    return i;
}

// from https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
void lowercase(char *word) {
    for ( ; *word; ++word) *word = tolower(*word);
}

void removePunctuation(char *string) {
    if (string[strlen(string)] == '.' || string[strlen(string)] == ',' || string[strlen(string)] == ';' || string[strlen(string)] == '?') {
        string[strlen(string)] = '\0';
    }   
}

