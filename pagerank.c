#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

typedef struct graphListNode *GraphPage;

void pageRankW(Graph, int, double, int);
double calcPageRank(Graph, GraphPage, int);
double inLinkPopularity(Graph, GraphPage, GraphPage);
int countInLinks(Graph, GraphPage);
int isInLink(Graph, GraphPage, GraphPage);
double outLinkPopularity(Graph, GraphPage, GraphPage);
int countOutLinks(Graph, GraphPage);
void orderWeightedGraphPages(Graph);


// Returns list of urls with page ranks
void pageRankW(Graph g, int d, double diffPR, int maxIterations){
    
    for(int i = 0; i < g->nV; i++){
        g->connections[i]->pageWeight = 1/g->nV;    // Initialise page weights
    }
    
    int i = 0;
    double diff = diffPR;
    while(i < maxIterations && diff >= diffPR){
        //random calculations
        i++;
        double prevWeight = g->connections[i]->pageWeight;
        g->connections[i]->pageWeight = calcPageRank(g, g->connections[i], d);
        
        diff = fabs(g->connections[i]->pageWeight - prevWeight);
    }
}
double calcPageRank(Graph g, GraphPage p, int d){    //TODO
    double sumOutGoing;
    
    // Search through all pages with outgoing links to p
    int i = 0;
    for(i = 0; i < g->nV; i++){
        GraphPage currPage = g->connections[i];
        if(isInLink(g, p, currPage)){
            sumOutGoing += (currPage->pageWeight)*inLinkPopularity(g, currPage, p)*outLinkPopularity(g, currPage, p);
        }
    }
    double pageRank = (1-d)/(g->nV) + (d*sumOutGoing);
}

//do we need separate ones for inLink and outLink?
double inLinkPopularity(Graph g, GraphPage v, GraphPage u){
    int sumRefLinks = 0;
    GraphPage curr = g->connections[findURLIndex(g, v)];
    while(curr->next != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countInLinks(g, curr);
        curr = curr->next;
    }
    return countInLinks(g, u)/sumRefLinks;
}
int countInLinks(Graph g, GraphPage url){    //check if this counts itself as inlink
    int numInLinks = 0;
    int i = 0;
    for (i = 0; i < g->nV; i++){
        if(isInLink(g, url, g->connections[i])){
            numInLinks++;
        }
    }
    return numInLinks;
}
// Returns 1 if Page v has an outgoing link to Page u, an ingoing link of u
int isInLink(Graph g, GraphPage u, GraphPage v){
    GraphPage curr = g->connections[findURLIndex(g, v)];
    while(curr != NULL){
        if(strcmp(curr->URL, u->URL) == 0){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
} 

double outLinkPopularity(Graph g, GraphPage v, GraphPage u){
    double sumRefLinks = 0.0;
    GraphPage curr = g->connections[findURLIndex(g, v)];
    while(curr != NULL){    // Search through all reference pages for v
        int numOutLinks = countOutLinks(g, curr);
        if(numOutLinks > 0){
            sumRefLinks = sumRefLinks + numOutLinks;
        }else{
            sumRefLinks = sumRefLinks + 0.5;
        }
        curr = curr->next;
    }
    
    return countOutLinks(g, u)/sumRefLinks;
}
// Counts number of outgoing links a given url has
int countOutLinks(Graph g, GraphPage url){    //TODO   (check if this counts itself as a link)
    int numOutLinks;
    GraphPage curr = g->connections[findURLIndex(g, url)];
    while(curr != NULL){
        numOutLinks++;
        curr = curr->next;
    }
    return numOutLinks;
}
// Orders urls by page rank
void orderWeightedPages(Graph g){   //TODO (very inefficient)
    FILE *pagerankList = fopen("pagerankList.txt", "w");
    double largest = 0.0;
    int largestIndex = 0;
    int i = 0;
    for(i = 0; i < g->nV; i++){
        int j = 0;
        for(j = 0; j < g->nV; j++){
            if(g->connections[j]->pageWeight >= largest){
                largest = g->connections[j]->pageWeight;
                largestIndex = j;
            }
        }
        GraphPage largestPage = g->connections[largestIndex];
        fprintf(pagerankList, "%s, %d, %.7f\n", largestPage->URL, countOutLinks(g, largestPage), largestPage->pageWeight);
    }
    fclose(pagerankList);
}
