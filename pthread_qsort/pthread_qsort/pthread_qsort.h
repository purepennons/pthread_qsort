//
//  pthread_qsort.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/14.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//
#ifndef _pthread_qsort
    #define _pthread_qsort
        extern int compare (const void * a, const void * b);
        extern void *singleThreadQuicksort(void *p);
        extern struct outputAttribute  pthread_qsort(void *p);
        extern void changeArray(void *p1, void *p2);
#endif
