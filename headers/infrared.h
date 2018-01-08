#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define TOP 24
#define MATCH 6
#define SHUTTER 0xB4B8F

//~ const uint8_t TOP = 24;    // 1000kHz/(TOP + 1) = 40kHz
//~ const uint8_t MATCH = 6;  // 25% duty/cycle
//~ const unsigned long SHUTTER = 0xB4B8F;

void shut(void);
void setupIR(void);
void sendCode(unsigned long code);
void pulse(uint8_t carrier, uint8_t gap);



