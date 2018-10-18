

void main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: searchPagerank ---search_terms---\n");
    }
    
    int i = 0;
    for(i = 0; i < argc - 1; i++){    // Create list of URLs matching each search term
        g->nV++;
        g->SearchList[i] = makeURLList(g->SearchList[i], argv[i]);
    }
    
    
}
// Makes a linked list of URLs that contain search term
SearchTerm makeURLList(FILE *invertedIndex, SearchTerm s, char *sTerm){
    char *searchTerm;
    char *urlList;
    
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    FILE *pagerankList = fopen("pagerankList.txt", "r");
    
    // Loops through entire file and finds URLs containing search term
    fscanf(invertedIndex, "%s  %s", searchTerm, urlList);
    while((invertedIndex != EOF) && (strcmp(searchTerm, sTerm) != 0)){    
        //need to find out how to store all urls and 
        //maintain how many search terms appear for each url
        fscanf(invertedIndex, "%s  %s", searchTerm, urlList);        
    }
    SearchTerm start = s;
    
    // Extract each URL and place into linked list
    while(urlList != NULL){    
        s->URL = strdup(strtok(urlList, " "));
        //include page weight?
        s = s->next;
    }
    fclose("invertedIndex.txt");
    fclose("pagerankList.txt");
    return start;
}

int numTermsInURL (char *sTerm, char *URL){
    int countTerms = 0;
    int i = 0;
    while(SearchList[i] != NULL){
        SearchTerm curr = SearchList[i];
        while(curr != NULL){
            if(strcmp(curr->URL, URL) == 0){
                countTerms++;
            }
            curr = curr->next;
        }
    }
    return countTerms;
}
