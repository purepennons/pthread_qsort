//
//  pthread_qsort.c
//  pthread_qsort
//
//  Created by PureWind on 2014/5/11.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthread_qsort.h"
#include "OtherAPI.h"
#include "Struct.h"

//qsort compare function
int compare(const void *a, const void *b)
{
    int c = *(int *)a;
    int d = *(int *)b;
    if(c < d) {return -1;}
    else if (c == d) {return 0;}
    else return 1;
}

void initThreadInputs(struct ThreadArguments thArg){
    
}

void *singleThreadQuicksort(void *p){
    struct ThreadArguments *singleThreadArg;
    singleThreadArg = (struct ThreadArguments *)p;
    pthread_exit(NULL);
}

void pthread_qsort(void *p){
    struct InputAttribute *inputStruct;
    struct ThreadArguments *thArg;
    pthread_t threads[inputStruct->numOfThreads];
    int rc, t;
    inputStruct = (struct InputAttribute *)p;
    thArg = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments)*(inputStruct->numOfThreads));
    printf("thread = %d\n", inputStruct->numOfThreads);
    printf("num = %d\n", inputStruct->numOfNumbers);
    for (t=0; t<(inputStruct->numOfThreads); t++) {
        thArg[t].threadId = t;
        thArg[t].pivot = inputStruct->tempArray[0][getRandomNum(0, inputStruct->tempLength)];
        thArg[t].splitArrayLength = inputStruct->tempLength;
        thArg[t].splitArray = inputStruct->tempArray[t];
        printf("s: %d", thArg[t].splitArrayLength);
    }
//    rc = pthread_create(&threads[t], NULL, singleThreadQuicksort, (void *) &thArg[t]);
    pthread_exit(NULL);
}



