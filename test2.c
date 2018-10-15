#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char *string = strdup(" url1    url2 url3");
    char *token;
    token = strtok(string, "u");
    printf("%s\n", token);
    while(token != '\0'){
        token = strtok(string, " ");
        printf("%s\n", token);
        token = strtok(string, "u");
        printf("%s\n", token);
    }
    
    
}
