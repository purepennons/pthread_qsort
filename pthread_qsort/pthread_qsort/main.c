#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "FileAPI.h"
#include "OtherAPI.h"
#include "pthread_qsort.h"

#define INPUT_FILE "input.txt"
#define NUM_OF_THREADS 4
void init();
int **tempArray = NULL;

//get input and inital matrix
void init(){
    int numOfNumbers;
    int *numArray;
    numOfNumbers = getNumOfLinesInFile(INPUT_FILE);
    //flag = writeFile("123.txt", tempNum, (int)(sizeof(tempNum)/sizeof(int)));
    numArray = readIntFromFileByLine(INPUT_FILE, numOfNumbers);
    int tempLength = (int)(numOfNumbers/NUM_OF_THREADS)+(numOfNumbers%NUM_OF_THREADS);
    tempArray = createIntMatrix(NUM_OF_THREADS, tempLength);
    //split input to thread
    int i, j;
    for (i=0; i<NUM_OF_THREADS; i++) {
        for (j=0; j<tempLength; j++) {
            if ((i==(NUM_OF_THREADS-1)) && (i*tempLength+j)>(numOfNumbers-2)) {
                break;
            }
            tempArray[i][j] = numArray[i*tempLength+j];
        }
    }
}

int main (int argc, char *argv[]) {
    init();
    return 0;
}