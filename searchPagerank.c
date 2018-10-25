#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "c99.h"

#define TRUE 1
#define FALSE 0

typedef struct listNode *URL;

// node in the sorted url list
struct listNode {
    char *URL;
    double pageWeight;
    int countTerms;
    URL next;
} listNode;

URL newURLNode(char *url);
URL updateURLList(URL listHead, char *searchTerm);
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]);
URL URLInList(URL list, char *u);
URL insertURL(URL listHead, URL url);
URL sortList(URL listHead, URL url);
URL deleteURL(URL listHead, URL url);
double getPageWeight(char *url);
void showURLList(URL listHead);

// Makes a list of urls sorted by number of matching search terms and pageweight
int main(int argc, char *argv[]){
    URL URLList = NULL;
    
    // Update the URLList based on number of search terms and pageweight
    int i;
    for(i = 1; i < argc; i++){
        URLList = updateURLList(URLList, argv[i]);
    }
    
    // Print the results 
    showURLList(URLList);
    
}

// Create a new url node
URL newURLNode(char *url) {
    URL new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->pageWeight = getPageWeight(url);
    new->countTerms = 1;
    new->next = NULL;
    return new;
}

// adds to and updates the URLList based on nodes containing the given search term
URL updateURLList(URL listHead, char *searchTerm){
    // Collect list of URLs containing the search term
    char *URLArray[BUFSIZ];
    int nURLs = sTermURLs(searchTerm, URLArray);

    URL url = NULL;
    int i = 0;
    
    // Insert the first url into the list
    if (listHead == NULL && nURLs > 0) {
        url = newURLNode(URLArray[i]);
        listHead = url;
        i++;
    }
    
    // Make changes to the URLList according to the URLs containing the search term
    while(i < nURLs){
        if((url = URLInList(listHead, URLArray[i])) != NULL){ // Updates existing node position
            url->countTerms++;
            listHead = sortList(listHead, url); // Reposition url based on countTerms and pageweight
        }else{    // Adds new URL to list
            url = newURLNode(URLArray[i]);
            listHead = insertURL(listHead, url); // Position url based on countTerms and pageweight
        }
        i++;
    }

    return listHead;
}

// Returns array of URLs matching search term
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]){
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUFSIZ], *searchTermLine, *term;
    int found = FALSE;
    
    // Loops through entire file and finds search term
    while (fgets(fileLine, BUFSIZ, invertedIndex) != NULL){
        searchTermLine = strdup(fileLine);
        term = strsep(&searchTermLine, " ");
        if (strcmp(term, searchTerm) == 0) {    // Check if this is the line containing urls for the search term
            strsep(&searchTermLine, " ");       // Skip the second space
            found = TRUE;
            break;
        }
    }
    
    // Search term doesn't appear in collection
    if (found == FALSE)
        return 0;
        
    // Extract each URL matching search term and place into array
    char *urlToken = strsep(&searchTermLine, " ");
    int i = 0;
    while(searchTermLine != '\0'){
        urlArray[i] = malloc(strlen(urlToken) + 1);
        strcpy(urlArray[i], urlToken);
        urlToken = strsep(&searchTermLine, " ");
        i++;
    }
    
    // Extract the last url 
    if (urlToken != NULL) {
        urlToken = strsep(&urlToken, "\n"); // Strip the trailing newline
        urlArray[i] = malloc(strlen(urlToken) + 1);
        strcpy(urlArray[i], urlToken);
        i++;
    }
    
    fclose(invertedIndex);
    return i;
}

// Returns node if url is in list
URL URLInList(URL list, char *u){
    URL curr = list;
    while(curr != NULL){
        if(strcmp(curr->URL, u) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// Insert a URL into the URLList
URL insertURL(URL listHead, URL url) {
    URL curr = listHead, prev = NULL;
    
    // url is new listHead
    if (listHead == NULL || url->countTerms > listHead->countTerms ||
        (url->countTerms == listHead->countTerms && url->pageWeight > listHead->pageWeight)) {
        url->next = listHead;
        return url;
    }
    
    // Get to the nodes with the same countTerms as url
    while (curr != NULL && curr->countTerms > url->countTerms) {
        prev = curr;
        curr = curr->next;
    }
    // Get to the right pageWeight position
    while (curr != NULL && curr->countTerms == url->countTerms && curr->pageWeight > url->pageWeight) {
        prev = curr;
        curr = curr->next;
    }
    
    // Insert the url
    if (curr == NULL) { // Append
        prev->next = url;
    }else{ // Put url before curr
        prev->next = url;
        url->next = curr;
    }
    
    return listHead;
}

// Deletes old url and inserts new url into correct position
URL sortList(URL listHead, URL url) {
    listHead = deleteURL(listHead, url);
    listHead = insertURL(listHead, url);

    return listHead;
}

// Delete a url from the URLList
URL deleteURL(URL listHead, URL url){
    if (listHead == url) {
        return url->next;
    }
    else {
        URL curr = listHead;
        while (curr->next != url) {
            curr = curr->next;
        }  
        curr->next = url->next;
    }
    return listHead;
}

// Get the pageweight of a url
double getPageWeight(char *url) {
    double pageWeight;
    FILE *file = fopen("pagerankList.txt", "r");
    char fileLine[BUFSIZ];
    
    // Find the line regarding the url in the file
    while (fgets(fileLine, BUFSIZ, file) != NULL) {
        if (strstr(fileLine, url) != NULL)
            break;
    }
    fclose(file);
    
    // scan in the pageweight
    sscanf(fileLine, "%*s %*d, %lf\n", &pageWeight);
    
    return pageWeight;
}

// Print out the URLList
void showURLList(URL listHead) {
    URL curr = listHead;
    
    int i = 0;
    while(curr != NULL && i < 30) {
        printf("%s\n", curr->URL);
        curr = curr->next;
        i++;
    }
}

