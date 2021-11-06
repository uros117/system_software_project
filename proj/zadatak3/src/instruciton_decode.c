#include "main.h"
#include "instruction_decode.h"
#include "mem_management.h"

void pre() {
    if(am == ADDR_MODE_REGINDIR || am == ADDR_MODE_REGINDIR_PAYLOAD) {
        switch(up) {
        case UPDATE_PRE_DEC:
            r[rs] -= 2;
            break;
        case UPDATE_PRE_INC:
            r[rs] += 2;
            break;
        default:
            break;    
        }
    }
}

void post() {
    if(am == ADDR_MODE_REGINDIR || am == ADDR_MODE_REGINDIR_PAYLOAD) {
        switch(up) {
        case UPDATE_POST_DEC:
            r[rs] -= 2;
            break;
        case UPDATE_POST_INC:
            r[rs] += 2;
            break;
        default:
            break;
        }
    }
}

int instr_decode() {
    if(oc == OC_STORE) {
        if(am == ADDR_MODE_REGINDIR || am == ADDR_MODE_REGINDIR_PAYLOAD)
            return 0;
        return -1;
    }
    
    pre();
    int temp;
    switch(am) {
        case ADDR_MODE_IMMED:
            rb = INSRT_PAYLOAD;
            break;
        case ADDR_MODE_REGDIR:
            rb = r[rs];
            break;
        case ADDR_MODE_REGDIR_PAYLOAD:
            temp = INSRT_PAYLOAD;
            rb = r[rs] + temp;
        case ADDR_MODE_REGINDIR:
            rb = mem_read(r[rs]);
            break;
        case ADDR_MODE_REGINDIR_PAYLOAD:
            temp = INSRT_PAYLOAD;
            rb = mem_read(r[rs] + temp);
            break;
        case ADDR_MODE_MEM:
            rb = mem_read(INSRT_PAYLOAD);
            break;
        default:
            return -1;
    }

    post();

    return 0;
}