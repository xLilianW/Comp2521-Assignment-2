char *collectData(void){
    FILE *collection = fopen("collection.txt", "r");
    char **urls;
    int i = 0;
    while (fscanf(text, " %s", url[i]) == 1) {
        printf("%s\n", url);
        //make empty graph
        //open file (add .txt)
        //update graph by adding node and outgoing links
        i++;
    }
}
