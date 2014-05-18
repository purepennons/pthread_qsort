#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Struct.h"
#include "FileAPI.h"
#include "OtherAPI.h"
#include "pthread_qsort.h"

#define INPUT_FILE "123.txt"
#define NUM_OF_THREADS 8

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
    int testArray[] = {567, 6583, 435, 5532, 634, 547, 643, 643, 346, 213, 5364, 453, 4356, 634};
    int testArray2[] = {1, 32, 53, 453, 67};
//    int i = divideWithPivot(634, testArray, 14);
//    printf("index = %d\n", i);
//    for (int i=0; i<14; i++) {
//        printf("%d, ", testArray[i]);
//    }
//    int *tempArray = waitArray(4, 2);
//    for (int i=0; i<2; i++) {
//        printf("%d, ", tempArray[i]);
//    }
//    printf("\n");
//    printf("isExist: %d\n",isExistInArray(tempArray, 4, 6));
    pthread_qsort((void *)&inputStruct);

    return 0;
}