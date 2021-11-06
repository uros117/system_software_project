#include <stdlib.h>
#include "main.h"
#include "stdint.h"
#include "instruction_execute.h"
#include "interrupt_handling.h"
#include "mem_management.h"
#include "instruction_execute.h"

void halt() {
    start = 0;
}

void intr() {
    signal_interrupt(r[rd] % 8);
}

void iret() {
    unsigned int temp = mem_stack_pop();
    PSW = temp;
    temp = mem_stack_pop();
    PC = temp;
    //PSW_RESET(PSW_I);
}

void call() {
    mem_stack_push(PC);
    PC = rb;
}

void ret() {
    PC = mem_stack_pop();
}

void jump() {
    int value = 0;
    switch (mod)
    {
    case 0x0:
        value = 1;
        break;
    case 0x1:
        value = PSW_READ(PSW_Z);
        break;
    case 0x2:
        value = !PSW_READ(PSW_Z);
        break;
    case 0x3:
        value = !PSW_READ(PSW_N);
    default:
        break;
    }

    if(value) {
        PC = rb;
    }
}

void xchg() {
    unsigned int temp = r[rs];
    r[rs] = r[rd];
    r[rd] = temp;
}

void aritm() {
    int16_t a = (int16_t)r[rd];
    int16_t b = (int16_t)r[rs];
    int al = r[rd];
    int bl = r[rs];

    int16_t temp;
    int templ;
    switch(mod) {
    case 0x0:
        r[rd] = a + b;
        break;
    case 0x1:
        r[rd] = a - b;
        break;
    case 0x2:
        r[rd] = a * b;
    case 0x3:
        r[rd] = a / b;
    case 0x4:
        temp = a - b;
        templ = al - bl;
        PSW_WRITE(PSW_C, (templ & ( 1 << 15 )));
        PSW_WRITE(PSW_N, (temp < 0));
        PSW_WRITE(PSW_Z, (temp == 0));
        PSW_WRITE(PSW_O, ((a > 0 && b > 0 && temp < 0) || (a < 0 && b < 0 && temp > 0)));
    }
}

void logic() {
    int16_t a = (int16_t)r[rd];
    int16_t b = (int16_t)r[rs];

    int16_t temp;
    switch(mod) {
    case 0x0:
        r[rd] = ~a;
        break;
    case 0x1:
        r[rd] = a & b;
        break;
    case 0x2:
        r[rd] = a | b;
        break;
    case 0x3:
        r[rd] = a ^ b;
        break;
    case 0x4:
        temp = a & b;
        PSW_WRITE(PSW_Z, (temp == 0));
        break;
    default:
        break;
    }
}

void shift() {
    int16_t a = (int16_t)r[rd];
    int16_t b = (int16_t)r[rs];
    int al = r[rd];
    int bl = r[rs];
    int templ;
    switch(mod) {
    case 0x0:
        r[rd] = a << b;
        templ = al << bl;
        PSW_WRITE(PSW_C, (templ & ( 1 << 15 )));
        break;
    case 0x1:
        r[rd] = a >> b;
        if(bl != 0)
            PSW_WRITE(PSW_C, (templ & ( 1 << bl )));
        break;
    default:
        break;
    }
}

void load() {
    r[rd] = rb;
}

void store() {
    pre();
    switch(am) {
    case ADDR_MODE_IMMED:
        break;
    case ADDR_MODE_REGDIR:
        r[rs] = r[rd];
        break;
    case ADDR_MODE_REGDIR_PAYLOAD:
        r[rs] = r[rd] + INSRT_PAYLOAD;
        break;
    case ADDR_MODE_REGINDIR:
        mem_write(r[rs], r[rd]);
        break;
    case ADDR_MODE_REGINDIR_PAYLOAD:
        mem_write(r[rs], r[rd] + INSRT_PAYLOAD);
        break;
    case ADDR_MODE_MEM:
        mem_write(INSRT_PAYLOAD, r[rd]);
        break;
    default:
        break;
    }
    post();
}

int instr_execute() {
    switch(oc) {
        case OC_HALT:
            halt();
            break;
        case OC_INT:
            intr();
            break;
        case OC_IRET:
            iret();
            break;
        case OC_CALL:
            call();
            break;
        case OC_RET:
            ret();
            break;
        case OC_JUMP:
            jump();
            break;
        case OC_XCHG:
            xchg();
            break;
        case OC_ARITM:
            aritm();
            break;
        case OC_LOGIC:
            logic();
            break;
        case OC_SHIFT:
            shift();
            break;
        case OC_LOAD:
            load();
            break;
        case OC_STORE:
            store();
            break;
    }
}