

void main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: searchPagerank ---search_terms---\n");
    }
    FILE *invertedIndex = fopen("invertedIndex.txt", "r");
    FILE *pagerankList = fopen("pagerankList.txt", "r");
    
    char *searchTerm;
    char *urlList;
    fscanf(invertedIndex, "%s %s", searchTerm, urlList);
    while(invertedIndex != EOF){    // Loops through entire file
        //need to find out how to store all urls and 
        //maintain how many search terms appear for each url
        
        fscanf(invertedIndex, "%s %s", searchTerm, urlList);        
    }
    
    fclose("invertedIndex.txt");
    fclose("pagerankList.txt");
}
