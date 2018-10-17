#include <stdio.h>
#include <stdlib.h>
#include "readData.c"
#include "graph.h"
int main() {
    Graph g = collectOutgoingURLs();
    printf("%d", numNodes(g));
}
