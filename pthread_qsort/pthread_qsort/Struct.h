//
//  ThreadStruct.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/13.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

struct ThreadArguments{
    int threadId;
    int splitArrayLength;
    int *splitArray;
};

struct InputAttribute{
    int numOfThreads;
    int numOfNumbers;
    int tempLength;
    int *numArray;
    int **tempArray;
};