#ifndef __MEM_MANAGEMENT_H__
#define __MEM_MANAGEMENT_H__

unsigned int mem_read(unsigned int addr);
void mem_write(unsigned int addr, unsigned int i);

void mem_stack_push(unsigned int i);
unsigned int mem_stack_pop();
#endif