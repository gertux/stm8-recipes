/**
 * pwm-awd-control: sample the value on AIN4 (Pin D3) using the analog watchdog interrupt
 *    and use the measured value to control a PWM output
 */
#include <stdio.h>
#include "common.h"

#define AWD_MAX 0x03ff
#define AWD_MIN 0x0000
#define AWD_MARGIN 2
#define DUTYMAX 0xFA

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
    printf("\nawd=0x%04x - awdh=0x%04x - awdl=0x%04x\n", awd, awdh, awdl);
}

void setup(void) {
    CLK_CKDIVR = 0x00; // 16MHz

    PB_DDR = 0x20; // Port 5 : 00010000 = 0x20
    PB_CR1 = 0x20;
    PB_ODR = 0x20;

    ADC_CSR |= (0x04 | ADC_CSR_AWDIE); // ADC channel select : AIN4, AWD interrupt enable
    ADC_CR1 |= (0x40 | ADC_CR1_CONT); // ADC clock select : fm/8 = 2MHz, continuous conversion
    ADC_CR2 |= ADC_CR2_ALIGN_R; // ADC Right data align
    ADC_CR1 |= ADC_CR1_ADON; // ADC power on

    TIM2_PSCR = 0x00;   // clk / 2^0 = clk = 16MHz
    TIM2_ARRH = DUTYMAX;// High byte of 64000 (16MHz/64000 = 250Hz)
    TIM2_ARRL = 0x00;   // Low byte of 64000
    TIM2_CCR1H = DUTYMAX; // High byte of the duty cycle
    TIM2_CCR1L = 0x00;  // Low byte
    TIM2_CCER1 |= TIMX_CCER_CC1E;     // Enable compare mode on channel 1
    TIM2_CCMR1 |= TIMX_CCMR_OCM_PWM1; // PWM mode 1
    TIM2_CR1 = 0x01;    // Enable timer 2

    UART1_CR2 = UART_CR2_TEN; // Allow TX and RX
    UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2); // 1 stop bit
    UART1_BRR2 = 0x0B; UART1_BRR1 = 0x08; // 115200 baud

    ADC_CR1 |= ADC_CR1_ADON; // ADC start conversion

    set_awd(0x0000); // default is 0x3ff which triggers never
}

void putchar(unsigned char c) {
    while(!(UART1_SR & UART_SR_TXE));
    UART1_DR = c;
}

void use_result() {
    register16 v;
    unsigned char dutyh;
    v.bytes[0] = (ADC_DRH & 0x3f);
    v.bytes[1] = ADC_DRL;
    PB_ODR ^= 0x20;
    dutyh = ((v.value & 0x03fc) >> 2);
    if(dutyh > DUTYMAX) {
        TIM2_CCR1H = DUTYMAX;
    } else {
        TIM2_CCR1H = dutyh;
    }
    TIM2_CCR1L = 0x00;
    set_awd(v.value);
    printf("value = 0x%04x - CCR1H=0x%02x CCR1L =0x%02x\n", v.value, TIM2_CCR1H, TIM2_CCR1L);
}

void adc_isr(void) __interrupt(22) {
    if(ADC_CSR & ADC_CSR_AWD) {
        use_result();
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