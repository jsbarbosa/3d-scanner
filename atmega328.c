#include "./headers/infrared.h"

int main(void)
{
	setupIR();
	
	while(1)
	{
		shut();
		_delay_ms(2000);
	}
	return 0;
}
