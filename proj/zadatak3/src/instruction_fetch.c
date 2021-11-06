#include <stdlib.h>
#include "main.h"



int instr_len() {
    if(
        oc == 0b0000 ||
        oc == 0b0010 ||
        oc == 0b0100
        ) {
        
        return 1;
    } else if (
        oc == 0b0001 ||
        oc == 0b0110 ||
        oc == 0b0111 ||
        oc == 0b1000 ||
        oc == 0b1001
        ) {
        return 2;
    } // Finish
}

int is_reg_instr() {
    if(
        oc == 0b0000 ||
        oc == 0b0010 ||
        oc == 0b0100
    )
        return 0;
    return 1;
}

int is_address_instr() {
    return
        oc == 0x3 ||
        oc == 0x5 ||
        oc == 0xa ||
        oc == 0xb ;
}

int is_supported_instr() {
    return 
        instr[0] == 0x00 ||
        instr[0] == 0x10 ||
        instr[0] == 0x20 ||
        instr[0] == 0x30 ||
        instr[0] == 0x40 ||
        instr[0] == 0x50 ||
        instr[0] == 0x51 ||
        instr[0] == 0x52 ||
        instr[0] == 0x53 ||
        instr[0] == 0x60 ||
        instr[0] == 0x70 ||
        instr[0] == 0x71 ||
        instr[0] == 0x72 ||
        instr[0] == 0x73 ||
        instr[0] == 0x74 ||
        instr[0] == 0x70 ||
        instr[0] == 0x80 ||
        instr[0] == 0x81 ||
        instr[0] == 0x82 ||
        instr[0] == 0x83 ||
        instr[0] == 0x84 ||
        instr[0] == 0x90 ||
        instr[0] == 0x91 ||
        instr[0] == 0xa0 ||
        instr[0] == 0xb0 ;
}

int is_payload_insrt() {
    return
        am == ADDR_MODE_IMMED ||
        am == ADDR_MODE_REGDIR_PAYLOAD ||
        am == ADDR_MODE_REGINDIR_PAYLOAD ||
        am == ADDR_MODE_MEM;
}

int instr_fetch() {
    // InstrDesc
    instr[0] = mem[PC];
    PC++;
    oc = instr[0] >> 4;
    mod = instr[0] & 0x0f;

    if(!is_supported_instr())
        return -1;

    if(!is_reg_instr())
        return 1;
    
    instr[1] = mem[PC];
    PC++;
    rd = instr[1] >> 4;
    rs = instr[1] & 0x0f;
    
    if(!is_address_instr())
        return 2;
    
    instr[2] = mem[PC];
    PC++;
    up = instr[2] >> 4;
    am = instr[2] & 0x0f;

    if(!is_payload_insrt())
        return 3;

    instr[3] = mem[PC];
    PC++;

    instr[4] = mem[PC];
    PC++;

    return 5;
}