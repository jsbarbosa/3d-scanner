#include <stdint.h>
#include <avr/io.h>

#define BUTTON_ADDR DDRB
#define BUTTON_PORT PORTB
#define BUTTON_NUMBER PB7
#define BUTTON_PIN PINB

void setupButton(void);
uint8_t buttonPressed(void);
uint16_t getDelay(uint16_t adc);
uint16_t getSteps(uint16_t adc);
void cameraDelay(uint16_t delay);
uint16_t getADC(uint8_t channel);
void start(uint16_t step, uint16_t delay);
