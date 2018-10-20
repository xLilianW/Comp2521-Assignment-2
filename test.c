#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BSTree.h"
#include "readData.h"
#include "pagerank.c"
#include "graph.h"

#define TRUE    1
#define FALSE   0

int main(int argc, char *argv[]) {
    Graph g = collectOutgoingURLs();
    pageRankW(g, atof(argv[1]), atof(argv[2]), atoi(argv[3]));
    showGraph(g);
    return 0;
}

