#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "FileAPI.h"
#define NUM_THREADS 5
int main (int argc, char *argv[]) {
    int flag, numOfLines;
    int i;
    int *numArray;
    numOfLines = getNumOfLinesInFile("123.txt");
    //flag = writeFile("123.txt", tempNum, (int)(sizeof(tempNum)/sizeof(int)));
    numArray = readIntFromFileByLine("123.txt", numOfLines);
    for (i=0; i<numOfLines; i++) {
        printf("%d\n", numArray[i]);
    }
    return 0;
}
