//
//  pthread_qsort.c
//  pthread_qsort
//
//  Created by PureWind on 2014/5/11.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#include <stdio>
#include <stdlib>
#include "pthread_qsort.h"
#include "Struct.h"

int compare(const void *a, const void *b);

//qsort compare function
int compare(const void *a, const void *b)
{
    int c = *(int *)a;
    int d = *(int *)b;
    if(c < d) {return -1;}
    else if (c == d) {return 0;}
    else return 1;
}

void initThreadInputs(struct InputAttribute inputStruct, struct ThreadArguments thArg){
    
}

void pthread_qsort(struct InputAttribute inputStruct){
    struct ThreadArguments thArg[inputStruct.numOfThreads];
    int *taskids[inputStruct.numOfThreads];
    int rc, t;
    for (t=0; t<inputStruct.numOfThreads; t++) {
        thArg[t].threadId = t;
        thArg[t].pivot = inputStruct.tempArray[0][getRandomNum(0, inputStruct.tempLength)];
        thArg[t].splitArrayLength = inputStruct.tempLength;
        thArg[t].splitArray = inputStruct.tempArray[t];
    }

}



