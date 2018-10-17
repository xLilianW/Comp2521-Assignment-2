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
    double sumOutGoing;
    for (all pages (inPage) with outgoing links to p){
        sumOutGoing = sumOutGoing + (inPage->pageRank)*inLinkPopularity(inPage, p)*outLinkPopularity(inPage, p);
    }
    double pageRank = (1-d)/(g->nV) + (d*sumOutGoing);
}

//do we need separate ones for inLink and outLink?
double inLinkPopularity(Outgoing v, Outgoing u){
    int sumRefLinks = 0;
    Outgoing curr = g->connections[findURLIndex(g, v)];
    while(curr->next != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countInLinks(curr);
        curr = curr->next;
    }
    
    return countInLinks(u)/sumRefLinks;
}
int countInLinks(url){    //TODO
    return numInLinks;
}

double outLinkPopularity(Outgoing v, Outgoing u){
    int sumRefLinks = 0;
    Outgoing curr = g->connections[findURLIndex(v)];
    while(curr != NULL){    // Search through all reference pages for v
        sumRefLinks = sumRefLinks + countOutLinks(curr);
        curr = curr->next;
    }
    
    return countOutLinks(u)/sumRefLinks;
}
// Counts number of outgoing links a given url has
int countOutLinks(url){    //TODO   (check if this counts itself as a link)
    int numOutLinks;
    Outgoing curr = g->connections[findURLIndex(url)];
    while(curr != NULL){
        numOutLinks++;
        curr = curr->next;
    }
    return ((numOutLinks > 0) ? numOutLinks : 0.5);
}

orderWeightedPages(){   //TODO
    // Order urls by page rank
}
