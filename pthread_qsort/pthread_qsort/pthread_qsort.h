//
//  pthread_qsort.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/14.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#ifndef _OtherAPI
    #define _OtherAPI
        extern int compare(const void *a, const void *b);
        extern void pthread_qsort(struct InputAttribute inputStruct);
#endif
