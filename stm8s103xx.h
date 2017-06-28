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
#define UART1_SR *(unsigned char*)0x5230 // UART 1 status register
#define UART1_DR *(unsigned char*)0x5231 // UART 1 data register
#define UART1_BRR1 *(unsigned char*)0x5232 // UART 1 baud rate register 1
#define UART1_BRR2 *(unsigned char*)0x5233 // UART 1 baud rate register 2
#define UART1_CR1 *(unsigned char*)0x5234 // UART 1 control register 1
#define UART1_CR2 *(unsigned char*)0x5235 // UART 1 control register 2
#define UART1_CR3 *(unsigned char*)0x5236 // UART 1 control register 3
#define TIM1_CR1 *(unsigned char*)0x5250 // Timer 1 control register
#define TIM1_IER *(unsigned char*)0x5254 // Timer 1 interrupt enable register
#define TIM1_SR1 *(unsigned char*)0x5255 // Timer 1 status register 1
#define TIM1_CCMR1 *(unsigned char*)0x5258 // Timer 1 capture/compare mode register 1
#define TIM1_CCER1 *(unsigned char*)0x525C // Timer 1 capture/compare enable register 1
#define TIM1_PSCRH *(unsigned char*)0x5260 // Timer 1 prescaler register high
#define TIM1_PSCRL *(unsigned char*)0x5261 // Timer 1 prescaler register low
#define TIM1_ARRH *(unsigned char*)0x5262 // Timer 1 auto-reload register high
#define TIM1_ARRL *(unsigned char*)0x5263 // Timer 1 auto-reload register low
#define TIM1_CCR1H *(unsigned char*)0x5265 // Timer 1 capture/compare register 1 high
#define TIM1_CCR1L *(unsigned char*)0x5266 // Timer 1 capture/compare register 1 low
#define TIM2_CR1 *(unsigned char*)0x5300 // Timer 2 control register
#define TIM2_IER *(unsigned char*)0x5303 // Timer 2 interrupt enable register
#define TIM2_SR1 *(unsigned char*)0x5304 // Timer 2 status register 1
#define TIM2_CCMR1 *(unsigned char*)0x5307 // Timer 2 capture/compare mode register 1
#define TIM2_CCER1 *(unsigned char*)0x530A // Timer 2 capture/compare enable register 1
#define TIM2_PSCR *(unsigned char*)0x530E // Timer 2 prescaler register
#define TIM2_ARRH *(unsigned char*)0x530F // Timer 2 auto-reload register high
#define TIM2_ARRL *(unsigned char*)0x5310 // Timer 2 auto-reload register low
#define TIM2_CCR1H *(unsigned char*)0x5311 // Timer 2 capture/compare register 1 high
#define TIM2_CCR1L *(unsigned char*)0x5312 // Timer 2 capture/compare register 1 low
#define ADC_CSR *(unsigned char*)0x5400 // ADC control/status register
#define ADC_CR1 *(unsigned char*)0x5401 // ADC configuration register 1
#define ADC_CR2 *(unsigned char*)0x5402 // ADC configuration register 2
#define ADC_DRH *(unsigned char*)0x5404 // ADC data register high
#define ADC_DRL *(unsigned char*)0x5405 // ADC data register low
#define ADC_HTRH *(unsigned char*)0x5408 // ADC high threshold register high
#define ADC_HTRL *(unsigned char*)0x5409 // ADC high threshold register low
#define ADC_LTRH *(unsigned char*)0x540A // ADC low threshold register high
#define ADC_LTRL *(unsigned char*)0x540B // ADC low threshold register low

#define TIMX_SR1_UIF 0x01
#define TIMX_CCER_CC1E 0x01
#define TIMX_CCER_CC1P 0x02
#define TIMX_CCMR_OCM_PWM1 0x60
#define CLK_SWCR_SWEN 0x02
#define CLK_SWCR_SWIF 0x08
#define CLK_SWR_LSI 0xD2
#define UART_CR2_TEN 0x08
#define UART_CR3_STOP1 0x10
#define UART_CR3_STOP2 0x20
#define UART_SR_TXE 0x80
#define ADC_CSR_EOC 0x80
#define ADC_CSR_AWD 0x40
#define ADC_CSR_EOCIE 0x20
#define ADC_CSR_AWDIE 0x10
#define ADC_CR1_CONT 0x02
#define ADC_CR1_ADON 0x01
#define ADC_CR2_ALIGN_R 0x08


#endif //STM8_STM8S103XX_H_H
