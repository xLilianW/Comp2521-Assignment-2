#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *string = strdup("design.");
    if (string[strlen(string)-1] == '.' || string[strlen(string)-1] == ',' || string[strlen(string)-1] == ';' || string[strlen(string)-1] == '?') {
        string[strlen(string)-1] = '\0';
    } 
    printf("%s\n", string);
}
