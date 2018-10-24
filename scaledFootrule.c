#include <stdlib.h>
#include <stdio.h>
#include "c99.h"


int main(int argc, char *argv[]){
    ListNode *tLists[argc-1] = getTLists(argc-1, argv);
    char **cList = getCList(tLists);
    char **pList = getCList(tLists);
    
    double totalDist = 0.0;
    double minDist = -1.0;
    char **bestPList;
    
    int i = 0;
    while(i < findCard(cList)){    // Loops through each alternate set of p(TODO 1 too many loops?)
        pList = generateP(pList, i);
        int j = 0;
        while(j < findCard(cList)){    // Loops through each element in C list
            int k;
            for(k = 0; k < argc-1; k++){    // Loops through each list
                totalDist += calcSFDist(tLists[k], positionInList(cList[j], cList), pList[j], findCard(cList));
                if(totalDist < minDist || minDist == -1.0){
                    minDist = totalDist;
                    bestPList = pList;
                }
            }
            j++;
        }
        i++;
    }
    printResult(bestPList, minDist, cList);
}

// Returns new list by swapping adjacent elements in list
int *generateP(list pList, int i){
    int temp = pList[i];
    pList[i] = pList[i+1];
    pList[i+1] = temp;
    return pList;
}

// Returns calulated scaled footrule aggregation
double calcSFDist(list t, char *c, int p, int n){
    int cardT = findCard(t);
    int cPosition = positionInList(c, t);
    
    return fabs(cPosition/cardT - p/n);    //TODO typecast to double
}

// Returns cardinality of a list
int findCard(list L){
    int card = 0;
    while(L[i] != NULL){
        card++;
    }
    return card;
}

// Returns position of string in list
int positionInList(char *c, list L){
    int position;
    for(position = 0; position < findCard(L); position++){
        if(strcmp(L[position], c) == 0){
            return position;
        }
    }
    return -1;
}

// Returns union of urls in lists
char **getCList(ListNode *Lists){
    char **list;    //malloc?
    int j = 0;
    
    int i = 0;
    while(Lists[i] != NULL){    // Loops through each list
        ListNode curr = Lists[i];
        while(curr != NULL){    // Loops through each list node
            if(positionInList(curr->url, list) == -1){
                list[j] = strdup(curr->url);    // Adds url to list
                j++;
            }
            curr = curr->next;
        }
        i++;
    }
    return list;
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

// Prints minimum distance and ranking
void printResult(list L, double dist, list c){
    printf("%lf\n", dist);
    int i = 0;
    while(i < findCard(L)){
        printf("%s\n", c(L[i]));
        i++;
    }
}
