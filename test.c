#include <stdio.h>
#include <string.h>

int main() {
    FILE *text = fopen("test.txt", "r");
    char url[50];
    fscanf(text, "%*[^\n]\n%*[^\n]\n", NULL,NULL); // skip #start section 1
    while (fscanf(text, " %s", url) == 1) {
        printf("%s\n", url);
    }
}
