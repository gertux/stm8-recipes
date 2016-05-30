#define PB_ODR *(unsigned char*)0x500F
#define PB_IDR *(unsigned char*)0x5010
#define PB_DDR *(unsigned char*)0x5011
#define PB_CR1 *(unsigned char*)0x5012
#define PB_CR2 *(unsigned char*)0x5013

int main() {
	int d;
	PB_DDR = 0x20;
	PB_CR1 = 0x20;

	do {
		PB_ODR ^= 0x20;
		for(d = 0; d < 29000; d++) {}
	} while(1);
}
