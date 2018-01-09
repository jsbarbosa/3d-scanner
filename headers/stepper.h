#include <stdint.h>
#include <avr/io.h>

void step(void);
void delay(void);
void cleanPort(void);
void setupStepper(void);
void makeNSteps(uint8_t n);
