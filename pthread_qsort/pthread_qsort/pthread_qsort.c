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
#include <math.h>
#include "pthread_qsort.h"
#include "OtherAPI.h"
#include "Struct.h"

int *checkSignal;
pthread_mutex_t changeMutex;
pthread_cond_t *changeCond;
int* leaderThreadArray;  //決定一個thread是否進入交換迴圈中
//qsort compare function


//void *singleThreadQuicksort(void *p){
//    
//    struct ThreadArguments *singleThreadArg;
//    singleThreadArg = (struct ThreadArguments *)p;
//    
//    //parameters from singleThreadArg
//    int numOfThreads = singleThreadArg->numOfThreads;
//    int hierarchy = singleThreadArg->hierarchy;
//    int currentThreadId = singleThreadArg->threadId;
//    int *pivot = singleThreadArg->pivot;
//    int *splitArrayLength = singleThreadArg->splitArrayLength;
//    int *index = singleThreadArg->index;
//    int **tempArray = singleThreadArg->tempArray;
//    
//    //other parameters
//    int isLeaderThread = isExistInArray(leaderThreadArray, numOfThreads/2, currentThreadId);
//    int sisterThreadId = isLeaderThread ? currentThreadId + (hierarchy/2) : currentThreadId - (hierarchy/2);
//    printf("cur = %d, sis = %d\n", currentThreadId, sisterThreadId);
//    
//    if(hierarchy==1){
//        
//    }else{
//        //doDivide with pivot
//        singleThreadArg->index[currentThreadId] = divideWithPivot(pivot[currentThreadId], tempArray[currentThreadId], splitArrayLength[currentThreadId]);
////        if(currentThreadId == 3){
////            printf("before change %d\n", currentThreadId);
////            for (int i=0; i<splitArrayLength[currentThreadId]; i++) {
////                printf("%d, ", tempArray[currentThreadId][i]);
////            }
////        }
//        
//        //critical section
//        pthread_mutex_lock(&changeMutex); //lock
//        if (isLeaderThread) {
//            while (!checkSignal[sisterThreadId%(hierarchy/2)]) {
//                pthread_cond_wait(&changeCond[currentThreadId%(hierarchy/2)], &changeMutex);
//                //pthread_cond_wait
//            }
//            printf("cur = %d, sister = %d\n", currentThreadId, sisterThreadId);
//            printf("curIndex = %d, sisterIndex = %d\n", index[sisterThreadId], index[currentThreadId]);
//            //start to exchange array and update array length.
//            int *temp = tempArray[currentThreadId];
//            tempArray[currentThreadId] = cascadeArray(tempArray[sisterThreadId] ,index[sisterThreadId], splitArrayLength[sisterThreadId]-1, tempArray[currentThreadId], index[currentThreadId], splitArrayLength[currentThreadId]-1);
//            splitArrayLength[currentThreadId] = ((splitArrayLength[sisterThreadId] - 1) - index[sisterThreadId] + 1) + ((splitArrayLength[currentThreadId]-1) - index[currentThreadId] + 1);
//            tempArray[sisterThreadId] = cascadeArray(tempArray[sisterThreadId], 0, index[sisterThreadId]-1, temp, 0, index[currentThreadId]-1);
//            splitArrayLength[sisterThreadId] = ((index[sisterThreadId]-1) - 0 + 1) + ((index[currentThreadId]-1)-0+1);
//
//        }else{
//            checkSignal[currentThreadId%(hierarchy/2)] = 1;
//            pthread_cond_signal(&changeCond[sisterThreadId%(hierarchy/2)]);
//            
//        }
//        pthread_mutex_unlock(&changeMutex); //unlock
//        //end of critical section
//    }
//    
//    pthread_exit((void *) (currentThreadId));
//}

//void pthread_qsort(void *p){
//    struct InputAttribute *inputStruct;
//    inputStruct = (struct InputAttribute *)p;
//    
//    //struct ThreadArguments thArg[inputStruct->numOfThreads];
//    struct ThreadArguments *thArg;
//    thArg = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments)*(inputStruct->numOfThreads));
//    int indexArray[inputStruct->numOfThreads];
//    int arrayLength[inputStruct->numOfThreads];
//    int pivotArray[inputStruct->numOfThreads];
//    //int pivot = inputStruct->tempArray[0][getRandomNum(0, inputStruct->tempLength)];
//    int pivot = inputStruct->tempArray[0][0];
//    
//    //threads parameters
//    pthread_t threads[inputStruct->numOfThreads];
//    checkSignal = createArray((inputStruct->numOfThreads/2), 0);
//    changeCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * (inputStruct->numOfThreads/2));
//    pthread_attr_t attr;
//    int rc, t;
//    void *status;
//    
//    //Initialize parameters
//    pthread_attr_init(&attr);
//    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//    pthread_mutex_init(&changeMutex, NULL);
//    
//    printf("thread = %d\n", inputStruct->numOfThreads);
//    printf("num = %d\n", inputStruct->numOfNumbers);
//    
//    //create threads
//    for (t=0; t<(inputStruct->numOfThreads); t++) {
//        pthread_cond_init (&changeCond[t], NULL);  //initialize pthread_cond_t
//        
//        arrayLength[t] = inputStruct->tempLength;
//        pivotArray[t] = pivot;
//        
//        thArg[t].threadId = t;
//        thArg[t].pivot = pivotArray;
//        //thArg[t].pivot = 453;
//        thArg[t].index = indexArray;
//        thArg[t].splitArrayLength = arrayLength;
//        thArg[t].tempArray = inputStruct->tempArray;
//        thArg[t].numOfThreads = inputStruct->numOfThreads;
//        thArg[t].hierarchy = inputStruct->numOfThreads;
//    }
//    for (int i=0; i<(int)(log((double)inputStruct->numOfThreads)/log(2.0)); i++) {
//        leaderThreadArray = waitArray(thArg[0].numOfThreads, thArg[0].hierarchy);
//        for (int i=0; i<inputStruct->numOfThreads; i++) {
//            printf("pivot = %d\n", thArg[0].pivot[i]);
//            //printf("%d, ", thArg[0].splitArrayLength[i]);
//        }
//        printf("\n");
//        
//        for (t=0; t<(inputStruct->numOfThreads); t++) {
//            rc = pthread_create(&threads[t], &attr, singleThreadQuicksort, (void *) &thArg[t]);
//            if (rc) {
//                printf("ERROR; return code from pthread_create() is %d\n", rc);
//                exit(-1);
//            }
//        }
//        //wait to complete.
//        for (t=0; t<(inputStruct->numOfThreads); t++) {
//            rc = pthread_join(threads[t], &status);
//            if (rc) {
//                printf("ERROR; return code from pthread_join() is %d\n", rc);
//                exit(-1);
//            }
//            printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
//        }
//        for (t=0; t<(inputStruct->numOfThreads); t++) {
//            thArg[t].hierarchy = thArg[t].hierarchy/2;
//            if ((t%thArg[t].hierarchy)==0) {
//                //pivot = thArg[t].tempArray[t][getRandomNum(0, thArg[t].splitArrayLength[t])];
//                pivot =thArg[t].tempArray[t][0];
//            }
//            pivotArray[t] = pivot;
//        }
//        for (int i=0; i<inputStruct->numOfThreads; i++) {
//            printf("#%d  index = %d\n", i, thArg[i].index[i]);
//            for (int j=0; j<thArg->splitArrayLength[i]; j++) {
//                printf("%d, ", thArg[i].tempArray[i][j]);
//            }
//            printf("\n");
//        }
//
//    }
//    
//    //Clean up and exit.
//    pthread_attr_destroy(&attr);
//    pthread_mutex_destroy(&changeMutex);
//    for (int t=0; t<inputStruct->numOfThreads/2; t++) {
//        pthread_cond_destroy(&changeCond[t]);
//    }
//    pthread_exit(NULL);
//}


void *singleThreadQuicksort(void *p){
    
    struct ThreadArguments *singleThreadArg;
    singleThreadArg = (struct ThreadArguments *)p;
    
    //parameters from singleThreadArg
    int numOfThreads = singleThreadArg->numOfThreads;
    int hierarchy = singleThreadArg->hierarchy;
    int currentThreadId = singleThreadArg->threadId;
    int pivot = singleThreadArg->pivot;
    int splitArrayLength = singleThreadArg->splitArrayLength;
    int *tempArray = singleThreadArg->tempArray;

    if(hierarchy==1){
        
    }else{
        //doDivide with pivot
        singleThreadArg->index = divideWithPivot(pivot, tempArray, splitArrayLength);
    }
    pthread_exit((void *) (currentThreadId));
}

void pthread_qsort(void *p){
    struct InputAttribute *inputStruct;
    inputStruct = (struct InputAttribute *)p;
    
    //struct ThreadArguments thArg[inputStruct->numOfThreads];
    struct ThreadArguments *thArg;
    thArg = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments)*(inputStruct->numOfThreads));
    
    //threads parameters
    pthread_t threads[inputStruct->numOfThreads];
    pthread_attr_t attr;
    int rc, i, t, pivot;
    void *status;
    
    //Initialize parameters
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //initialize parameters from threadArguments
    for (t=0; t<inputStruct->numOfThreads; t++) {
        thArg[t].threadId = t;
        //thArg[t].pivot = inputStruct->tempArray[0][getRandomNum(0, inputStruct->tempLength)];
        thArg[t].pivot = inputStruct->tempArray[0][0];
        thArg[t].splitArrayLength = inputStruct->tempLength;
        thArg[t].tempArray = inputStruct->tempArray[t];
        thArg[t].numOfThreads = inputStruct->numOfThreads;
        thArg[t].hierarchy = inputStruct->numOfThreads;
    }
    
    printf("thread = %d\n", inputStruct->numOfThreads);
    printf("num = %d\n", inputStruct->numOfNumbers);


    //create threads
    for (int i=0; i<=(int)(log((double)inputStruct->numOfThreads)/log(2.0)); i++){
        for (int i=0; i<inputStruct->numOfThreads; i++) {
            printf("pivot = %d\n", thArg[i].pivot);
            //printf("%d, ", thArg[0].splitArrayLength[i]);
        }
        
        for (t=0; t<(inputStruct->numOfThreads); t++) {
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
        
        changeArray((void *)&thArg[0], (void *)&thArg[1]);
        
        for (int i=0; i<inputStruct->numOfThreads; i++) {
            printf("#%d  index = %d\n", i, thArg[i].index);
            for (int j=0; j<thArg->splitArrayLength; j++) {
                printf("%d, ", thArg[i].tempArray[j]);
            }
            printf("\n");
        }
        
        for (t=0; t<(inputStruct->numOfThreads); t++) {
            if(thArg[t].hierarchy > 1){
                thArg[t].hierarchy = thArg[t].hierarchy/2;
            }
            if ((t%thArg[t].hierarchy)==0) {
                //pivot = thArg[t].tempArray[t][getRandomNum(0, thArg[t].splitArrayLength[t])];
                pivot =thArg[t].tempArray[0];
            }
            thArg[t].pivot = pivot;
        }



    }
    
    //Clean up and exit.
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}

void changeArray(void *p1, void *p2){
    struct ThreadArguments *currentStruct;
    struct ThreadArguments *sisterStruct;
    currentStruct = (struct ThreadArguments*)p1;
    sisterStruct = (struct ThreadArguments*)p2;
    int *temp = currentStruct->tempArray;
    currentStruct->tempArray = cascadeArray(sisterStruct->tempArray, sisterStruct->index, sisterStruct->splitArrayLength-1, currentStruct->tempArray, currentStruct->index, currentStruct->splitArrayLength-1);
   
    sisterStruct->tempArray = cascadeArray(sisterStruct->tempArray, 0, sisterStruct->index-1, temp, 0, currentStruct->index-1);
    sisterStruct->splitArrayLength = ((sisterStruct->index-1) - 0 + 1) + ((currentStruct->index-1)-0+1);

}



