#include "tim.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "interrupt_handling.h"

void *tim_timer_loop( void *ptr );
pthread_t tim_timer_loop_thread;
volatile int tim_timer_run = 1;
volatile int tim_write_flag = 0;
volatile int tim_flag = 0;
volatile uint16_t tim_cfg = 0;

uint16_t tim_read() {
    return tim_cfg;
}

void tim_write(uint16_t c) {
    tim_cfg = c;
    tim_write_flag = 1;
}

int tim_init() {
    tim_write(0x0);
    pthread_create( &tim_timer_loop_thread, NULL, tim_timer_loop, NULL);
    return 0;
}

void tim_deinit() {
    tim_timer_run = 0;
    pthread_join( tim_timer_loop_thread, NULL);
}

void tim_loop() {
    if(tim_flag) {
        tim_flag = 0;
        signal_interrupt(INT_TIM);
    }
}

void *tim_timer_loop( void *ptr )
{   
    long curr = 0;
    long mark = 500;
    int delta = 50;
    while(tim_timer_run) {
        if(tim_write_flag == 1) {
            curr = 0;
            uint16_t temp = tim_cfg;
            switch(temp) {
            case 0x0:
                mark = 500;
                break;
            case 0x1:
                mark = 1000;
                break;
            case 0x2:
                mark = 1500;
                break;
            case 0x3:
                mark = 2000;
                break;
            case 0x4:
                mark = 5000;
                break;
            case 0x5:
                mark = 10000;
                break;
            case 0x6:
                mark = 30000;
                break;
            default:
            case 0x7:
                mark = 60000;
                break;
            
            }
            tim_write_flag = 0;
        }

        usleep(delta * 1000);
        curr += delta;

        if(curr >= delta) {
            tim_flag = 1;
            curr = 0;
        }
    }
    
}