/**
 * pwm: output a PWM signal on timer 2 channel 1 (pin D4)
 *  change the PWM signal every 0.05 second between max and min duty
 *  timer 1 is used to variate the PWM duty cycle setting
 *  timer 2 is used to generate the PWM signal
 */
#include "common.h"
#define DUTYMAX 0xFA
volatile unsigned char dutyh;
volatile unsigned char dir;

void setup(void) {
    dutyh = DUTYMAX;
    dir = 0x01;
    CLK_CKDIVR = 0x00;  // 16MHz

    TIM1_PSCRH = 0x00;  // High byte of 250 (clk / 250 = 64000)
    TIM1_PSCRL = 0xFA;  // Low byte of 250
    TIM1_ARRH = 0x0C;   // High byte of 3200 (every 0.05 second).
    TIM1_ARRL = 0x80;   // Low byte of 3200.
    TIM1_IER = 0x01;    // Update interrupt enabled
    TIM1_CR1 = 0x01;    // Enable timer 1

    TIM2_PSCR = 0x00;   // clk / 2^0 = clk = 16MHz
    TIM2_ARRH = DUTYMAX;// High byte of 64000 (16MHz/64000 = 250Hz)
    TIM2_ARRL = 0x00;   // Low byte of 64000
    TIM2_CCR1H = dutyh; // High byte is the variable part of the duty cycle
    TIM2_CCR1L = 0x00;  // We ignore the low byte
    TIM2_CCER1 |= TIMX_CCER_CC1E;     // Enable compare mode on channel 1
    TIM2_CCMR1 |= TIMX_CCMR_OCM_PWM1; // PWM mode 1
    TIM2_CR1 = 0x01;    // Enable timer 2
}

void tim1_isr(void) __interrupt(11) {
    if(TIM1_SR1 & TIMX_SR1_UIF) {
        TIM1_SR1 &= ~TIMX_SR1_UIF;
        if(dutyh == 0x00 || dutyh == DUTYMAX) {
            dir ^= 0x01;
        }
        if(dir) {
            dutyh++;
        } else {
            dutyh--;
        }
        TIM2_CCR1H = dutyh;
        TIM2_CCR1L = 0x00;
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