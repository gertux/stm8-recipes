/**
 * blinky: blink the on board LED connected to B5 and an external LED if connected to
 *   D4 and GND using a dumb wait routine.
 *   We are looking for a 1Hz signal with 50% duty for LED B5 and 50% duty for LED D4
 *
 **/
#include "stm8s103xx.h"

#define WAITS 15625/25 // about 0.5s wait for 15625Hz

void setup(void) {
    CLK_CKDIVR = 0x1f; // 16MHz (Base)/ 8 (HSIDIV) / 128 (CPUDIV) = 15625Hz
    PB_DDR = 0x20; // Port 5 : 00010000 = 0x20
    PB_CR1 = 0x20;
    PD_DDR = 0x10; // Port 4 : 00001000 = 0x10
    PD_CR1 = 0x10;
    PB_ODR = 0x20;
    PD_ODR = 0x10;
}

int main() {
	int d;

    setup();

	do {
        PB_ODR ^= 0x20; // Flip the active bits
        PD_ODR ^= 0x10;
//		 Dumb loop
		for(d = 0; d < WAITS; d++) {
		}
	} while(1);
}
