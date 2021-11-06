#include "system_init.h"
#include <stdio.h>
#include <stdlib.h>

int init(unsigned char** pmem, unsigned int * r, unsigned int * psw, char* file_name) {
    // Allocate memory
    *pmem = (unsigned char*)calloc(1<<16, sizeof(unsigned char));
    unsigned char* mem = *pmem;
    if(!mem) {
        printf("Error while allocating memory!");
        return -2;
    }

    // Open the file
    FILE* fi = fopen(file_name, "r");

    if(!fi) {
        printf("Error while openning the input file!");
        return -3;
    }

    // Read the file
    unsigned int address;
    unsigned int data[8];
    int count = 0;
    while(
        (count = fscanf(fi, "%x: %x %x %x %x %x %x %x %x\n", &address, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]))
        > 0) {
        /*
        // Print test
        printf("%x:", address);
        for(int i = 0; i < count - 1; i++) {
            printf(" %x", data[i]);
        }
        printf("\n");*/
        for(int i = 0; i < count - 1; i++) {
            mem[address + i] = data[i];
        }
    }

    fclose(fi);

    for (int i = 0; i < 8; i++)
    {
        r[i] = 0;
    }

    *psw = 0;
    
    return 0;
}