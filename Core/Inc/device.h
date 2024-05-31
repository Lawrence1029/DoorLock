#include "stm32f1xx_hal.h"
#include "fonts.h"
#include "ssd1306.h"
#include "fingerprint.h"


extern char *key_input;
extern uint8_t SaveFinger_Flag;

void key_pad_scan();
void stepCCV (int steps, uint16_t delay); // CCV - Counter Clockwise
void stepCV (int steps, uint16_t delay); // CV - Clockwise
