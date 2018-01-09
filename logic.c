#include "./headers/infrared.h"
#include "./headers/stepper.h"
#include "./headers/lcd.h"
#include "./headers/logic.h"
#include <stdio.h>
#include <util/delay.h>

const uint16_t POSSIBLE_DELAYS[] = {10, 100, 250, 500, 1000, 2500, 5000};
const uint16_t POSSIBLE_STEPS[] = {8, 16, 32, 64, 128, 256, 512};

void setupButton(void)
{
	BUTTON_ADDR &= ~(1 << BUTTON_NUMBER);
	BUTTON_PORT |= (1 << BUTTON_NUMBER);
}

uint16_t getDelay(uint16_t adc)
{
	uint8_t index = adc/146;
	if(index >= 7) index = 6;
	return POSSIBLE_DELAYS[index];
}

uint16_t getSteps(uint16_t adc)
{
	uint8_t index = adc/146;
	if(index >= 7) index = 6;
	return POSSIBLE_STEPS[index];
}

void cameraDelay(uint16_t delay)
{
	uint16_t i;
	for(i=0; i<delay/10; i++)
	{
		if(buttonPressed()) break;
		_delay_ms(10);
	}
}

void start(uint16_t step, uint16_t delay)
{
	char buffer[16];
	uint16_t i, steps = 512/step;
	
	lcd_home();
	lcd_puts("Current: 000");
	
	_delay_ms(500);
	
	for(i=0; i<step; i++)
	{
		lcd_home();
		snprintf(buffer, sizeof(buffer), "Current: %03d", i+1);
		lcd_puts(buffer);
		
		makeNSteps(steps);
		shut();
		
		cameraDelay(delay);
		if(buttonPressed()) break;
	}
}

uint16_t getADC(uint8_t channel)
{
	ADMUX = (1 << REFS0);
	if(channel)	ADMUX |= (1 << (channel - 1));
	else;
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	
	return ADC;
}

uint8_t buttonPressed(void)
{
	if((BUTTON_PIN & (1<<BUTTON_NUMBER)) == 0) return 1;
	else return 0;
}
