#ifndef __TIM_H__
#define __TIM_H__
#include "stdint.h"

int tim_init();
void tim_loop();
void tim_deinit();

uint16_t tim_read();
void tim_write(uint16_t c);

#endif