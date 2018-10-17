#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *urlFile = fopen("test.txt", "r");    

    char url[50];
    fscanf(urlFile, "%*s#start Section-2", NULL);
    fscanf(urlFile, " %s", url);
    while (strcmp(url, "#end") != 0) {
        printf("%s\n",url);
        fscanf(urlFile, " %s", url);
    } 
}
