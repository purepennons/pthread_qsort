//
//  OtherAPI.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/13.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

int** createIntMatrix(int m, int n);
int** splitArrayToMatrix(int* inputArray, int length, int numOfArray, int splitArrayLength);
struct InputAttribute getInputAttribute(char *filename, int numOfThreads);

int** createIntMatrix(int m, int n){
    int **tempMatrix;
    int *pData;
    int a;
    tempMatrix = (int**)malloc(m*sizeof(int*)+m*n*sizeof(int));
    for (a=0, pData=(int*)(tempMatrix+m); a<m;a++, pData+=n) {
        tempMatrix[a] = pData;
    }
    if (tempMatrix == NULL) {
        printf("Error: Fail to malloc memory.");
    }
    return tempMatrix;
}

int** splitArrayToMatrix(int* inputArray, int length, int numOfArray, int splitArrayLength){
    int **splitMatrix = createIntMatrix(numOfArray, splitArrayLength);
    int i, j;
    for (i=0; i<numOfArray; i++) {
        for (j=0; j<splitArrayLength; j++) {
            if ((i==(numOfArray-1)) && (i*splitArrayLength+j)>(length-2)) {
                break;
            }
                splitMatrix[i][j] = inputArray[i*splitArrayLength+j];
        }
    }
    return splitMatrix;
}

struct InputAttribute getInputAttribute(char *filename, int numOfThreads){
    struct InputAttribute attStruct;
    attStruct.numOfThreads = numOfThreads;
    attStruct.numOfNumbers = getNumOfLinesInFile(filename);
    attStruct.numArray = readIntFromFileByLine(filename, attStruct.numOfNumbers);
    attStruct.tempLength = (int)(attStruct.numOfNumbers/attStruct.numOfThreads)+(attStruct.numOfNumbers%attStruct.numOfThreads);
    attStruct.tempArray = splitArrayToMatrix(attStruct.numArray, attStruct.numOfNumbers, attStruct.numOfThreads, attStruct.tempLength);
    return attStruct;
}
