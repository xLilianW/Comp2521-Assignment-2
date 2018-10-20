#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"

int collectURLs(char *urls[BUFSIZ]);
void lowercase(char *word);
char *removePunctuation(char *word);

Graph collectOutgoingURLs () {    
    char *urls[BUFSIZ];
    int i, j, nURLs = collectURLs(urls);
    
    Graph g = newGraph(nURLs, urls);    // Make empty graph
    for(i = 0; i < numNodes(g); i++){
        char *fileName = strdup(urls[i]);
        fileName = realloc(fileName, strlen(urls[i]) + strlen(".txt") + 1);
        strcat(fileName, ".txt");   // Open each url file
        FILE *urlFile = fopen(fileName, "r");
        
        fscanf(urlFile, "%*[^\n]\n", NULL); // skip #start section 1
        
        char outgoingURL[BUFSIZ];
        fscanf(urlFile, " %s", outgoingURL);
        // Update graph by adding node and outgoing links
        while (strcmp(outgoingURL, "#end") != 0) { 
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
        char *fileName = strdup(urls[i]);
        fileName = realloc(fileName, strlen(urls[i]) + strlen(".txt") + 1);
        strcat(fileName, ".txt");   // Open each url file
        FILE *urlFile = fopen(fileName, "r");
        
        fscanf(urlFile, "%*[^\n]%*[^#]#%*[^#]#%*[^\n]\n", NULL, NULL, NULL, NULL); // skip to section 2 // skip to section 2

        char word[BUFSIZ];
        fscanf(urlFile, " %s", word);
        
        // process words in section 2
        for (j = 0; strcmp(word, "#end") != 0; j++) {
            // normalise the string
            lowercase(word);
            strcpy(word,removePunctuation(word));
            
            // add word and url to BST
            invertedIndex = BSTreeInsert(invertedIndex, word);
            BSTLink node = BSTreeFind(invertedIndex, word);
            BSTAddBSTPage(urls[i], node);
            fscanf(urlFile, " %s", word);
        }
        fclose(urlFile);
    }
    return invertedIndex;
}

// extract list of urls from collection.txt
int collectURLs(char *urls[BUFSIZ]) {
    char url[BUFSIZ];
    FILE *collection = fopen("collection.txt", "r"); //FIXME make it collection.txt
    int i = 0;
    
    // make a list of URLS
    while (fscanf(collection, " %s", url) == 1) {
        urls[i] = malloc(strlen(url) + 1);
        strcpy(urls[i], url);
        i++;
    }
    return i;
}

// from https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
void lowercase(char *word) {
    for ( ; *word; ++word) *word = tolower(*word);
}

// remove trailing punctuation
char *removePunctuation(char *string) { //FIXME is there a better way? edit string directly
    char *str = strdup(string);
    if (string[strlen(string)-1] == '.' || string[strlen(string)-1] == ',' || string[strlen(string)-1] == ';' || string[strlen(string)-1] == '?') {
        str[strlen(str)-1] = '\0';
    } 
    return str;  
}

