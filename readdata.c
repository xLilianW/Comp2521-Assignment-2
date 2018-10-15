
    FILE *collection = fopen("collection.txt", "r");
    char url[50];
    while (fscanf(text, " %s", url) == 1) {
        printf("%s\n", url);

