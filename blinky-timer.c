/**
 * blinky-timer: blink the on board LED connected to B5 and an external LED if
 *   connected to D4 and GND using a timer interrupt.
 *   We want a 1Hz signal with 50% duty for LED B5 and 50% duty for LED D4
 *
 **/
#include "common.h"

void setup(void) {
    CLK_CKDIVR = 0x00; // 16MHz
	PB_DDR = 0x20; // Port 5 : 00010000 = 0x20
	PB_CR1 = 0x20;
	PD_DDR = 0x10; // Port 4 : 00001000 = 0x10
	PD_CR1 = 0x10;
    PB_ODR = 0x20;
    PD_ODR = 0x10;

    TIM2_PSCR = 0x07; // clk / 2^0x07 (= 128) = 125000
    TIM2_ARRH = 0xf4; //  High byte of 62500 (= 125000/2 -> 50% duty).
    TIM2_ARRL = 0x24; //  Low byte of 62500.
    TIM2_IER = 0x01; // Update interrupt enabled
    TIM2_CR1 = 0x01; // Enable timer 2
}

void tim2_isr(void) __interrupt(13) {
    if(TIM2_SR1 & TIMX_SR1_UIF) {
        PB_ODR ^= 0x20;
        PD_ODR ^= 0x10;
        TIM2_SR1 &= ~TIMX_SR1_UIF;
    }
}

int main() {
    __disable_interrupts();
	setup();
    __enable_interrupts();

	do {
        __wait_for_interrupt();
    } while(1);
}
