#ifndef __TERM_H__
#define __TERM_H__
#include "stdint.h"

int term_init();
void term_loop();
void term_deinit();

uint16_t term_read();
void term_write(uint16_t c);
#endif