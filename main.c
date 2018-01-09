#include "./headers/infrared.h"
#include "./headers/stepper.h"
#include "./headers/OnLCDLib.h"

const uint16_t POSSIBLE_DELAYS[] = {10, 100, 250, 500, 1000, 2500, 5000};
const uint16_t POSSIBLE_STEPS[] = {8, 16, 32, 64, 128, 256, 512};

void stepsDelayToLCD(uint16_t steps, uint16_t delay);

void cameraDelay(uint16_t delay)
{
	uint16_t i;
	for(i=0; i<delay/10; i++)
	{
		_delay_ms(10);
	}
}

void stepsDelayToLCD(uint16_t steps, uint16_t delay)
{
	LCDWriteStringXY(2,2, "N:");
	LCDWriteInt(steps, 3);
	LCDWriteString(" ms:");
	LCDWriteInt(delay, 4);
}

void start(uint16_t step, uint16_t delay)
{
	uint16_t i, steps = 512/step;
	
	shut();
	for(i=0; i<step; i++)
	{
		LCDClear();
		LCDWriteStringXY(1,1, "Current: ");
		LCDWriteInt(i+1, 3);
		stepsDelayToLCD(step, delay);
		
		makeNSteps(steps);
		shut();
		
		cameraDelay(delay);
	}
}

int main(void)
{	
	setupIR();
	setupStepper();
	LCDSetup(LCD_CURSOR_NONE);
	
	uint16_t step, delay;
	
	step = 8;
	delay = 100; 
	
	while(1)
	{
		LCDClear();
		LCDWriteStringXY(1,1, "Waiting...");
		stepsDelayToLCD(step, delay);
			
		_delay_ms(2000);
		
		start(step, delay);
	}
	return 0;
}
