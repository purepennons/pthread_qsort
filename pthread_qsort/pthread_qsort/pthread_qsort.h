//
//  pthread_qsort.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/14.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//
#ifndef _pthread_qsort
    #define _pthread_qsort
        extern int compare(const void *a, const void *b);
        extern void *initThreadInputs();
        extern void *singleThreadQuicksort(void *p);
        extern void pthread_qsort(void *p);
#endif
