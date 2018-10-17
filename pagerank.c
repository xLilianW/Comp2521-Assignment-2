#include <stdio.h>
#include <stdlib,h>
#include "graph.h"
#include "readData.c"

Graph g = collectData();

// Returns list of urls with page ranks
// d = damping factor (0.85), diffPR = difference in page rank sum
pageRankW(g, d, diffPR, maxIterations){
    
    for(int i = 0; i < g->nV; i++){
        g->connections[i]->pageWeight = 1/g->nV;    // Initialise page weights
    }
    
    int i = 0;
    diff = diffPR;
    while(i < maxIterations && diff >= diffPR){
        //random calculations
        i++;
        g->connections[i]->pageWeight = calcPageRank();
        
        
        //diff = sum of absolute differences of page ranks at t+1 and t for all nodes
    }
}
double calcPageRank(Graph g, Page p){    //TODO
    double sumOutGoing;
    
    // Search through all pages with outgoing links to p
    int i = 0;
    for(i; i < g->nV; i++){
        Page currPage = g->connections[i];
        if(isInLink(g, p, currPage)){
            sumOutGoing += (currPage->pageWeight)*inLinkPopularity(g, currPage, p)*outLinkPopularity(g, currPage, p);
        }
    }
    double pageRank = (1-d)/(g->nV) + (d*sumOutGoing);
}

//do we need separate ones for inLink and outLink?
double inLinkPopularity(Graph g, Page v, Page u){
    int sumRefLinks = 0;
    Page curr = g->connections[findURLIndex(g, v)];
    while(curr->next != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countInLinks(curr);
        curr = curr->next;
    }
    return countInLinks(g, u)/sumRefLinks;
}
int countInLinks(Graph g, Page url){    //check if this counts itself as inlink
    int i = 0;
    for (i; i < g->nV; i++){
        if(isInLink(g, url, g->connections[i])){
            numInLinks++;
        }
    }
    return numInLinks;
}
// Returns 1 if Page v has an outgoing link to Page u, an ingoing link of u
int isInLink(Graph g, Page u, Page v){
    Page curr = g->connections[findURLIndex(v)];
    while(curr != NULL){
        if(strcmp(curr->URL, u->URL) == 0){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
} 

double outLinkPopularity(Graph g, Page v, Page u){
    int sumRefLinks = 0;
    Page curr = g->connections[findURLIndex(v)];
    while(curr != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countOutLinks(curr);
        curr = curr->next;
    }
    
    return countOutLinks(g, u)/sumRefLinks;
}
// Counts number of outgoing links a given url has
int countOutLinks(Graph g, Page url){    //TODO   (check if this counts itself as a link)
    int numOutLinks;
    Page curr = g->connections[findURLIndex(url)];
    while(curr != NULL){
        numOutLinks++;
        curr = curr->next;
    }
    return ((numOutLinks > 0) ? numOutLinks : 0.5);
}

orderWeightedPages(){   //TODO
    // Order urls by page rank
}
