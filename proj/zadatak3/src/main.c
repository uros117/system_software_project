#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "system_init.h"
#include "instruction_fetch.h"
#include "instruction_decode.h"
#include "instruction_execute.h"
#include "interrupt_handling.h"
#include "mem_management.h"
#include "term.h"
#include "tim.h"

unsigned int psw = 0;
unsigned char* mem = NULL;
unsigned int r[8] = {};
unsigned char instr[6] = {};
unsigned char oc = 0;
unsigned char mod = 0;
unsigned char rd = 0;
unsigned char rs = 0;
unsigned char up = 0;
unsigned char am = 0;
int start = 1;

int rb = 0;

int main(int argc, char* argv[]) {
    //printf("\033[1;33m""Emulator\n""\033[0m");
    int ec = 0;
    if(argc < 2) {
        printf("Missing argument: emulator <file_name>!");
        return -1;
    }
    
    if(ec = init(&mem, r, &psw, argv[1]) < 0) {
        printf("Init error!");
        return ec;
    }

    if(ec = tim_init() != 0) {
        printf("Timer init error!");
        return ec;
    }

    if(ec = term_init() != 0) {
        printf("Terminal init error!");
        return ec;
    }

    PC = mem_read(0);
    SP = 0xffff;

    while(start) {
        // Instruction fetch
        _if:switch(instr_fetch()) {
        case -1:
            // unsupported instruction
            signal_interrupt(INT_BADOC);
            goto _hi;
        case 1:
        case 2:
            goto _ie;
        case 3:
        case 5:
        default:
            break;
        }
        // Instruction decode
        _id: instr_decode();
        // Instruction execute
        _ie: instr_execute();
        if(oc == OC_IRET)
            continue;
        // Handle interrupts
        _hi: 
        term_loop();
        tim_loop();
        handle_interrupts();
    }
    
    term_deinit();
    tim_deinit();

    if(mem) 
        free(mem);
    return 0;
}