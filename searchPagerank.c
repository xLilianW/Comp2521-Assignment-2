#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct listNode *URL;

struct listNode {
    char *URL;
    double pageWeight;
    int countTerms;
    URL prev, next;
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

int main(int argc, char *argv[]){
    URL URLList = NULL;
    
    // Make list of URLs based on number of search terms in each URL
    int i;
    for(i = 1; i < argc; i++){
        URLList = updateURLList(URLList, argv[i]);
    }
    
    // Print the results 
    showURLList(URLList);
    
}

URL newURLNode(char *url) {
    URL new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->pageWeight = getPageWeight(url);
    new->countTerms = 1;
    new->prev = new->next = NULL;
    return new;
}

// Makes list of URLs if they contain search term
// Places URLs with more search terms closer to start
// Places URLs with higher pageWeight closer to start
URL updateURLList(URL listHead, char *searchTerm){
    // collect list of URLs containing the search term
    char *URLArray[BUFSIZ];
    int nURLs = sTermURLs(searchTerm, URLArray);

    URL url = NULL;
    URL curr = listHead;    
    int i = 0;
    
    // insert the first url into the list
    if (listHead == NULL && nURLs > 0) {
        url = newURLNode(URLArray[i]);
        listHead = url;
        i++;
    }
    
    // make changes to the URLList according to the URLs containing the search term
    while(i < nURLs){
        if((url = URLInList(listHead, URLArray[i])) != NULL){ // updates existing node position
            url->countTerms++;
            listHead = sortList(listHead, url); //position url on countTerms and pageweight
        }else{    // Adds new URL to list
            url = newURLNode(URLArray[i]);
            listHead = insertURL(listHead, url); //position url on countTerms and pageweight
        }
        printf("%s\n", URLArray[i]);
        showURLList(listHead);
        i++;
    }

    return listHead;
}

// Returns array of URLs matching search term
int sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]){
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUFSIZ], *searchTermLine;
    
    // Loops through entire file and finds search term
    while(fgets(fileLine, BUFSIZ, invertedIndex) != NULL){
        if(strstr(fileLine, searchTerm) != NULL){
            searchTermLine = strdup(fileLine);
            strsep(&searchTermLine, " ");    // Removes search term leaving url list
            strsep(&searchTermLine, " ");    // Skip the second space
            break;
        }
    }
    
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
    URL curr = listHead;
    
    // empty url list
    if (listHead == NULL) {
        return url;
    }
    
    // get to the nodes with the same countTerms as url
    while (curr->next != NULL && curr->countTerms > url->countTerms) {
        curr = curr->next;
    }
    // get to the right pageWeight position
    while (curr->next != NULL && curr->countTerms == url->countTerms && curr->pageWeight > url->pageWeight) {
        curr = curr->next;
    }
    
    //FIXME the condition is curr->next != NULL because i cbf having a "prev" pointer, just in case the url needs to be added at te end
    //FIXME Check if these are all the cases
    if (curr->next == NULL && curr->countTerms == url->countTerms && curr->pageWeight > url->pageWeight){ // append url
        curr->next = url;
        url->prev = curr;
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

// get the pageweight of a url
double getPageWeight(char *url) {
    double pageWeight;
    FILE *file = fopen("pagerankList.txt", "r");
    char fileLine[BUFSIZ];
    
    // find the line regarding the url in the file
    while (fgets(fileLine, BUFSIZ, file) != NULL) {
        if (strstr(fileLine, url) != NULL)
            break;
    }
    fclose(file);
    
    // scan in the pageweight
    sscanf(fileLine, "%*s %*d, %lf\n", &pageWeight);
    
    return pageWeight;
}

void showURLList(URL listHead) {
    printf("\n========\n");
    URL curr = listHead;
    while(curr != NULL) {
        printf("%s %d %lf\n", curr->URL, curr->countTerms, curr->pageWeight);
        curr = curr->next;
    }
}

