
//ECE 532 - Header for LED GPIO
// Franklin Okoh
// 12th September 2024
//
// definitions
//Franklin Okoh
#define LED_BASE 0x60000
#define switch_BASE 0x90000
#define hex_BASE 0x80000
#include<sys/alt_irq.h>
#define button_BASE 0x70000
void led_on(void);
unsigned int get_switch(void);
void o_hex(void);
void delay(int mint);
void button_isr(void* isr_context);

typedef struct gr{
	unsigned int data;
	unsigned int dir;
	unsigned int intmask;
	unsigned int edge;
	unsigned int outset;
	unsigned int outclear;
	unsigned int p2;
} gpio_regs;