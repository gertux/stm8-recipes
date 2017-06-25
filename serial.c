/**
 * serial: setup the uart and write every second a message
 *
 *
 */
#include <stdio.h>
#include "stm8s103xx.h"
volatile unsigned int count;
void setup(void) {
    count = 0;
    CLK_CKDIVR = 0x00; // 16MHz
    TIM2_PSCR = 0x0f; // clk / 2^0x0f (= 32768) = 488
    TIM2_ARRH = 0x01; //  High byte of 488 (every second).
    TIM2_ARRL = 0xE8; //  Low byte of 488.
    TIM2_IER = 0x01; // Update interrupt enabled
    TIM2_CR1 = 0x01; // Enable timer 2

    UART1_CR2 = UART_CR2_TEN; // Allow TX and RX
    UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2); // 1 stop bit
    UART1_BRR2 = 0x0B; UART1_BRR1 = 0x08; // 115200 baud
}

void putchar(unsigned char c) {
    while(!(UART1_SR & UART_SR_TXE));
    UART1_DR = c;
}

void tim2_isr(void) __interrupt(13) {
    if(TIM2_SR1 & TIMX_SR1_UIF) {
        TIM2_SR1 &= ~TIMX_SR1_UIF;
        printf("%d times interrupted\n", ++count);
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