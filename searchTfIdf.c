#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "c99.h"

#define TRUE 1
#define FALSE 0

typedef struct listNode *URL;

// Node containing a url
struct listNode {
    char *URL;
    double tfidf;
    int countTerms;
    URL next;
} listNode;

URL newURLNode(char *url, double tfidf);
URL updateURLList(URL listHead, char *searchTerm, int nDocs);
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]);
URL URLInList(URL list, char *u);
URL insertURL(URL listHead, URL url);
URL sortList(URL listHead, URL url);
URL deleteURL(URL listHead, URL url);
int getNDocs();
double termFrequency(char *term, char *url);
double inverseDocumentFrequency(double containingDocs, double nDocs);
void lowercase(char *word);
char *removePunctuation(char *string);
void showURLList(URL listHead);
void freeURLList(URL listHead);

// Make a sorted list of urls based on number of matching search terms and tfidf
int main(int argc, char *argv[]){
    URL URLList = NULL;
    int nDocs = getNDocs();
    
    // For each URL, add to and update URLList
    int i;
    for(i = 1; i < argc; i++){
        URLList = updateURLList(URLList, argv[i], nDocs);
    }
    
    // Print the results 
    showURLList(URLList);
    
    freeURLList(URLList);
}

// Make a new URL node
URL newURLNode(char *url, double tfidf) {
    URL new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->tfidf = tfidf;
    new->countTerms = 1;
    new->next = NULL;
    return new;
}

// Add to and update URLList based on urls containing the search term
URL updateURLList(URL listHead, char *searchTerm, int nDocs){
    // Collect list of URLs containing the search term
    char *URLArray[BUFSIZ];
    int nURLs = sTermURLs(searchTerm, URLArray);
    
    if (nURLs == 0) return listHead;
    
    double tfidf, idf = inverseDocumentFrequency(nURLs, nDocs);

    URL url = NULL;
    int i = 0;
    
    // Insert the first url into the list
    if (listHead == NULL) {
        tfidf = termFrequency(searchTerm, URLArray[i]) * idf;
        url = newURLNode(URLArray[i], tfidf);
        listHead = url;
        i++;
    }
    
    // Make changes to the URLList according to the URLs containing the search term
    while(i < nURLs){
        tfidf = termFrequency(searchTerm, URLArray[i]) * idf;
        if((url = URLInList(listHead, URLArray[i])) != NULL){ // Updates existing node position
            url->countTerms++;
            url->tfidf += tfidf;
            listHead = sortList(listHead, url); // Reposition url based on countTerms and tfidf
        }else{    // Adds new URL to list
            url = newURLNode(URLArray[i], tfidf);
            listHead = insertURL(listHead, url); // Position url based on countTerms and tfidf
        }
        i++;
    }

    return listHead;
}

// Returns array of URLs matching search term
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]) {
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUFSIZ], *searchTermLine, *term;
    int found = FALSE;
    
    // Loops through entire file and finds search term
    while (fgets(fileLine, BUFSIZ, invertedIndex) != NULL){
        searchTermLine = strdup(fileLine);
        term = strsep(&searchTermLine, " ");
        if (strcmp(term, searchTerm) == 0) {    // check if this is the line containing urls for the search term
            strsep(&searchTermLine, " ");    // Skip the second space
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
        (url->countTerms == listHead->countTerms && url->tfidf > listHead->tfidf)) {
        url->next = listHead;
        return url;
    }
    
    // Get to the nodes with the same countTerms as url
    while (curr != NULL && curr->countTerms > url->countTerms) {
        prev = curr;
        curr = curr->next;
    }
    // Get to the right tfidf position
    while (curr != NULL && curr->countTerms == url->countTerms && curr->tfidf > url->tfidf) {
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

// Get the number of documents in collection.txt
int getNDocs() {
    FILE *collection = fopen("collection.txt", "r"); 
    int nDocs = 0;
    char temp[BUFSIZ];
    
    while (fscanf(collection, " %s", temp) == 1) {
        nDocs++;
    }
    fclose(collection);

    return nDocs;
}

// Calculate the term frequency of a term within a page, proportionate to the number of words
double termFrequency(char *term, char *url) {
    // Open the url file
    char *fileName = strdup(url);
    fileName = realloc(fileName, strlen(url) + strlen(".txt") + 1);
    strcat(fileName, ".txt");  
    FILE *page = fopen(fileName, "r");

    double count = 0.0, words, termFreq;
    fscanf(page, "%*[^\n]%*[^#]#%*[^#]#%*[^\n]\n"); // Skip to section 2 

    char word[BUFSIZ];
    fscanf(page, " %s", word);
        
    // Loop through words to find term frequency
    for (words = 0.0; strcmp(word, "#end") != 0; words++) {
        // Normalise the word
        lowercase(word);
        strcpy(word,removePunctuation(word));
        
        if (strcmp(term,word) == 0)
            count++;
        fscanf(page, " %s", word);
    }
    
    termFreq = count/words;
    return termFreq;
}

// Calculate inverse document frequency
double inverseDocumentFrequency(double containingDocs, double nDocs) {
    double quotient = nDocs/containingDocs;
    double inverseDocFreq = log10(quotient);
    return inverseDocFreq;
}



// From https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
// Make a word lowercase
void lowercase(char *word) {
    for ( ; *word; ++word) *word = tolower(*word);
}

// Remove trailing punctuation
char *removePunctuation(char *string) { //FIXME is there a better way? edit string directly
    char *str = strdup(string);
    if (string[strlen(string)-1] == '.' || string[strlen(string)-1] == ',' || string[strlen(string)-1] == ';' || string[strlen(string)-1] == '?') {
        str[strlen(str)-1] = '\0';
    } 
    return str;  
}

void showURLList(URL listHead) {
    URL curr = listHead;
    int i = 0;
    while(curr != NULL && i < 30) {
        printf("%s  %.6f\n", curr->URL, curr->tfidf);
        curr = curr->next;
        i++;
    }
}

// clean up the urllist
void freeURLList(URL listHead) {
    URL curr = listHead, next;
    while (curr != NULL) {
        free(curr->URL);
        next = curr->next;
        free(curr);
        curr = next;
    }
}


