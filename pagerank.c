#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graph.h"
#include "readData.h"

double calcPageRank(Graph, GraphPage, double);
void orderWGraphPages(Graph);

// Creates file containing list of urls ordered by page ranks
int main(int argc, char *argv[]){
    if (argc < 4) {
        fprintf(stderr, "Correct Usage: ./pagerank d diffPR maxIterations\n");
        exit(1);
    }
    
    double d = atof(argv[1]), diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    
    Graph g = collectOutgoingURLs();
    showGraph(g);
    
    for(int i = 0; i < numNodes(g); i++){
        setPageWeight(getPage(g, i), 1.0/numNodes(g));    // Initialise page weights
    }
    
    int i = 0;
    double diff = diffPR;
    while(i < maxIterations && diff >= diffPR){
        int j;
        for(j = 0; j < numNodes(g); j++){
            double prevWeight = getPageWeight(getPage(g, j));
            setPageWeight(getPage(g, j), calcPageRank(g, getPage(g, j), d));
            diff = fabs(getPageWeight(getPage(g, j)) - prevWeight);
        }
        i++;
    }
    orderWGraphPages(g);
    freeGraph(g);
}

// Calculates page rank
double calcPageRank(Graph g, GraphPage p, double d){
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

// Orders urls by page rank
void orderWGraphPages(Graph g){
    FILE *pagerankList = fopen("pagerankList.txt", "w");
    
    double largestWeight = 0.0;
    int largestPage = 0;
    
    int i;
    for(i = 0; i < numNodes(g); i++){
        int j;
        largestWeight = 0.0;
        largestPage = 0;
        for(j = 0; j < numNodes(g); j++){
            if(getPageWeight(getPage(g, j)) >= largestWeight){
                largestWeight = getPageWeight(getPage(g, j));
                largestPage = j;
            }
        }
        fprintf(pagerankList, "%s, %d, %.7f\n", getURL(getPage(g, largestPage)), countOutLinks(g, largestPage), getPageWeight(getPage(g, largestPage)));
        setPageWeight(getPage(g, largestPage), -1);
    }
    fclose(pagerankList);
}
