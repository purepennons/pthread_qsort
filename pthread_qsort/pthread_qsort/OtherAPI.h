//
//  OtherAPI.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/14.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#ifndef _OtherAPI
    #define _OtherAPI
        extern int getRandomNum(int min, int max);
        extern void swap(int *x, int *y);
        extern int* createArray(int m, int initalValue);
        extern int** createIntMatrix(int m, int n);
        extern int** splitArrayToMatrix(int* inputArray, int length, int numOfArray, int splitArrayLength);
        extern struct InputAttribute getInputAttribute(char *filename, int numOfThreads);
        extern int divideWithPivot(int pivot, int *unDivideArray, int length);
        extern int* cascadeArray(int *array1, int from1, int to1, int *array2, int from2, int to2);
        extern int* waitArray(int numOfThreads, int hierarchy);
        extern int isExistInArray(int *array, int length, int search);
#endif
