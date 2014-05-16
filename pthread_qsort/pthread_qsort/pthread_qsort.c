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

int *checkSignal;
pthread_mutex_t changeMutex;
pthread_cond_t *changeCond;

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
    int trc;
    void * status;
    struct ThreadArguments *singleThreadArg;
    singleThreadArg = (struct ThreadArguments *)p;
    
    //parameters from singleThreadArg
    int numOfThreads = singleThreadArg->numOfThreads;
    int currentThreadId = singleThreadArg->threadId;
    int sisterThreadId = currentThreadId + (numOfThreads/2);
    int pivot = singleThreadArg->pivot;
    int *splitArrayLength = singleThreadArg->splitArrayLength;
    int *index = singleThreadArg->index;
    int **tempArray = singleThreadArg->tempArray;
    
    //doDivide with pivot
    singleThreadArg->index[currentThreadId] = divideWithPivot(pivot, tempArray[currentThreadId], splitArrayLength[currentThreadId]);
    
    //critical section
    pthread_mutex_lock(&changeMutex); //lock
    if (currentThreadId < (numOfThreads/2)) {
        while (!checkSignal[currentThreadId%(numOfThreads/2)]) {
            pthread_cond_wait(&changeCond[currentThreadId%(numOfThreads/2)], &changeMutex);
        }
        printf("cur = %d, sister = %d\n", currentThreadId, sisterThreadId);
        printf("curIndex = %d, sisterIndex = %d\n", index[sisterThreadId], index[currentThreadId]);
        //start to exchange array and update array length.
        int *temp = tempArray[currentThreadId];
        tempArray[currentThreadId] = cascadeArray(tempArray[sisterThreadId] ,index[sisterThreadId], splitArrayLength[sisterThreadId]-1, tempArray[currentThreadId], index[currentThreadId], splitArrayLength[currentThreadId]-1);
        splitArrayLength[currentThreadId] = ((splitArrayLength[sisterThreadId] - 1) - index[sisterThreadId] + 1) + ((splitArrayLength[currentThreadId]-1) - index[currentThreadId] + 1);
        tempArray[sisterThreadId] = cascadeArray(tempArray[sisterThreadId], 0, index[sisterThreadId]-1, temp, 0, index[currentThreadId]-1);
        splitArrayLength[sisterThreadId] = ((index[sisterThreadId]-1) - 0 + 1) + ((index[currentThreadId]-1)-0+1);
        
    }else{
        checkSignal[currentThreadId%(numOfThreads/2)] = 1;
        pthread_cond_signal(&changeCond[currentThreadId%(numOfThreads/2)]);
    }
    pthread_mutex_unlock(&changeMutex); //unlock
    //end of critical section
    
    
    pthread_exit((void *) (currentThreadId));
}

void pthread_qsort(void *p){
    struct InputAttribute *inputStruct;
    inputStruct = (struct InputAttribute *)p;
    
    //struct ThreadArguments thArg[inputStruct->numOfThreads];
    struct ThreadArguments *thArg;
    thArg = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments)*(inputStruct->numOfThreads));
    int indexArray[inputStruct->numOfThreads];
    int arrayLength[inputStruct->numOfThreads];
    
    //threads parameters
    pthread_t threads[inputStruct->numOfThreads];
    checkSignal = createArray((inputStruct->numOfThreads/2), 0);
    changeCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * (inputStruct->numOfThreads/2));
    pthread_attr_t attr;
    int rc, t;
    void *status;
    
    //Initialize parameters
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&changeMutex, NULL);
    
    printf("thread = %d\n", inputStruct->numOfThreads);
    printf("num = %d\n", inputStruct->numOfNumbers);
    
    //create threads
    for (t=0; t<(inputStruct->numOfThreads); t++) {
        pthread_cond_init (&changeCond[t], NULL);  //initialize pthread_cond_t
        
        arrayLength[t] = inputStruct->tempLength;
        thArg[t].threadId = t;
        thArg[t].pivot = inputStruct->tempArray[0][getRandomNum(0, inputStruct->tempLength)];
        //thArg[t].pivot = 453;
        thArg[t].index = indexArray;
        thArg[t].splitArrayLength = arrayLength;
        thArg[t].tempArray = inputStruct->tempArray;
        thArg[t].numOfThreads = inputStruct->numOfThreads;
        rc = pthread_create(&threads[t], &attr, singleThreadQuicksort, (void *) &thArg[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    //wait to complete.
    for (t=0; t<(inputStruct->numOfThreads); t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
    }
    printf("pivot = %d\n", thArg[0].pivot);
    for (int i=0; i<inputStruct->numOfThreads; i++) {
        printf("#%d  index = %d\n", i, thArg[i].index[i]);
        for (int j=0; j<thArg->splitArrayLength[i]; j++) {
            printf("%d, ", thArg[i].tempArray[i][j]);
        }
        printf("\n");
    }
    
    for (int i=0; i<4; i++) {
        printf("%d, ", thArg[0].splitArrayLength[i]);
    }
    
    //Clean up and exit.
    pthread_attr_destroy(&attr);

    pthread_exit(NULL);
}



