//
//  OtherAPI.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/13.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#include <stdio.h>

int** createIntMatrix(int m, int n);

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