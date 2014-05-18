#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Struct.h"
#include "FileAPI.h"
#include "OtherAPI.h"
#include "pthread_qsort.h"

#define INPUT_FILE "input.txt"
#define NUM_OF_THREADS 8

int main(int argc, char *argv[]) {
    struct InputAttribute inputStruct = getInputAttribute(INPUT_FILE, NUM_OF_THREADS);
    struct outputAttribute outputStruct =  pthread_qsort((void *)&inputStruct);
    int flag =  writeFileByOutputAttribute("sort.txt", (void *)&outputStruct);
    pthread_exit(NULL);
}