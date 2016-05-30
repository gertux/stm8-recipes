/**
* blinky: blink the LED on the board connected to B5
*         and an external LED if connected to D4
*         using a dumb wait routine
**/
#define PB_ODR *(unsigned char*)0x5005  // Port B data output latch register
#define PB_DDR *(unsigned char*)0x5007  // Port B data direction register
#define PB_CR1 *(unsigned char*)0x5008  // Port B control register 1
#define PD_ODR *(unsigned char*)0x500F  // Port D data output latch register
#define PD_DDR *(unsigned char*)0x5011  // Port D data direction register
#define PD_CR1 *(unsigned char*)0x5012  // Port D control register 1
#define CLK_CKDIVR *(unsigned char*)0x50C6  // Clock divider 

int main() {
	long d;
	CLK_CKDIVR = 0x00;
	PB_DDR = 0x20; // Port 5 : 00010000 = 0x20
	PB_CR1 = 0x20;
	PD_DDR = 0x10; // Port 4 : 00001000 = 0x10
	PD_CR1 = 0x10;

	do {
		PB_ODR ^= 0x20; // Flip the active bits
		PD_ODR ^= 0x10; 
		// Dumb loop
		for(d = 0; d < 80000; d++) {
		}
	} while(1);
}
