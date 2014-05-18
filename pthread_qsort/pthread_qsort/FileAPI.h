//
//  FileAPI.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/14.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#ifndef _FileAPI
    #define _FileAPI
        extern int writeFile(char* filename, int* intArray, int arrayLength);
        extern int writeFileByOutputAttribute(char* filename, void *output);
        extern int* readIntFromFileByLine(char* filename, int numOfLines);
        extern int getNumOfLinesInFile(char* filename);
#endif
