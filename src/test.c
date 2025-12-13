#include "../include/gauss.h"
#include "../include/backsubst.h"
#include "../include/mat_io.h"

#include <stdio.h>

typedef struct {
    int eliminate;
    int backsubst; 
} ExpectedResults;

void readExpectedResults(char* file_name, ExpectedResults *results) {
    FILE * fin =  fopen(file_name,"r");
    
    fscanf(fin,"%d %d",&results->eliminate, &results->backsubst);
    fclose(fin);
}


int main(int argc, char** args) {
    if (argc != 5) {
        return 1;
    }


    Matrix *A = readFromFile(args[2]);
    Matrix *b = readFromFile(args[3]);
    ExpectedResults results;
    readExpectedResults(args[4], &results);
    
    int eliminateVal = eliminate(A, b);

    Matrix *x = createMatrix(b->r, 1);
    int backsubstVal = -1;

    if (x != NULL) {
        backsubstVal = backsubst(x,A,b);
        freeMatrix(x);
    }
    
    printf("[TEST %s] %s\n", args[1], results.eliminate == eliminateVal && results.backsubst == backsubstVal ? "PASSED" : "FAILED");
    if (results.eliminate != eliminateVal) {
        printf("Expected %d instead of %d in eliminate function result\n", results.eliminate, eliminateVal);
    }

    if (results.backsubst != backsubstVal) {
        printf("Expected %d instead of %d in backsubst function result\n", results.backsubst, backsubstVal);
    }

    freeMatrix(A);
    freeMatrix(b);

    return 0;
}
