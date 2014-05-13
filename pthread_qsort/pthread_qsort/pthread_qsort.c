//
//  pthread_qsort.c
//  pthread_qsort
//
//  Created by PureWind on 2014/5/11.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//


#define NUM_OF_THREADS 4
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
void pthread_qsort(){
    struct ThreadArguments thArg[NUM_OF_THREADS];
    int *taskids[NUM_OF_THREADS];
    int rc, t;
    for (t=0; t<NUM_OF_THREADS; t++) {
        thArg[t].threadId = t;
    }

}


