//
//  FileAPI.h
//  pthread_qsort
//
//  Created by PureWind on 2014/5/11.
//  Copyright (c) 2014年 Chiahao Lin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int writeFile(char* filename, int* intArray, int arrayLength);
int* readIntFromFileByLine(char* filename, int numOfLines);
int getNumOfLinesInFile(char* filename);

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
    printf("write data to %s, success.\n", filename);
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
//    while ((read = getline(&line, &len, fp)) != -1) {
//        stringArray[i] = line;
//        printf("line = %s\n", line);
//        i++;
//    }
    return numArray;
}

int getNumOfLinesInFile(char* filename){
    FILE *fp;
    int numOfLines = 0;
    char ch;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Can not open %s.\n", filename);
        return 1;
    }
    do{
        ch = fgetc(fp);
        if (ch == '\n') {
            numOfLines++;
        }
    }while(ch != EOF);
    if ((ch != '\n') && (numOfLines != 0)) {
        numOfLines++;
    }
    fclose(fp);
    return numOfLines;
}


