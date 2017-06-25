//
// Created by gert on 24/06/17.
//

#ifndef STM8_STM8S103XX_H_H
#define STM8_STM8S103XX_H_H
#define PB_ODR *(unsigned char*)0x5005  // Port B data output latch register
#define PB_DDR *(unsigned char*)0x5007  // Port B data direction register
#define PB_CR1 *(unsigned char*)0x5008  // Port B control register 1
#define PD_ODR *(unsigned char*)0x500F  // Port D data output latch register
#define PD_DDR *(unsigned char*)0x5011  // Port D data direction register
#define PD_CR1 *(unsigned char*)0x5012  // Port D control register 1
#define CLK_SWR *(unsigned char*)0x50C4  // Clock master switch register
#define CLK_SWCR *(unsigned char*)0x50C5  // Clock control register
#define CLK_CKDIVR *(unsigned char*)0x50C6  // Clock divider
#define TIM2_CR1 *(unsigned char*)0x5300 // Timer 2 control register
#define TIM2_IER *(unsigned char*)0x5303 // Timer 2 interrupt enable register
#define TIM2_SR1 *(unsigned char*)0x5304 // Timer 2 status register 1
#define TIM2_PSCR *(unsigned char*)0x530E // Timer 2 prescaler register
#define TIM2_ARRH *(unsigned char*)0x530F // Timer 2 auto-reload register high
#define TIM2_ARRL *(unsigned char*)0x5310 // Timer 2 auto-reload register low

#define TIMX_SR1_UIF 0x01
#define CLK_SWCR_SWEN 0x02
#define CLK_SWCR_SWIF 0x08

#define CLK_SWR_LSI 0xD2

#define __wait_for_interrupt() { __asm__("wfi\n"); }
#define __enable_interrupts() { __asm__("rim"); }
#define __disable_interrupts() { __asm__("sim"); }

#endif //STM8_STM8S103XX_H_H
