#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *urlFile = fopen("url11.txt", "r");    
    fscanf(urlFile, "%*[^\n]%*[^#]#%*[^#]#%*[^\n]\n", NULL, NULL, NULL, NULL); // skip to section 2
    char word[30];
    fscanf(urlFile, " %s", word);
    printf("%s", word);
}
