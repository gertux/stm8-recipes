/**
 * awd: sample the value on AIN4 (Pin D3) and write the result on UART1
 *   use the analog watchdog interrupt
 *
 */
#include <stdio.h>
#include "common.h"

#define AWD_MAX 0x03ff
#define AWD_MIN 0x0000
#define AWD_MARGIN 2

volatile unsigned int value;

void set_awd(unsigned int awd) {
    unsigned int awdl, awdh;
    if(awd < (AWD_MIN + AWD_MARGIN)) {
        awdl = AWD_MIN;
    } else {
        awdl = awd - AWD_MARGIN;
    }
    ADC_LTRL = (awdl & 0x0003);
    ADC_LTRH = ((awdl & 0x03fc) >> 2);
    if (awd > (AWD_MAX - AWD_MARGIN)) {
        awdh = AWD_MAX;
    } else {
        awdh = awd + AWD_MARGIN;
    }
    ADC_HTRL = (awdh & 0x0003);
    ADC_HTRH = ((awdh & 0x03fc) >> 2);
//    printf("\nawd=0x%04x - awdh=0x%04x - awdl=0x%04x\n", awd, awdh, awdl);
}

void setup(void) {
    value = 0;

    CLK_CKDIVR = 0x00; // 16MHz

    PB_DDR = 0x20; // Port 5 : 00010000 = 0x20
    PB_CR1 = 0x20;
    PB_ODR = 0x20;

    ADC_CSR |= (0x04 | ADC_CSR_AWDIE); // ADC channel select : AIN4, AWD interrupt enable
    ADC_CR1 |= (0x40 | ADC_CR1_CONT); // ADC clock select : fm/8 = 2MHz, continuous conversion
    ADC_CR2 |= ADC_CR2_ALIGN_R; // ADC Right data align
    ADC_CR1 |= ADC_CR1_ADON; // ADC power on

    UART1_CR2 = UART_CR2_TEN; // Allow TX and RX
    UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2); // 1 stop bit
    UART1_BRR2 = 0x0B; UART1_BRR1 = 0x08; // 115200 baud

    ADC_CR1 |= ADC_CR1_ADON; // ADC start conversion

    set_awd(value);
}

void putchar(unsigned char c) {
    while(!(UART1_SR & UART_SR_TXE));
    UART1_DR = c;
}

void log_result() {
    register16 v;
    v.bytes[0] = (ADC_DRH & 0x3f);
    v.bytes[1] = ADC_DRL;
    if(v.value != value) {
        PB_ODR ^= 0x20;
        value = v.value;
        set_awd(value);
        printf("value = 0x%04x\n", value);
    }
}

void eoc_isr(void) __interrupt(22) {
    if(ADC_CSR & ADC_CSR_AWD) {
        log_result();
        ADC_CSR &= ~ADC_CSR_AWD;
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