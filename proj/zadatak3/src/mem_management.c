#include "mem_management.h"
#include "term.h"
#include "main.h"
#include "tim.h"

unsigned int mem_read(unsigned int addr) {
    if(addr == 0xff02) {
        return term_read();
    }
    if(addr == 0xff10) {
        return tim_read();
    }
    if(addr >= 0 && addr + 1 < (1 << 16)) {
        unsigned int high = mem[addr];
        unsigned int low = mem[addr + 1];

        return high << 8 | low;
    }
    return 0;
}

void mem_write(unsigned int addr, unsigned int i) {
    if(addr == 0xff00) {
        term_write(i);
        return;
    }
    if(addr == 0xff10) {
        tim_write(i);
        return;
    }
    if(addr >= 0 && addr + 1 < (1 << 16)) {
        mem[addr] = i >> 8;
        mem[addr + 1] = i & 0xff;
    }
}

void mem_stack_push(unsigned int i) {
    SP--;
    SP--;
    mem_write(SP, i);
}

unsigned int mem_stack_pop() {
    unsigned int i = mem_read(SP);
    SP++;
    SP++;
    return i;
}

