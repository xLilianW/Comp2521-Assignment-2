#include <stdlib.h>
#include <stdio.h>
#include "c99.h"


int main(int argc, char *argv[]){
    ListNode *tLists[argc-1] = getTLists(argc-1, argv);
    int *cList = getCList(tLists);
    int *pList = getCList(tLists);
    
    double totalDist = 0.0;
    double minDist = -1.0;
    int *bestPList;
    
    int i = 0;
    while(i < findCard(cList)){    // Loops through each alternate set of p
        pList = generateP(pList, i);
        int j = 0;
        while(j < findCard(cList)){    // Loops through each element in C list
            int k;
            for(k = 0; k < argc-1; k++){    // Loops through each list
                totalDist += calcSFDist(tLists[k], cList[j], pList[j], findCard(cList));
                if(totalDist < minDist || minDist == -1.0){
                    minDist = totalDist;
                    bestPList = pList;
                }
            }
            j++;
        }
        i++;
    }
}

double calcSFDist(list t, int c, int p, int n){
    int cardT = findCard(t);
    int cPosition = positionInList(c, t);
    
    return fabs(cPosition/cardT - p/n);    //TODO typecast to double
}

int findCard(list L){
    int card = 0;
    while(L[i] != NULL){
        card++;
    }
    return card;
}

int positionInList(int c, list L){
    int position;
    for(position = 0; position < findCard(L); position++){
        if(L[position] == c){
            return position;
        }
    }
    return -1;
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
