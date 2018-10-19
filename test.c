#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readData.h"
#include "graph.h"

#define TRUE    1
#define FALSE   0

int main() {
    Graph g = collectOutgoingURLs();
    showGraph(g);
}

