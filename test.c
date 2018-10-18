#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *string = "hello.";
    char *p = &string[strlen(string)-1];
    if (strcmp(p, ".") == 0) {
        *p = '\0';
    }   
    printf("%s", string);
}
