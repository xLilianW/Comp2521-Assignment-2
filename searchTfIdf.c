#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "c99.h"

typedef struct listNode *URL;

struct listNode {
    char *URL;
    double tfidf;
    int countTerms;
    URL prev, next;
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

int main(int argc, char *argv[]){
    URL URLList = NULL;
    int nDocs = getNDocs();
    
    // Make list of URLs based on number of search terms in each URL
    int i;
    for(i = 1; i < argc; i++){
        printf("%d %s\n", i, argv[i]);
        URLList = updateURLList(URLList, argv[i], nDocs);
    }
    
    // Print the results 
    showURLList(URLList);
    
}

URL newURLNode(char *url, double tfidf) {
    URL new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->tfidf = tfidf;
    new->countTerms = 1;
    new->prev = new->next = NULL;
    return new;
}

// Makes list of URLs if they contain search term
// Places URLs with more search terms closer to start
// Places URLs with higher pageWeight closer to start
URL updateURLList(URL listHead, char *searchTerm, int nDocs){
    // collect list of URLs containing the search term
    char *URLArray[BUFSIZ];
    int nURLs = sTermURLs(searchTerm, URLArray);
    double tfidf, idf = inverseDocumentFrequency(nURLs, nDocs);

    URL url = NULL;
    int i = 0;
    
    // insert the first url into the list
    if (listHead == NULL && nURLs > 0) {
        tfidf = termFrequency(searchTerm, URLArray[i]) * idf;
        url = newURLNode(URLArray[i], tfidf);
        listHead = url;
        i++;
    }
    
    // make changes to the URLList according to the URLs containing the search term
    while(i < nURLs){
        tfidf = termFrequency(searchTerm, URLArray[i]) * idf;
        if((url = URLInList(listHead, URLArray[i])) != NULL){ // updates existing node position
            url->countTerms++;
            url->tfidf += tfidf;
            listHead = sortList(listHead, url); //position url on countTerms and pageweight
        }else{    // Adds new URL to list
            url = newURLNode(URLArray[i], tfidf);
            listHead = insertURL(listHead, url); //position url on countTerms and pageweight
        }
        showURLList(listHead);
        i++;
    }

    return listHead;
}

// Returns array of URLs matching search term
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]){
    // append " " to the search term so the exact word is found in the file
    char *searchTerm_copy = strdup(searchTerm);
    searchTerm_copy = realloc(searchTerm_copy, strlen(searchTerm) + 2);
    strcat(searchTerm_copy, " ");
    
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUFSIZ], *searchTermLine = NULL;
    
    // Loops through entire file and finds search term
    while(fgets(fileLine, BUFSIZ, invertedIndex) != NULL){
        if(strstr(fileLine, searchTerm_copy) != NULL){
            searchTermLine = strdup(fileLine);
            strsep(&searchTermLine, " ");    // Removes search term leaving url list
            strsep(&searchTermLine, " ");    // Skip the second space
            break;
        }
    }
    
    // Search term doesn't appear in collection
    if (searchTermLine == NULL)
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
    // extract the last url //FIXME can make more efficient?
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
    printf("Inserting: %s\n", url->URL);
    URL curr = listHead, prev = NULL;
    
    // empty url list
    if (listHead == NULL) {
        return url;
    }
    
    // get to the nodes with the same countTerms as url
    while (curr != NULL && curr->countTerms > url->countTerms) {
        prev = curr;
        curr = curr->next;
    }
    // get to the right pageWeight position
    while (curr != NULL && curr->countTerms == url->countTerms && curr->tfidf > url->tfidf) {
        prev = curr;
        curr = curr->next;
    }
    
    //FIXME the condition is curr->next != NULL because i cbf having a "prev" pointer, just in case the url needs to be added at te end
    //FIXME Check if these are all the cases
    if (curr == NULL) {
        prev->next = url;
        url->prev = prev;
    }else{ // put url before curr
        if (curr->prev != NULL) {
            curr->prev->next = url;
        }
        url->prev = curr->prev;
        curr->prev = url;
        url->next = curr;
    }
    
    if (url->prev == NULL)
        return url;
    else
        return listHead;
}

// Deletes old url and inserts new url into correct position
URL sortList(URL listHead, URL url) {
    listHead = deleteURL(listHead, url);
    listHead = insertURL(listHead, url);

    return listHead;
}

// delete a url from the URLList
URL deleteURL(URL listHead, URL url){
    if (listHead == url) {
        if (url->next != NULL) 
            url->next->prev = NULL;
        return url->next;
    }
    else {
        // Change next only if node to be deleted is NOT the last node 
        if(url->next != NULL) 
          url->next->prev = url->prev; 
      
        // Change prev only if node to be deleted is NOT the first node 
        if(url->prev != NULL) 
            url->prev->next = url->next;   
    }
    return listHead;
}

// calculate the term frequency of a term within a page, proportionate to the number of words
double termFrequency(char *term, char *url) {
    // open the url file
    char *fileName = strdup(url);
    fileName = realloc(fileName, strlen(url) + strlen(".txt") + 1);
    strcat(fileName, ".txt");  
    FILE *page = fopen(fileName, "r");

    double count = 0.0, words, termFreq;
    fscanf(page, "%*[^\n]%*[^#]#%*[^#]#%*[^\n]\n"); // skip to section 2 // skip to section 2

    char word[BUFSIZ];
    fscanf(page, " %s", word);
        
    // loop through words to find term frequency
    for (words = 0.0; strcmp(word, "#end") != 0; words++) {
        // normalise the word
        lowercase(word);
        strcpy(word,removePunctuation(word));
        
        if (strcmp(term,word) == 0)
            count++;
        fscanf(page, " %s", word);
    }
    
    termFreq = count/words;
    return termFreq;
}

// calculate inverse document frequency
double inverseDocumentFrequency(double containingDocs, double nDocs) {
    double quotient = nDocs/containingDocs;
    double inverseDocFreq = log(quotient);
    return inverseDocFreq;
}

void showURLList(URL listHead) {
    printf("\n========\n");
    URL curr = listHead;
    int i = 0;
    while(curr != NULL && i < 30) {
        printf("%s %d %lf\n", curr->URL, curr->countTerms, curr->tfidf);
        curr = curr->next;
        i++;
    }
}

// from https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
// make a word lowercase
void lowercase(char *word) {
    for ( ; *word; ++word) *word = tolower(*word);
}

// remove trailing punctuation
char *removePunctuation(char *string) { //FIXME is there a better way? edit string directly
    char *str = strdup(string);
    if (string[strlen(string)-1] == '.' || string[strlen(string)-1] == ',' || string[strlen(string)-1] == ';' || string[strlen(string)-1] == '?') {
        str[strlen(str)-1] = '\0';
    } 
    return str;  
}

// get the number of documents in collection.txt
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



