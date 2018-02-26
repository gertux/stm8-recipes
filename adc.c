/**
 * adc: sample the value on AIN4 (Pin D3) and write the result on UART1
 *   use the end-of-conversion interrupt
 *
 */
#include <stdio.h>
#include "common.h"

volatile unsigned int value;

void setup(void) {
    value = 0;

    CLK_CKDIVR = 0x00; // 16MHz

    ADC_CSR |= (0x04 | ADC_CSR_EOCIE); // ADC channel select : AIN4, EOC interrupt enable
    ADC_CR1 |= (0x40 | ADC_CR1_CONT); // ADC clock select : fm/8 = 2MHz, continuous conversion
    ADC_CR2 |= ADC_CR2_ALIGN_R; // ADC Right data align
    ADC_CR1 |= ADC_CR1_ADON; // ADC power on

    UART1_CR2 = UART_CR2_TEN; // Allow TX and RX
    UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2); // 1 stop bit
    UART1_BRR2 = 0x0B; UART1_BRR1 = 0x08; // 115200 baud

    ADC_CR1 |= ADC_CR1_ADON; // ADC start conversion
}

void putchar(unsigned char c) {
    while(!(UART1_SR & UART_SR_TXE));
    UART1_DR = c;
}

void log_result() {
    register16 v;
    v.bytes[0] = (ADC_DRH & 0x3f);
    v.bytes[1] = ADC_DRL;
    if((v.value & 0xfffc) != (value & 0xfffc)) { // don't update too often
        value = v.value;
        printf("value = 0x%04x\n", value);
    }
}

void adc_isr(void) __interrupt(22) {
    if(ADC_CSR & ADC_CSR_EOC) {
        log_result();
        ADC_CSR &= ~ADC_CSR_EOC;
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