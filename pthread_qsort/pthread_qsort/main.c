#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Struct.h"
#include "FileAPI.h"
#include "OtherAPI.h"
#include "pthread_qsort.h"

#define INPUT_FILE "123.txt"
#define NUM_OF_THREADS 4

//get input and inital matrix
//void init(){
//    int *numArray;
//    numOfNumbers = getNumOfLinesInFile(INPUT_FILE);
//    //flag = writeFile("123.txt", tempNum, (int)(sizeof(tempNum)/sizeof(int)));
//    numArray = readIntFromFileByLine(INPUT_FILE, numOfNumbers);
//    tempLength = (int)(numOfNumbers/NUM_OF_THREADS)+(numOfNumbers%NUM_OF_THREADS);
//    tempArray = createIntMatrix(NUM_OF_THREADS, tempLength);
//    //split input to thread
//    int i, j;
//    for (i=0; i<NUM_OF_THREADS; i++) {
//        for (j=0; j<tempLength; j++) {
//            if ((i==(NUM_OF_THREADS-1)) && (i*tempLength+j)>(numOfNumbers-2)) {
//                break;
//            }
//            tempArray[i][j] = numArray[i*tempLength+j];
//        }
//    }
//}



int main(int argc, char *argv[]) {
    struct InputAttribute inputStruct = getInputAttribute(INPUT_FILE, NUM_OF_THREADS);
    int testArray[] = {23, 435, 231, 41, 65, 23, 86, 45, 34, 543};
    int testArray2[] = {1, 32, 53, 453, 67};
    int *tempArray;
    pthread_qsort((void *)&inputStruct);
//    tempArray = cascadeArray(testArray, 1, 4, testArray2, 2, 3);
//    for (int i=0; i<10; i++) {
//        printf("%d, ", testArray[i]);
//    }
//    printf("\n");
//    for (int j=0; j<5; j++) {
//        printf("%d, ", testArray2[j]);
//    }
//    printf("\n");
//    for (int k=0; k<(3-0+1)+(3-0+1); k++) {
//        printf("%d, ",tempArray[k]);
//    }
    return 0;
}