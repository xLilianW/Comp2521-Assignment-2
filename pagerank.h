#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"

void pageRankW(double, double, int);
double calcPageRank(Graph, GraphPage, int);
double inLinkPopularity(Graph, GraphPage, GraphPage);
int countInLinks(Graph, GraphPage);
int isInLink(Graph, GraphPage, GraphPage);
double outLinkPopularity(Graph, GraphPage, GraphPage);
int countOutLinks(Graph, GraphPage);
void orderWGraphPages(Graph); //improve func name
int findURLIndex(Graph, GraphPage);

#endif
