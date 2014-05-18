#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "Struct.h"
#include "FileAPI.h"
#include "OtherAPI.h"
#include "pthread_qsort.h"

//#define INPUT_FILE "input.txt"
//#define NUM_OF_THREADS 8

//argv[0] = 執行檔, argv[1] = thread 數量, argv[2] = input檔名, argv[3] = output檔名

int main(int argc, char *argv[]) {
    if (argc !=4 || atoi(argv[1])%2!=0) {
        printf("錯誤的參數格式.\n");
        printf("\n");
        printf("argc = 4\n");
        printf("\n");
        printf("argv[0] = 執行檔, argv[1] = thread 數量, argv[2] = input檔名, argv[3] = output檔名\n");
        printf("\n");
        printf("thread數量需為偶數.\n");
        printf("\n");
        printf("EX: ./exe 4 input.txt output.txt\n");
        exit(-1);
    }
    
    //time record parameters
    clock_t start, end;
    
    //start to record.
    start = clock();
    
    //qsort main function
    struct InputAttribute inputStruct = getInputAttribute(argv[2], atoi(argv[1]));
    struct outputAttribute outputStruct =  pthread_qsort((void *)&inputStruct);
//    for (int i =0; i<outputStruct.numOfArray; i++) {
//        for (int j=0; j<outputStruct.arrayLength[i]; j++) {
//            printf("%d\n",outputStruct.outputArray[i][j]);
//        }
//    }
    writeFileByOutputAttribute(argv[3], (void *)&outputStruct);
    
    //end to record.
    end = clock();
    
    double diff = end - start; // ms
    printf("總耗時： %f  sec\n", diff / CLOCKS_PER_SEC );

    
    pthread_exit(NULL);
}
