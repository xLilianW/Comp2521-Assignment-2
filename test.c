#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "graph.h"

#define TRUE    1
#define FALSE   0

int main() {
    char *searchTerm = "mars";
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUFSIZ], *searchTermLine;
    
    // Loops through entire file and finds search term
    while(fgets(fileLine, BUFSIZ, invertedIndex) != NULL){
        if(strstr(fileLine, searchTerm) != NULL){
            //TODO check if need to use strsep instead
            searchTermLine = strdup(fileLine);
            strsep(&searchTermLine, " ");    // Removes search term leaving url list
            strsep(&searchTermLine, " ");    // Skip the second space
            break;
        }
    }
    
    // Extract each URL matching search term and place into array
    char *urlToken = strsep(&searchTermLine, " ");
    char *urlArray[BUFSIZ];
    int i = 0;
    while(searchTermLine != '\0'){
        urlArray[i] = malloc(strlen(urlToken) + 1);
        strcpy(urlArray[i], urlToken);
        urlToken = strsep(&searchTermLine, " ");
        i++;
    }
    
    fclose(invertedIndex);
    return i;
}
