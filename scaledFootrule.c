#include <stdlib.h>
#include <stdio.h>
#include "c99.h"


int main(int argc, char *argv[]){
    ListNode *tLists[argc-1] = getTLists(argc-1, argv);
    
    double totalDist = 0.0;
    //loop through lists calculating dist and sum them
    while(){
        totalDist += calculateSFDistance(tList, cList, p, findCardinality(tLists));
    }
}

double calculateSFDistance(list t, list c, int position, int k){
    int cardC = findCardinality(c);
    int cardT = findCardinality(t);
    int cPosition = positionInList(c, t);
    
    return fabs(cPosition/cardT - position/cardC);    //TODO typecast to double
}

int findCardinality(list){
    return cardinality;
}

int positionInList(int c, list){
    
    return position;
}


// get list of ordered urls in each search list
listNode **getTLists(int nFiles, char *files[]){
    listNode *tLists[nFiles] = malloc(nFiles*sizeof(listNode));
    listNode *curr = NULL;
    int i;
    
    for(i = 0; i < argc; i++){
        // open file
        char *fileName = strdup(files[i+1]);
        fileName = realloc(fileName, strlen(files[i+1]) + strlen(".txt") + 1);
        strcat(fileName, ".txt");   // Open each url file
        if ((FILE *file = fopen(fileName, "r")) == NULL)
            perror("");
        
        char url[BUFSIZ];
        
        // insert first URL
        if (fscanf(file, " %s", url) == 1) {
            tLists[i] = newNode(url);
            curr = tLists[i];
        }
        else // empty file
            continue;
        
        // make a list of URLS
        while (fscanf(file, " %s", url) == 1) {
            listNode *node = newNode(url);
            curr->next = node;
            curr = node;
        }
        fclose(file);
    }
    return tLists;   
}
