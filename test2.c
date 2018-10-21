#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "graph.h"

int main(){ 
    Graph g = collectOutgoingURLs();
    showGraph(g);
}
