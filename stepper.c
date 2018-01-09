#include "./headers/stepper.h"

#define STEPPER_CONFIG_ADDRESS DDRD
#define STEPPER_PORT PORTD
#define STEPPER_PORT1 PD0
#define STEPPER_PORT2 PD1
#define STEPPER_PORT3 PD2
#define STEPPER_PORT4 PD3

const uint8_t STEPPER_PORTS[] = {STEPPER_PORT1, STEPPER_PORT2, 
				STEPPER_PORT3, STEPPER_PORT4};
const uint8_t STEPPER_BITS = (1 << STEPPER_PORT1) | (1 << STEPPER_PORT2) | (1 << STEPPER_PORT3) | (1 << STEPPER_PORT4);

void setupStepper(void) 
{
	STEPPER_CONFIG_ADDRESS |= STEPPER_BITS;
}

void delay(void)
{
	_delay_ms(3);
}

void cleanPort(void)
{	
	STEPPER_PORT &= ~STEPPER_BITS;
}

void step(void)
{
	uint8_t i;
	for(i=0; i<4; i++)
	{
		cleanPort();
		STEPPER_PORT |= (1 << STEPPER_PORTS[i]);
		delay();
	}
}

void makeNSteps(uint8_t n)
{
	uint8_t i;
	for(i=0; i<n;i++) step();
	cleanPort();
}
