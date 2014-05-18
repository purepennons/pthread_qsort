//
//  ThreadStruct.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/13.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//
#include <pthread.h>

//struct ThreadArguments{
//    int threadId;
//    int *pivot;
//    int *index;
//    int *splitArrayLength;
//    int **tempArray;
//    int numOfThreads;
//    int hierarchy;
//};

struct InputAttribute{
    int numOfThreads;
    int numOfNumbers;
    int tempLength;
    int *numArray;
    int **tempArray;
};

struct ThreadArguments{
    int threadId;
    int pivot;
    int index;
    int splitArrayLength;
    int *tempArray;
    int numOfThreads;
    int hierarchy;
};

struct outputAttribute{
    int numOfNumbers;
    int numOfArray;
    int *arrayLength;
    int **outputArray;
};