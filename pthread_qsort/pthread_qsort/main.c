#include <stdio.h>
#include <stdlib.h>
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
        printf("argv[0] = 執行檔, argv[1] = thread 數量, argv[2] = input檔名, argv[3] = output檔名\n");
        printf("\n");
        printf("thread數量需為2的倍數.\n");
        printf("\n");
        printf("EX: ./exe 4 input.txt output.txt\n");
        exit(-1);
    }
    
    //qsort main function
    struct InputAttribute inputStruct = getInputAttribute(argv[2], atoi(argv[1]));
    struct outputAttribute outputStruct =  pthread_qsort((void *)&inputStruct);
    writeFileByOutputAttribute(argv[3], (void *)&outputStruct);
    pthread_exit(NULL);
}
