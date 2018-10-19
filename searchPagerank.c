
#define TRUE    1
#define FALSE   0

struct listNode {
    char *URL;
    double pageWeight;
    int countTerms;
    URL prev, next;
} listNode;

typedef struct listNode *URL;

URL newURLNode(char *url) {
    URL new = malloc(sizeof(listNode));
    assert(new != NULL);
    new->URL = strdup(url);
    new->countTerms = 1;
    new->prev = new->next = NULL;
    reaturn new;
}

void main(int argc, char *argv[]){
    URL URLList = NULL;
    
    // Make list of URLs based on number of search terms in each URL
    int i;
    for(i = 1; i < argc; i++){
        URLList = updateURLList(URLList, argv[i]);
    }
    
}

// Makes list of URLs if they contain search term
// Places URLs with more search terms closer to start
// Places URLs with higher pageWeight closer to start
URL updateURLList(URL listHead, char *searchTerm){
    // collect list of URLs containing the search term
    char *URLArray[BUFSIZ]
    int nURLs = sTermURLs(searchTerm, URLArray);

    URL url = NULL;
    URL curr = listHead;    
    int i = 0;
    
    // insert the first url into the list
    if (listHead == NULL && nURLS > 0) {
        url = newURLNode(URLArray[0]);
        listHead = url;
        i++;
    }
    
    // make changes to the URLList according to the URLs containing the search term
    while(i < nURLs){
        if((url = URLInList(listHead, URLArray[i])) != NULL){   // Moves existing URL to front of list
            url->countTerms++;
            listHead = sortList(listHead, url); //position url on countTerms and pageweight
        }else{    // Adds new URL to list //TODO include pageWeight
            url = newURLNode(URLArray[i]);
            listHead = insertURL(listHead, url); //position url on countTerms and pageweight
        }
        i++;
    }
    return listHead;
}

// Returns array of URLs matching search term
int *sTermURLs(char *searchTerm, char *urlArray[BUFSIZ]){
    char *searchTerm = "mars";
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUFSIZ], *searchTermLine;
    
    // Loops through entire file and finds search term
    while(fgets(fileLine, BUFSIZ, invertedIndex) != NULL){
        if(strstr(fileLine, searchTerm) != NULL){
            //TODO check if need to use strsep instead
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
    
    fclose(invertedIndex);
    return i;
}

// Returns TRUE if url is in list
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

//FIXME make this more efficient
// insert a URL into the URLList
URL insertURL(URL listHead, URL url) {
    URL curr = listHead;
    
    // get to the nodes with the same countTerms as url
    while (curr->next != NULL && curr->countTerms > url->countTerms) {
        curr = curr->next;
    }
    if (curr->next == NULL){ // all nodes have a higher countTerms than url
        curr->next = url; // append url at the end
    }else{ // insert based on pageweight
        while (curr->next != NULL && curr->countTerms == url->countTerms && curr->pageWeight > url->pageWeight) {
            curr = curr->next;
        }
        //the condition is curr->next != NULL because i cbf having a "prev" pointer, just in case the url needs to be added at te end
        if (curr->next == NULL){
            if (curr->countTerms == url->countTerms && curr->pageWeight > url->pageWeight){ // append url
                curr->next = url;
                url->prev = curr;
            }else{ // url goes before curr
                url->prev = curr->prev;
                curr->prev = url;
                url->next = curr;
            }
        }else{ // not at the end
            // put url before curr
            url->prev = curr->prev;
            curr->prev = url;
            url->next = curr;
        }
    }

    return listHead;
}

//TODO
URL sortList(URL listHead, URL url) {
    URL curr = listHead;
    
    // find the correct position for the url
    // connect url->prev to url->next
    // reposition url

    return listHead;
}


