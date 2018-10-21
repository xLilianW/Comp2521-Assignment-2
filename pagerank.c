#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pagerank.h"
#include "readData.h"


// Returns list of urls with page ranks (doesnt return anything)
void pageRankW(double d, double diffPR, int maxIterations){
    Graph g = collectOutgoingURLs();
    //showGraph(g);
    
    for(int i = 0; i < numNodes(g); i++){
        setPageWeight(getPage(g, i), 1.0/numNodes(g));    // Initialise page weights
    }
    
    int i = 0;
    double diff = diffPR;
    while(i < maxIterations && diff >= diffPR){
        printf("i %d diff %lf \n", i, diff);
        int j;
        for(j = 0; j < numNodes(g); j++){
            double prevWeight = getPageWeight(getPage(g, j));
            //printf("prevWeight %lf calcPageRank %lf\n", prevWeight, calcPageRank(g, getPage(g,j), d));
            setPageWeight(getPage(g, j), calcPageRank(g, getPage(g, j), d));
            diff = fabs(getPageWeight(getPage(g, j)) - prevWeight);
            printf("diff %lf\n", diff);
        }
        i++;
    }
    printf("maxIterations %d i %d diff %lf \n", maxIterations, i, diff);
    orderWGraphPages(g);
}
double calcPageRank(Graph g, GraphPage p, double d){    //TODO
    double sumOutGoing = 0.0;
    
    // Search through all pages with outgoing links to p
    int i = 0;
    for(i = 0; i < numNodes(g); i++){
        if(isInLink(g, p, getPage(g, i))){
            sumOutGoing += getPageWeight(getPage(g, i))*inLinkPopularity(g, getPage(g, i), p)*outLinkPopularity(g, getPage(g, i), p);
        }
    }
    double pageRank = (1-d)/(numNodes(g)) + (d*sumOutGoing);
    printf("d %lf sumOutGoing %lf pageRank %lf\n", d, sumOutGoing, pageRank);
    return pageRank;
}

//do we need separate ones for inLink and outLink?
double inLinkPopularity(Graph g, GraphPage v, GraphPage u){
    double sumRefLinks = 0.0;
    int curr = findURLIndex(g, v);
    while(getPage(g, curr) != NULL){    // Search through all reference pages for v
        sumRefLinks += countInLinks(g, getPage(g, curr));
        curr++;
    }
    //printf("inLinkPopularity %lf\n", countInLinks(g, u)/sumRefLinks);
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
    //printf("outLinkPopularity %lf\n", countOutLinks(g, u)/sumRefLinks);
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
void orderWGraphPages(Graph g){   //TODO (very inefficient)
    FILE *pagerankList = fopen("pagerankList.txt", "w");
    
    double largestWeight = 0.0;
    int largestPage = 0;
    
    int i;
    for(i = 0; i < numNodes(g); i++){
        int j;
        for(j = 0; j < numNodes(g); j++){
            if(getPageWeight(getPage(g, j)) >= largestWeight){
                largestWeight = getPageWeight(getPage(g, j));
                largestPage = j;
            }
        }
        fprintf(pagerankList, "%s, %d, %.7f\n", getURL(getPage(g, largestPage)), countOutLinks(g, getPage(g, largestPage)), getPageWeight(getPage(g, largestPage)));
        setPageWeight(getPage(g, largestPage), -1);
    }
    fclose(pagerankList);
}

// Orders urls by page rank
void orderWGraphPages(Graph g){   //TODO (very inefficient)
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
        //TODO getURL cant just be for largest
        fprintf(pagerankList, "%s, %d, %.7f\n", getURL(getPage(g, largestPage)), countOutLinks(g, getPage(g, largestPage)), getPageWeight(getPage(g, largestPage)));
    }
    fclose(pagerankList);
}
