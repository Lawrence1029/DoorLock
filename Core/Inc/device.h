#include "stm32f1xx_hal.h"
#include "fonts.h"
#include "ssd1306.h"

extern char *key_input;

void key_pad_scan();
void stepCCV (int steps, uint16_t delay); // CCV - Counter Clockwise
void stepCV (int steps, uint16_t delay); // CV - Clockwise
