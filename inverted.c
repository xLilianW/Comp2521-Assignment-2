#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h" 
#include "readData.h"

int main() {
    BSTree invertedIndex = collectInvertedIndex();  // get the BSTree containing the invertedIndex
    FILE *index = fopen("invertedIndex.txt", "w"); 
    BSTreeInfix(invertedIndex, index);              // print the BSTree contents to the file
    fclose(index);
    freeBSTree(invertedIndex);
}

