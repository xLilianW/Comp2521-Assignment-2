#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graph.h"

void pageRankW(Graph, int, double, int);
double calcPageRank(Graph, GraphPage, int);
double inLinkPopularity(Graph, GraphPage, GraphPage);
int countInLinks(Graph, GraphPage);
int isInLink(Graph, GraphPage, GraphPage);
double outLinkPopularity(Graph, GraphPage, GraphPage);
int countOutLinks(Graph, GraphPage);
void orderWGraphPages(Graph);
int findURLIndex(Graph, GraphPage);

// Returns list of urls with page ranks
void pageRankW(Graph g, int d, double diffPR, int maxIterations){
    
    for(int i = 0; i < numNodes(g); i++){
        setPageWeight(getPage(g, i), 1/numNodes(g));    // Initialise page weights
    }
    
    int i = 0;
    double diff = diffPR;
    while(i < maxIterations && diff >= diffPR){
        //random calculations
        i++;
        double prevWeight = getPageWeight(getPage(g, i));
        setPageWeight(getPage(g, i), calcPageRank(g, getPage(g, i), d));
        
        diff = fabs(getPageWeight(getPage(g, i)) - prevWeight);
    }
}
double calcPageRank(Graph g, GraphPage p, int d){    //TODO
    double sumOutGoing = 0.0;
    
    // Search through all pages with outgoing links to p
    int i = 0;
    for(i = 0; i < numNodes(g); i++){
        if(isInLink(g, p, getPage(g, i))){
            sumOutGoing += getPageWeight(getPage(g, i))*inLinkPopularity(g, getPage(g, i), p)*outLinkPopularity(g, getPage(g, i), p);
        }
    }
    double pageRank = (1-d)/(numNodes(g)) + (d*sumOutGoing);
    return pageRank;
}

//do we need separate ones for inLink and outLink?
double inLinkPopularity(Graph g, GraphPage v, GraphPage u){
    int sumRefLinks = 0;
    int curr = findURLIndex(g, v);
    while(getPage(g, curr+1) != NULL){    // Search through all reference pages for v
        sumRefLinks += countInLinks(g, getPage(g, curr));
        curr++;
    }
    return countInLinks(g, u)/sumRefLinks;
}
int countInLinks(Graph g, GraphPage url){    //check if this counts itself as inlink
    int numInLinks = 0;
    int i = 0;
    for (i = 0; i < numNodes(g); i++){
        if(isInLink(g, url, getPage(g, i))){
            numInLinks++;
        }
    }
    return numInLinks;
}
// Returns 1 if Page v has an outgoing link to Page u, an ingoing link of u
int isInLink(Graph g, GraphPage u, GraphPage v){
    int curr = findURLIndex(g, v);
    while(getPage(g, curr) != NULL){
        if(strcmp(getURL(getPage(g, curr)), getURL(u)) == 0){
            return 1;
        }
        curr++;
    }
    return 0;
} 

double outLinkPopularity(Graph g, GraphPage v, GraphPage u){
    double sumRefLinks = 0.0;
    int curr = findURLIndex(g, v);
    while(getPage(g, curr) != NULL){    // Search through all reference pages for v
        int numOutLinks = countOutLinks(g, getPage(g, curr));
        if(numOutLinks > 0){
            sumRefLinks += numOutLinks;
        }else{
            sumRefLinks += 0.5;
        }
        curr++;
    }
    return countOutLinks(g, u)/sumRefLinks;
}

// Counts number of outgoing links a given url has
int countOutLinks(Graph g, GraphPage url){    //TODO   (check if this counts itself as a link)
    int numOutLinks = 0;
    int curr = findURLIndex(g, url);
    while(getPage(g, curr) != NULL){
        numOutLinks++;
        curr++;
    }
    return numOutLinks;
}

// Orders urls by page rank
void orderWeightedPages(Graph g){   //TODO (very inefficient)
    FILE *pagerankList = fopen("pagerankList.txt", "w");
    double largest = 0.0;
    int largestIndex = 0;
    int i = 0;
    for(i = 0; i < numNodes(g); i++){
        int j = 0;
        for(j = 0; j < numNodes(g); j++){
            if(getPageWeight(getPage(g, i)) >= largest){
                largest = getPageWeight(getPage(g, i));
                largestIndex = j;
            }
        }
        int largestPage = largestIndex;
        fprintf(pagerankList, "%s, %d, %.7f\n", getURL(getPage(g, largestPage)), countOutLinks(g, getPage(g, largestPage)), getPageWeight(getPage(g, largestPage)));
    }
    fclose(pagerankList);
}
