

struct listNode {
    char *URL;
    double pageWeight;
    SearchTerm next;
} listNode;

// graph representation 
typedef struct GraphRep {
	int    nV;          // #URLs
	SearchTerm  *SearchList; // list representation of outgoing links
} GraphRep;

typedef struct GraphRep *Graph;
typedef struct listNode *SearchTerm;

void main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: searchPagerank ---search_terms---\n");
    }
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    FILE *pagerankList = fopen("pagerankList.txt", "r");
    
    int i = 0;
    for(i = 0; i < argc - 1; i++){    // Create list of URLs matching each search term
        g->nV++;
        SearchTerm searchList = makeURLList(invertedIndex, g->SearchList[i], argv[i]);
    }
    
    
    fclose("invertedIndex.txt");
    fclose("pagerankList.txt");
}

SearchTerm makeURLList(FILE *invertedIndex, SearchTerm s, char *sTerm){
    char *searchTerm;
    char *urlList;
    
    // Loops through entire file and finds URLs containing search term
    fscanf(invertedIndex, "%s  %s", searchTerm, urlList);
    while((invertedIndex != EOF) && (strcmp(searchTerm, sTerm) != 0)){    
        //need to find out how to store all urls and 
        //maintain how many search terms appear for each url
        fscanf(invertedIndex, "%s  %s", searchTerm, urlList);        
    }
    
    // Extract each URL and place into linked list
    while(urlList != NULL){    
        s->URL = strdup(strtok(urlList, " "));
        //include page weight?
        s = s->next;
    }
}
