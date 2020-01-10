#include <stdint.h>
#include "stm8.h"

void setupOutGPIO()
{
	//Onboard LED
	PB_DDR = 0x20;
	PB_CR1 = 0x20;
	PB_ODR = 1 << 5;
}

void setupTimer()
{
	//FOSC = 8MHz
	//FSAMP = 8kHz
	//8.000.000 / 8 / 125
	//8 = Prescaler
	//125 = Counter

	//FOR FOSC Prescaler = Prescaler * 2

	TIM4_PSCR = 0x04; //Prescaler: 0x03=8 0x04=16
//	TIM4_ARR = 125;
	TIM4_ARR = 123;
	TIM4_IER = 1;
	//TIM4_CR1 = (uint8_t)(TIM_CR1_APRE | TIM_CR1_URS | TIM_CR1_CEN);
	//TIM4_CR1 = (1 << TIM_CR1_CEN);
	TIM4_CR1 = 0x85;
}

uint16_t audio_idx = 0;

//ISR(timer4_isr, TIM4_OVR_UIF_vector) {
void tim4_isr() __interrupt(23) {
	TIM4_SR = 0; // Reset Interrupts (LAZY)
	audio_idx++;
	
	PB_ODR = (audio_idx % 2 > 0) << 5;
}

int main(void)
{
	/* Set clock to full speed (16 Mhz) */
	CLK_CKDIVR = 0;
	setupOutGPIO();
	setupTimer();

	enableInterrupts();

	while(1) {
	}
}

