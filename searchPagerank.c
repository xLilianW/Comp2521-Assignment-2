
#define TRUE    1
#define FALSE   0

struct listNode {
    char *URL;
    double pageWeight;
    int countTerms;
    URL next;
} listNode;

// graph representation 
typedef struct GraphRep {
	int    nV;          // #URLs (maybe not necessary)
	URL  SearchList; // list representation of outgoing links
} GraphRep;

typedef struct GraphRep *Graph;
typedef struct listNode *URL;

void main(int argc, char *argv[]){
    URL URLList;
    
    // Make list of URLs based on number of search terms in each URL
    int i;
    for(i = 0; i < argc - 1; i++){
        URLList = makeURLList(URLList, argv[i]);
    }
    
}

// Makes list of URLs if they contain search term
// Places URLs with more search terms closer to start
// Places URLs with higher pageWeight closer to start
URL makeURLList(URL list, char *searchTerm){
    URL *URLArray = sTermURLs(searchTerm);
    
    //check if list is empty
    URL start = list;
    URL curr = list;    //should be last node of list
    
    int i = 0;
    while(URLArray[i] != NULL){
        if(URLInList(list, URLArray[i])){   // Moves existing URL to front of list
            //move to front, removing duplicate
            //move should account for pageweight too
            
            URLArray[i]->countTerms++;
        }else{    // Adds new URL to end of list //TODO include pageWeight
            URLArray[i]->countTerms = 1;
            curr->next = URLArray[i];
            curr = curr->next;
        }
    }
    return start;
}

// Returns array of URLs matching search term
char *sTermURLs(char *searchTerm){
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    char fileLine[BUF_SIZ];
    
    // Loops through entire file and finds search term
    int found = FALSE;
    while(fgets(fileLine, BUF_SIZ, invertedIndex) != NULL && found == FALSE){
        if(strstr(fileLine, searchTerm) != NULL){
            fileLine = strtok(fileLine, " ");    // Removes search term leaving url list
            found = TRUE;
        }
    }
    
    // Extract each URL matching search term and place into array
    char *urlToken = strtok(fileLine, " ");
    char **urlArray = malloc(strlen(urlToken));    //need calloc?
    int i = 0;
    while(urlToken != NULL){
        //need to resize array?
        urlArray[i] = strdup(urlToken);
        urlToken = strtok(fileLine, " ");
        i++;
    }
    
    fclose("invertedIndex.txt");
}

// Returns TRUE if url is in list
int URLInList(URL list, URL u){
    URL curr = list;
    while(curr != NULL){
        if(strcmp(curr->URL, u) == 0){
            return TRUE;
        }
        curr = curr->next;
    }
    return FALSE;
}

