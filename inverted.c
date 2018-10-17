#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"
#include "readData.h"

void BSTreeInfix(BSTree t);

int main() {
    BSTree invertedIndex = collectInvertedIndex();
    BSTreeInfix(invertedIndex);
}

