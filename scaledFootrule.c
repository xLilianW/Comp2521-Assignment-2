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
int *generateP(int *, int);
int *copyArray(int *, int *, int);
double calcSFDist(urlNode, int, int, int);
int findTCard(urlNode);
int findCCard(char **);
int positionInNodeList(char *, urlNode);
int positionInList(char *, char **);
void getCList(urlNode *, char **);
urlNode *getTLists(int, char *[]);
void printResult(int *, double, char **);


int main(int argc, char *argv[]){
    urlNode *tLists = getTLists(argc-1, argv);
    char *cList[BUFSIZ];    
    getCList(tLists, cList);
    int pList[findCCard(cList)];
    int bestPList[findCCard(cList)];
    int x;
    for(x = 0; x < findCCard(cList); x++){
        pList[x] = x;
        bestPList[x] = x;
    }
    
    double totalDist = 0.0;
    double minDist = -1.0;
    
    int i = 0;
    while(i < findCCard(cList)){    // Loops through each alternate set of p(TODO 1 too many loops?)
        copyArray(pList, generateP(pList, i), findCCard(cList));
        int j = 0;
        while(j < findCCard(cList)){    // Loops through each element in C urlNode
            int k;
            for(k = 0; k < argc-1; k++){    // Loops through each urlNode
                totalDist += calcSFDist(tLists[k], positionInList(cList[j], cList), pList[j], findCCard(cList));
                if(totalDist < minDist || minDist == -1.0){
                    minDist = totalDist;
                    copyArray(bestPList, pList, findCCard(cList));
                }
            }
            j++;
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

// Returns cardinality of c list
int findCCard(char **c){
    int i = 0;
    while(c[i] != NULL){
        i++;
    }
    return i;
}

// Returns new urlNode by swapping adjacent elements in urlNode
int *generateP(int *pList, int i){
    int temp = pList[i];
    pList[i] = pList[i+1];
    pList[i+1] = temp;
    return pList;
}

// Returns calulated scaled footrule aggregation
double calcSFDist(urlNode t, int c, int p, int n){
    int cardT = findTCard(t);
    double result = fabs((double)c/cardT - p/n);
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

// Returns position of string in node list
int positionInNodeList(char *c, urlNode L){
    urlNode curr = L;
    int i = 0;
    while(curr != NULL){
        if(strcmp(curr->url, c) == 0){
            return i;
        }
        i++;
        curr = curr->next;
    }
    return -1;
}

// Returns position of string in array
int positionInList(char *c, char **L){
    int i = 0;
    while(L[i] != NULL){
        if(strcmp(L[i], c) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

// Returns union of urls in lists
void getCList(urlNode *Lists, char *list[BUFSIZ]){
    int i = 0, j = 0;
    
    while(Lists[i] != NULL){    // Loops through each urlNode
        urlNode curr = Lists[i];
        while(curr != NULL){    // Loops through each urlNode node
            if(positionInList(curr->url, list) == -1){
                list[j] = strdup(curr->url);    // Adds url to urlNode
                j++;
            }
            curr = curr->next;
        }
        i++;
    }

}

// get urlNode of ordered urls in each search urlNode
urlNode *getTLists(int nFiles, char *files[]){
    urlNode *tLists = malloc((nFiles+1)*sizeof(listNode));
    urlNode curr = NULL;
    int i;
    
    for(i = 0; i < nFiles; i++){    //TODO nFiles-1?
        // open file
        FILE *file;
        if ((file = fopen(files[i+1], "r")) == NULL){
            perror("");
        }
        
        char url[URLSIZE];
        
        // insert first URL
        if (fscanf(file, " %s", url) == 1) {
            tLists[i] = newNode(url);
            curr = tLists[i];
        }
        else // empty file
            continue;
        
        // make a urlNode of URLS
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

// Prints minimum distance and ranking
void printResult(int *L, double dist, char **c){
    printf("%lf\n", dist);
    int i = 0;
    while(c[L[i]] != NULL){
        printf("%s\n", c[L[i]]);
        i++;
    }
}
