// to be replaced with a header file for your chosen micro controller
#include "stm8s103xx.h"

#ifndef STM8_COMMON_H_H
#define STM8_COMMON_H_H

#define __wait_for_interrupt() { __asm__("wfi\n"); }
#define __enable_interrupts() { __asm__("rim"); }
#define __disable_interrupts() { __asm__("sim"); }

typedef union {
    unsigned int value;
    unsigned char bytes[2];
} register16;

#endif //STM8_COMMON_H_H
