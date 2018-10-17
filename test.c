#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *urls[BUFSIZ], url[BUFSIZ];
    FILE *collection = fopen("test.txt", "r"); //FIXME make it collection.txt
    int i = 0;
    
    // make a list of URLS
    while (fscanf(collection, " %s", url) == 1) {
        urls[i] = malloc(strlen(url) + 1);
        strcpy(urls[i], url);
        printf("%s\n", urls[i]);
        i++;
    }
}
