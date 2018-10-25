#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"

void pageRankW(double, double, int);
double calcPageRank(Graph, GraphPage, double);
double inLinkPopularity(Graph, GraphPage, GraphPage);
int countInLinks(Graph, GraphPage);
int isInLink(Graph, GraphPage, GraphPage);
double outLinkPopularity(Graph, GraphPage, GraphPage);
int countOutLinks(Graph, int);
void orderWGraphPages(Graph); //improve func name
int findURLIndex(Graph, GraphPage);

#endif
