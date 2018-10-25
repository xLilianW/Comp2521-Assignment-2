#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "c99.h"

#define TRUE    1
#define FALSE   0
#define URLSIZE 50

typedef struct listNode *urlNode;

typedef struct listNode {
    char *url;
    urlNode next;
} listNode;

urlNode newNode(char *);
int *generateP(int *, int, int);
int *copyArray(int *, int *, int);
double calcSFDist(urlNode, int, int, int);
int findTCard(urlNode);
int inList(char *, char **, int);
int getCList(urlNode *, char **);
urlNode *getTLists(int, char *[]);
char *getURL(urlNode list, int i);
int getCIndex(char **cList, char *url, int numCURLs);
int getPIndex(int *pList, int index, int numCURLs);
int fac(int);
void printResult(int *, double, char **);


int main(int argc, char *argv[]){
    urlNode *tLists = getTLists(argc-1, argv);
    char *cList[BUFSIZ];
    int numCURLs = getCList(tLists, cList), numTURLs;
    int pList[numCURLs], bestPList[numCURLs];
    int pIndex, cIndex;
    int pCombinations = fac(numCURLs);
    
    int x;
    for(x = 0; x < numCURLs; x++){
        pList[x] = x;
        bestPList[x] = x;
    }
    
    double totalDist = 0.0;
    double minDist = -1.0;
    
    int i = 0, j, k;
    while(i < pCombinations){    // Loops through each alternate set of p(TODO 1 too many loops?)
        copyArray(pList, generateP(pList, i, numCURLs), numCURLs);
        totalDist = 0.0;
        for(k = 0; k < argc-2; k++){    // Loops through each list file
            numTURLs = findTCard(tLists[k]);
            j = 0;
            while(j < numTURLs){    // Loops through each node in the list
                char *url = getURL(tLists[k], j);
                cIndex = getCIndex(cList, url, numCURLs);
                pIndex = (pList, cIndex, numCURLs);
                totalDist += calcSFDist(numTURLs, j, pIndex, numCURLs);
                j++;
            }
        }
        printf("calc %lf\n", totalDist);
        if(totalDist < minDist || minDist == -1.0){
            minDist = totalDist;
            copyArray(bestPList, pList, numCURLs);
        }
        i++;
    }
    printResult(bestPList, minDist, cList);
}

urlNode newNode(char *url) {
    urlNode new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->url = strdup(url);
    new->next = NULL;
    return new;
}

int *copyArray(int *array1, int *array2, int len){
    int i;
    for(i = 0; i < len; i++){
        array1[i] = array2[i];
    }
    return array1;
}

// Returns new urlNode by swapping adjacent elements in urlNode
int *generateP(int *pList, int i, int nURLs){
    int x = i%nURLs;
    int y = (i+1)%nURLs;
    
    int temp = pList[x];
    pList[x] = pList[y];
    pList[y] = temp;
    return pList;
}

// Returns calulated scaled footrule aggregation
double calcSFDist(int cardT, int c, int p, int n){
    double result = fabs((double)c/cardT - (p+1)/n);
    return result;
}

// Returns cardinality of a urlNode list
int findTCard(urlNode L){
    urlNode curr = L;
    int i = 0;
    while(curr != NULL){
        curr = curr->next;
        i++;
    }
    return i;
}

// Returns position of string in array //TODO change to inList not position
int inList(char *c, char **L, int numCURLs){
    int i = 0;
    while(i < numCURLs){
        //printf("%s\n", L[i]);
        if(strcmp(L[i], c) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

// Returns union of urls in lists
int getCList(urlNode *Lists, char *list[BUFSIZ]){
    int i = 0, j = 0;
    
    while(Lists[i] != NULL){    // Loops through each urlNode
        urlNode curr = Lists[i];
        while(curr != NULL){    // Loops through each list node
            if(inList(curr->url, list, j) == -1){
                list[j] = strdup(curr->url);    // Adds url to urlNode
                j++;
            }
            curr = curr->next;
        }
        i++;
    }
    return i;
}

// get urlNode of ordered urls in each search urlNode
urlNode *getTLists(int nFiles, char *files[]){
    urlNode *tLists = malloc((nFiles+1)*sizeof(listNode));
    urlNode curr = NULL;
    int i;
    
    for(i = 0; i < nFiles; i++){   
        // Open file
        FILE *file;
        if ((file = fopen(files[i+1], "r")) == NULL){
            perror("");
        }
        
        char url[URLSIZE];
        
        // Insert first URL
        if (fscanf(file, " %s", url) == 1) {
            tLists[i] = newNode(url);
            curr = tLists[i];
        }
        else // empty file
            continue;
        
        // Make a urlNode of URLS
        while (fscanf(file, " %s", url) == 1) {
            urlNode node = newNode(url);
            curr->next = node;
            curr = node;
        }
        fclose(file);
    }
    tLists[nFiles] = NULL; // signify end of lists
    
    return tLists;   
}

// Returns the jth url in a tlist
char *getURL(urlNode list, int i) {
    urlNode curr = list;
    int i;
    for (i=0; i < j; i++) {
        curr = curr->next;
    }
    return curr->url;
}

// Returns the urls index in cList
int getCIndex(char **cList, char *url, int numCURLs) {
    int i;
    for (i=0; i < numCURLs; i++) {
        if (strcmp(cList[i], url) == 0)
            return i;
    }
    
    return -1; // should never get here    
}

// Returns the index's index in pList
int getPIndex(int *pList, int index, int numCURLs) {
    int i;
    for (i=0; i < numCURLs; i++) {
        if (pList[i] == index)
            return i;
    }
    
    return -1; // should never get here    
}

// Calculates n!
int fac(int n) {
    int c, fact = 0;
    for (c = 1; c <= n; c++)
        fact *= c;
    return fact;
}

// Prints minimum distance and ranking
void printResult(int *L, double dist, char **c){
    printf("%lf\n", dist);
    int i = 0;
    while(c[L[i]] != NULL){
        printf("%s\n", c[L[i]]);
        i++;
    }
}
