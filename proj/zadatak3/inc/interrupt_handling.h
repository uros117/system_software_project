#ifndef __INTERRUPT_HANDLING_H__
#define __INTERRUPT_HANDLING_H__

extern int interrupt_signals[8];

#define INT_RESET           (0)
#define INT_BADOC           (1)
#define INT_TIM             (2)
#define INT_KEYBRD          (3)

void signal_interrupt(int i);
void reset_interrupt(int i);

int handle_interrupts();
#endif