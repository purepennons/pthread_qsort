//
//  FileAPI.c
//  pthread_qsort
//
//  Created by PureWind on 2014/5/11.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "FileAPI.h"

enum {LINE_CNT = 150, BUF_SIZE = 20};


int writeFile(char* filename, int* intArray, int arrayLength){
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Can not open %s.\n", filename);
        return 1;
    }
    int i;
    for (i=0; i<arrayLength; i++) {
        fprintf(fp, "%d\n", intArray[i]);
    }
    fclose(fp);
    printf("Write data to %s, success.\n", filename);
    return 0;
}

int writeFileByOutputAttribute(char* filename, void *output){
    FILE *fp;
    struct outputAttribute *outputStruct;
    outputStruct = (struct outputAttribute *)output;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Can not open %s.\n", filename);
        return 1;
    }
    int i, j;
    for (i=0; i<outputStruct->numOfArray; i++) {
        if (i!=0) {
            for (j=0; j<outputStruct->arrayLength[i]; j++) {
                fprintf(fp, "%d\n", outputStruct->outputArray[i][j]);
            }
        }else{
            for (j=outputStruct->numOfArray - (outputStruct->numOfNumbers%outputStruct->numOfArray); j<outputStruct->arrayLength[i]; j++) {
                fprintf(fp, "%d\n", outputStruct->outputArray[i][j]);
            }
        }
    }
    fclose(fp);
    printf("Write data to %s, success.\n", filename);
    return 0;
}


int* readIntFromFileByLine(char* filename, int numOfLines){
    FILE *fp;
    int i;
    int *numArray;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Can not open %s.\n", filename);
        return NULL;
    }
    numArray = (int*)malloc(sizeof(int)*numOfLines);
    if (numArray == NULL) {
        printf("Error: Fail to malloc memory.");
        return NULL;
    }

    for (i=0; i<numOfLines; i++) {
        read = getline(&line, &len, fp);
        numArray[i] = atoi(line);
    }
    return numArray;
}

int getNumOfLinesInFile(char* filename){
    FILE *fp;
    int numOfLines = 0;
    char ch;
    char buf[BUF_SIZE+1] ;
    char * ptr;
    size_t read_bytes;
    
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Can not open %s.\n", filename);
        return 1;
    }
    //slow way
//    do{
//        ch = fgetc(fp);
//        if (ch == '\n') {
//            numOfLines++;
//        }
//    }while(ch != EOF);
//    if ((ch != '\n') && (numOfLines != 0)) {
//        numOfLines++;
//    }
    
    //fast way
    while((read_bytes = fread(buf, 1, BUF_SIZE, fp))) { // read_bytes==0 時結束
        buf[read_bytes] = '\0';
        ptr = (char*)strchr(buf, '\n');
        while(ptr!=NULL) {
            numOfLines++;
            ptr = (char*)strchr(ptr+1, '\n');
        }
    }
    fclose(fp);
    return numOfLines+1;
}



