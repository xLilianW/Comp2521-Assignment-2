#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"
#include "c99.h"

#define URLSIZE 50

int collectURLs(char *urls[BUFSIZ]);
void lowercase(char *word);
char *removePunctuation(char *word);

Graph collectOutgoingURLs() {    
    char *urls[BUFSIZ];
    int i, nURLs = collectURLs(urls);
    
    Graph g = newGraph(nURLs, urls);    // Make empty graph
    // Read in outgoing urls for each url
    for(i = 0; i < numNodes(g); i++){
        // Open the file
        char *fileName = strdup(urls[i]);
        fileName = realloc(fileName, strlen(urls[i]) + strlen(".txt") + 1);
        strcat(fileName, ".txt");   // Open each url file
        FILE *urlFile = fopen(fileName, "r");
        
        fscanf(urlFile, "%*[^\n]\n"); // Skip #start Section-1
        
        char outgoingURL[URLSIZE];
        fscanf(urlFile, " %s", outgoingURL);
        // Update graph by adding node and outgoing links
        while (strcmp(outgoingURL, "#end") != 0) { 
            Outgoing hyperlink = newNode(outgoingURL);
            addGraphConnection(g, i, hyperlink);
            fscanf(urlFile, " %s", outgoingURL);    
        }
        
        fclose(urlFile);
    }
     
    return g; 
}

// Update invertedIndex according to section 2 of url files
BSTree collectInvertedIndex() {
    char *urls[BUFSIZ];
    BSTree invertedIndex = newBSTree();
    int i, j, nURLs = collectURLs(urls);
    
    // Loop through each url file and add the words & urls to the tree
    for (i = 0; i < nURLs; i++) {
        // Open the file
        char *fileName = strdup(urls[i]);
        fileName = realloc(fileName, strlen(urls[i]) + strlen(".txt") + 1);
        strcat(fileName, ".txt");   
        FILE *urlFile = fopen(fileName, "r");
        
        fscanf(urlFile, "%*[^\n]%*[^#]#%*[^#]#%*[^\n]\n"); // skip to section 2 

        char word[BUFSIZ];
        fscanf(urlFile, " %s", word);
        
        // Process words in section 2
        for (j = 0; strcmp(word, "#end") != 0; j++) {
            // Normalise the string
            lowercase(word);
            strcpy(word,removePunctuation(word));
            
            // Add word and url to BST
            invertedIndex = BSTreeInsert(invertedIndex, word);
            BSTLink node = BSTreeFind(invertedIndex, word);
            BSTAddBSTPage(urls[i], node);
            
            fscanf(urlFile, " %s", word);
        }
        fclose(urlFile);
    }
    return invertedIndex;
}

// Extract list of urls from collection.txt
int collectURLs(char *urls[BUFSIZ]) {
    char url[URLSIZE];
    FILE *collection = fopen("collection.txt", "r"); //FIXME make it collection.txt
    int i = 0;
    
    // Make a list of URLS
    while (fscanf(collection, " %s", url) == 1) {
        urls[i] = malloc(strlen(url) + 1);
        strcpy(urls[i], url);
        i++;
    }
    fclose(collection);
    
    return i;
}

// From https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
// Makes a string lower case
void lowercase(char *word) {
    for ( ; *word; ++word) *word = tolower(*word);
}

// Remove trailing punctuation
char *removePunctuation(char *string) { //FIXME is there a better way? edit string directly
    char *str = strdup(string);
    if (string[strlen(string)-1] == '.' || string[strlen(string)-1] == ',' || string[strlen(string)-1] == ';' || string[strlen(string)-1] == '?') {
        str[strlen(str)-1] = '\0';
    } 
    return str;  
}

