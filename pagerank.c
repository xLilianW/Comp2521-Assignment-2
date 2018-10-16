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
double calcPageRank(p){    //TODO
    double sumOutgoing;
    for (all pages, inPage, with outgoing links to p){
        sumOutgoing = sumOutgoing + (inPage->pageRank)*inLinkPopularity(inPage, p)*outLinkPopularity(inPage, p);
    }
    double pageRank = (1-d)/(g->nV) + (d*sumOutgoing);
}

//do we need separate ones for inLink and outLink?
double inLinkPopularity(v, u){
    int sumRefLinks = 0;
    Outgoing curr = g->connections[v];
    while(curr->next != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countInLinks(curr);
        curr = curr->next;
    }
    
    return countInLinks(u)/sumRefLinks;
}
int countInLinks(url){    //TODO
    return numInLinks;
}

double outLinkPopularity(v, u){
    int sumRefLinks = 0;
    Outgoing curr = g->connections[v];
    while(curr->next != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countOutLinks(curr);
        curr = curr->next;
    }
    
    return countOutLinks(u)/sumRefLinks;
}
int countOutLinks(url){    //TODO
    return ((numOutLinks > 0) ? numOutLinks : 0.5);
}

orderWeightedPages(){   //TODO
    // Order urls by page rank
}
