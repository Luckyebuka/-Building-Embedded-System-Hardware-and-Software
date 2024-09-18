main.c file
#include <stdio.h>
#include "led.h"
#define LED_BASE 0x60000
#define BUTTON_BASE 0X70000
#define hex7_BASE 0x80000
#define switch0 0x90000
#define button_IRQ 0x1

int hexValue = 0;  // Declare 

int main()
{
  printf("ECE532 assignment1 #1\n");
  printf("Franklin Okoh 1#\n");
  printf("15th September 2024 #1\n");
  alt_ic_isr_register(0,1,(void*)button_isr,NULL,NULL);
alt_ic_irq_enable(0,1);
gpio_regs * gr = button_BASE;
gr->intmask = 1;
led_off();
  while (1)
  {
    //led_on();
    int switchState = get_switch();
    printf("switch = %d\n", switchState);

    if (switchState == 1)
    {
      // Increment the HEX2 value
      //led_on();
      hexValue = (hexValue + 1) % 16;
      printf("hex value = %d", hexValue);
      o_hex();
      //delay(); // Delay after each increment
    }
    else if(switchState == 0)
    {
      // Decrement the HEX2 value
      //led_off();
      hexValue = (hexValue - 1 + 16) % 16;  //
      o_hex();
      //delay(); // Delay after each decrement
    }
    delay(1000000);
  }

  return 0;
}

void o_hex()
{
  gpio_regs *gr = hex_BASE;

  // Define the hexadecimal values for 0-F
  unsigned char hexValues[] = {
    0x40, 0x79, 0x24, 0x30,
    0x19, 0x12, 0x02,
    0x78, 0x00, 0x18,
    0x08, 0x03, 0x27,
    0x21, 0x06, 0x0E
  };

  if (hexValue >= 0 && hexValue < 16)
  {
    gr->data = hexValues[hexValue];
  }
  else
  {
    // Handle an invalid value (out of range)
    gr->data = hexValues[15 - hexValue]; // Display values from F to 0
  }
}
void button_isr(void* isr_context){
	gpio_regs * button = (gpio_regs*) BUTTON_BASE;
	led_on();
	delay(100000);
	led_off();
	button->edge = 1;
}

void delay(int mint)
{
  unsigned int i;
  int n = 1000000;  // Adjust the value to control the delay duration
  for (i = 0; i < mint; i++)
  {
    // Wait
  }
}

void led_on(void)
{
	gpio_regs *gr = LED_BASE;
	gr->data = 0x01;
}
unsigned int get_switch(void)
{
	gpio_regs *gr=switch_BASE;
	return(gr->data);
}
void led_off(void)
{
	gpio_regs *gr = LED_BASE;
	gr->data = 0x00;
}