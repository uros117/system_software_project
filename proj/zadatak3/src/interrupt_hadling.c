#include "interrupt_handling.h"
#include "mem_management.h"
#include "main.h"
int interrupt_signals[8] = {};
int is_external_interrupt[8] = {0, 0, 1, 1};
int psw_mask_bit[8] = {-1, -1, 15, 14, -1, -1, -1, -1};

int check_masked_bit_if_exists(int pos) {
    if(psw_mask_bit[pos] > 0) {
        return PSW_READ(psw_mask_bit[pos]);
    }
    return 1;
}

int handle_interrupts() {
    if(interrupt_signals[INT_RESET]) {
        PC = mem_read(0);
    } else {
        for(int i = 1;i < 8;i++) {
            if(
                interrupt_signals[i] && 
                (is_external_interrupt[i] ? !PSW_READ(PSW_I) : 1) &&
                !check_masked_bit_if_exists(i)
            ) {
                // Serve
                interrupt_signals[i] = 0;
                
                mem_stack_push(PC);
                mem_stack_push(PSW);

                PSW_SET(PSW_I);
                
                PC = mem_read(i << 1);
                return 0;
            }
        }
    }
}

void signal_interrupt(int i) {
    if(i >= 0 && i < 8) {
        interrupt_signals[i] = 1;
    }
}

void reset_interrupt(int i) {
    if(i >= 0 && i < 8) {
        interrupt_signals[i] = 0;
    }
}