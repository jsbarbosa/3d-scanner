#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

void step(void);
void delay(void);
void cleanPort(void);
void setupStepper(void);
void makeNSteps(uint8_t n);
