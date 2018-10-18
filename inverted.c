#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h" 
#include "readData.h"

int main() {
    BSTree invertedIndex = collectInvertedIndex();
    //FILE *index = fopen("invertedIndex.txt", "w");
    BSTreeInfix(invertedIndex, stdout);
}

