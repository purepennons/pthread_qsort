//
//  OtherAPI.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/14.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#ifndef _OtherAPI
    #define _OtherAPI
        extern int** createIntMatrix(int m, int n);
        extern int** splitArrayToMatrix(int* inputArray, int length, int numOfArray, int splitArrayLength);
        extern struct InputAttribute getInputAttribute(char *filename, int numOfThreads);
#endif
