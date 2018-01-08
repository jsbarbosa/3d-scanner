/* Atmega328 Sony Alpha Remote Control
	Juan Barbosa - https://github.com/jsbarbosa/3d-scanner

	Based on:
		David Johnson-Davies - www.technoblogy.com - 12th April 2015
		ATtiny85 @ 1 MHz (internal oscillator; BOD disabled)
		CC BY 4.0
		Licensed under a Creative Commons Attribution 4.0 International license: 
		http://creativecommons.org/licenses/by/4.0/
	Modifications:
		Renamed functions
		No inverted output
		Code syntax
*/


#include "./headers/infrared.h"

void setupIR(void) 
{
	TCCR0A = (1<<COM0A0) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00); // Fast PWM
	TCCR0B = (1<<WGM02) | (1<<CS00);   // Fast PWM and divide by 1
	OCR0A = TOP;                   // 40kHz
	OCR0B = 0;                   // Keep output low 
	DDRD |= (1 << PD5);
}

void pulse(uint8_t carrier, uint8_t gap)
{
	OCR0B = MATCH;  // Generate pulses 
	uint8_t i, c, count = carrier;
	for(i=0; i<2; i++)
	{
		for(c=0; c<count; c++)
		{
			while((TIFR0 & 1<<TOV0) == 0)
			{
			}
			TIFR0 = 1<<TOV0;
		}
		count = gap;
		OCR0B = 0;
	}
}

void sendCode(unsigned long code)
{
	TCNT0 = 0;
	int8_t bit;   
	       
	pulse(96, 24);
	for(bit=19; bit>=0; bit--)
	{
		if(code & ((unsigned long) 1<<bit))
		{
			pulse(48, 24);
		}
		else
		{
			pulse(24, 24);
		}
	}
}

void shut(void)
{
	sendCode(SHUTTER);
	_delay_ms(11);
	sendCode(SHUTTER);
}
