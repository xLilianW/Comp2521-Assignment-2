#include <stdio.h>
#include <string.h>

int main() {
    FILE *text = fopen("test.txt", "r");
    char url[50];
    while (fscanf(text, " %s", url) == 1) {
        printf("%s\n", url);
    }
}
