#include "./headers/infrared.h"
#include "./headers/stepper.h"
#include "./headers/lcd.h"
#include "./headers/logic.h"
#include <util/delay.h>
#include <stdio.h>

int main(void)
{	
	setupIR();
	setupStepper();
	setupButton();
	
	char buffer[34];
	uint16_t step, delay;
	
	lcd_init(LCD_DISP_ON);
	
	while(1)
	{
		lcd_home();	
		
		step = getSteps(getADC(0));
		delay = getDelay(getADC(1));
		
		snprintf(buffer, sizeof(buffer), "Waiting...\nN:%03d ms:%04d", step, delay);
		lcd_puts(buffer);
		
		if(buttonPressed())
		{
			start(step, delay);
			lcd_clrscr();
			snprintf(buffer, sizeof(buffer), "Waiting...\nN:%03d ms:%04d", step, delay);
			_delay_ms(500);
		}		
	}
	return 0;
}
