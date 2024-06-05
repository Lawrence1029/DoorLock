/*
 * device.c
 *
 *  Created on: Apr 19, 2024
 *      Author: lawrence
 */

#include "device.h"

#define IN1_PIN GPIO_PIN_0
#define IN1_PORT GPIOB
#define IN2_PIN GPIO_PIN_1
#define IN2_PORT GPIOB
#define IN3_PIN GPIO_PIN_10
#define IN3_PORT GPIOB
#define IN4_PIN GPIO_PIN_11
#define IN4_PORT GPIOB

char *key_input = " ";
uint8_t SaveFinger_Flag = 0;
uint8_t Lock_state = 0;

void key_pad_scan(){
	key_input = ' ';
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET ){
		key_input = '1';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET ){
		key_input = '2';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET ){
		key_input = '3';
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET ){
		key_input = '4';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET ){
		key_input = '5';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET ){
		key_input = '6';
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET ){
		key_input = '7';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET ){
		key_input = '8';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET ){
		key_input = '9';
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET ){
		key_input = '*';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET ){
		key_input = '0';
	}else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET ){
		key_input = '#';
	}
}

void stepCCV (int steps, uint16_t delay) // CCV - Counter Clockwise
{
  for(int x=0; x<steps; x=x+1)
  {
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    osDelay(delay);
  }
}

void stepCV (int steps, uint16_t delay) // CV - Clockwise
{
  for(int x=0; x<steps; x=x+1)
  {
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    osDelay(delay);
  }
}
