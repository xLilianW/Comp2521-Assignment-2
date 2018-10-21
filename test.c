
#include "pagerank.c"

#define TRUE    1
#define FALSE   0

int main(int argc, char *argv[]) {
    pageRankW(atof(argv[1]), atof(argv[2]), atoi(argv[3]));
    return 0;
}

