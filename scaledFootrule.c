

int main(int argc, char *argv[]){
    List *tLists = getTLists(argc, argv);
    
    double totalDist = 0.0;
    //loop through lists calculating dist and sum them
    while(){
        totalDist += calculateSFDistance(tList, cList, p, findCardinality(tLists));
    }
    
}

double calculateSFDistance(list t, list c, int position, int k){
    int cardC = findCardinality(c);
    int cardT = findCardinality(t);
    int cPosition = positionInList(c, t);
    
    return fabs(cPosition/cardT - position/cardC);    //TODO typecast to double
}

int findCardinality(list){
    return cardinality;
}

int positionInList(int c, list){
    
    return position;
}

List *getTLists(){
    int i;
    for(i = 1; i < argc; i++){
        //put urls from argv[i] file into a list and add to array
    }
    return tLists;   
}
