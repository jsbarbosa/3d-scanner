#include <stdint.h>

#define TOP 24
#define MATCH 6
#define SHUTTER 0xB4B8F

void shut(void);
void setupIR(void);
void sendCode(unsigned long code);
void pulse(uint8_t carrier, uint8_t gap);



