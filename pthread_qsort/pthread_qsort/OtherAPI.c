//
//  OtherAPI.c
//  pthread_qsort
//
//  Created by PureWind on 2014/5/13.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Struct.h"
#include "FileAPI.h"
#include "OtherAPI.h"

int getRandomNum(int min, int max){
    int randomNum;
    srand(time(NULL));
    randomNum = (rand()%(max-min+1));
    return randomNum;
}

void swap(int *x, int *y) {
    if (x != y) {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

int* createArray(int m, int initalValue){
    int *array;
    int i;
    array = (int*)malloc(m*sizeof(int));
    if (array == NULL) {
        printf("Error: Fail to malloc memory.");
    }
    for (i=0; i<m; i++) {
        array[i] = initalValue;
    }
    return array;
}

int** createIntMatrix(int m, int n){
    int **tempMatrix;
    int *pData;
    int a, i, j;
    tempMatrix = (int**)malloc(m*sizeof(int*)+m*n*sizeof(int));
    for (a=0, pData=(int*)(tempMatrix+m); a<m;a++, pData+=n) {
        tempMatrix[a] = pData;
    }
    if (tempMatrix == NULL) {
        printf("Error: Fail to malloc memory.");
    }
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            tempMatrix[i][j] = -1;
        }
    }
    return tempMatrix;
}

int** splitArrayToMatrix(int* inputArray, int length, int numOfArray, int splitArrayLength){
    int **splitMatrix = createIntMatrix(numOfArray, splitArrayLength);
    int i, j;
    for (i=0; i<numOfArray; i++) {
        for (j=0; j<splitArrayLength; j++) {
            if ((i==(numOfArray-1)) && (i*splitArrayLength+j)>(length-1)) {
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
    //Length of splitArray = (arrayLength + (n-(arrayLength%n)))/n, if arrayLength%n != 0, else Length of splitArray = arrayLength/n
    attStruct.tempLength = (attStruct.numOfNumbers%attStruct.numOfThreads==0)? (int)(attStruct.numOfNumbers/attStruct.numOfThreads):(int)((attStruct.numOfNumbers+ (attStruct.numOfThreads - (attStruct.numOfNumbers%attStruct.numOfThreads)))/attStruct.numOfThreads);
    attStruct.tempArray = splitArrayToMatrix(attStruct.numArray, attStruct.numOfNumbers, attStruct.numOfThreads, attStruct.tempLength);
    return attStruct;
}

int divideWithPivot(int pivot, int *unDivideArray, int length){
    int index=0;
    int i;
    for (i=index; i<length; i++) {
        if (unDivideArray[i] <= pivot) {
            swap(&unDivideArray[index], &unDivideArray[i]);
            index++;
        }
    }
    return index;
}

int* cascadeArray(int *array1, int from1, int to1, int *array2, int from2, int to2){
    int *tempArray = createArray((to1-from1+1)+(to2-from2+1), 0);
    int i, j;
    for (i=0;i<(to1-from1+1); i++) {
        tempArray[i] = array1[from1+i];
    }
    for (j=(to1-from1+1); j<(to1-from1+1)+(to2-from2+1); j++) {
        tempArray[j] = array2[from2+j -(to1-from1+1)];
    }
    return tempArray;
}

int* waitArray(int numOfThreads, int hierarchy){
    int totalCondWait = numOfThreads/2;
    int padding = hierarchy/2;
    int numOfCluster = totalCondWait/padding;
    int *condArray = (int*)malloc(sizeof(int)*totalCondWait);

    int i, j=1;
    condArray[0] = 0;
    for (i=1; i<totalCondWait; i++) {
        if (j<padding) {
            condArray[i] = condArray[i-1] + 1;
            j++;
        }else{
            condArray[i] = condArray[i-padding] + hierarchy;
            j=1;
        }
    }
    return condArray;
}

int isExistInArray(int *array, int length, int search){
    int low = 0;
    int high = length-1;
    int middle;
    while (low <= high) {
        middle = (low+high)/2;
        if (array[middle] == search) {
            return 1;
        }else if(array[middle] > search){
            high = middle -1;
        }else if(array[middle] < search){
            low = middle + 1;
        }
    }
    return 0;
}
