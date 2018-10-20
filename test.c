#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readData.h"
#include "graph.h"

#define TRUE    1
#define FALSE   0

int main() {
  char *s = "url32, 3, 8.649292\n" ;
  double d ;
  char str[50];
   int num = 0;
  sscanf( s, "%s %d, %lf\n", str, &num, &d ) ;

  printf("%s %d, %lf\n", str, num, d ); 
}

