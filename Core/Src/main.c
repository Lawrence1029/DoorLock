/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLASH_END_ADDRESS 0x0800FFFB  // Address of the last 5 bytes
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

IWDG_HandleTypeDef hiwdg;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Definitions for OLEDTask */
osThreadId_t OLEDTaskHandle;
const osThreadAttr_t OLEDTask_attributes = {
  .name = "OLEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for KeyPadTask */
osThreadId_t KeyPadTaskHandle;
const osThreadAttr_t KeyPadTask_attributes = {
  .name = "KeyPadTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for FingerPrintTask */
osThreadId_t FingerPrintTaskHandle;
const osThreadAttr_t FingerPrintTask_attributes = {
  .name = "FingerPrintTask",
  .stack_size = 300 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LockControl */
osThreadId_t LockControlHandle;
const osThreadAttr_t LockControl_attributes = {
  .name = "LockControl",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_IWDG_Init(void);
void OLEDLoop(void *argument);
void KeyPadLoop(void *argument);
void FingerPrintLoop(void *argument);
void LockControlLoop(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // Your receive callback code here
	char rx;
	if (huart == &huart1)
		HAL_UART_Receive_IT(&huart1, rx, 1);
	else if (huart == &huart2)
		HAL_UART_Receive_IT(&huart2, rx, 1);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of OLEDTask */
  OLEDTaskHandle = osThreadNew(OLEDLoop, NULL, &OLEDTask_attributes);

  /* creation of KeyPadTask */
  KeyPadTaskHandle = osThreadNew(KeyPadLoop, NULL, &KeyPadTask_attributes);

  /* creation of FingerPrintTask */
  FingerPrintTaskHandle = osThreadNew(FingerPrintLoop, NULL, &FingerPrintTask_attributes);

  /* creation of LockControl */
  LockControlHandle = osThreadNew(LockControlLoop, NULL, &LockControl_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg.Init.Reload = 799;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 57600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 FInger_Sense_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|FInger_Sense_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_OLEDLoop */
/**
  * @brief  Function implementing the OLEDTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_OLEDLoop */
void OLEDLoop(void *argument)
{
  /* USER CODE BEGIN 5 */
	  char prev = ' ';
	  uint8_t timeout_counter= 0;
	  SSD1306_Init();
	  char snum[5];

	  SSD1306_GotoXY (0,0);
	  SSD1306_Puts ("Wei", &Font_11x18, 1);
	  SSD1306_GotoXY (0, 30);
	  SSD1306_Puts ("Liu", &Font_11x18, 1);
	  SSD1306_UpdateScreen();
	  HAL_Delay (1000);

	  SSD1306_ScrollLeft(0,7);
	  HAL_Delay(3000);
	  SSD1306_ScrollRight(0,7);
	  HAL_Delay(3000);
	  SSD1306_Stopscroll();
	  SSD1306_Clear();
	  SSD1306_GotoXY (15,0);
	  SSD1306_Puts ("Enter Key", &Font_11x18, 1);
	  SSD1306_UpdateScreen();

  /* Infinite loop */
  for(;;)
  {
	  if(key_input != ' '){
		  if(prev != key_input){
		  		prev = key_input;
		  		SSD1306_GotoXY (53, 30);
		  		SSD1306_Puts ("             ", &Font_16x26, 1);
		  		SSD1306_UpdateScreen();
		  		SSD1306_GotoXY (53, 30);
		  		SSD1306_Puts (&key_input, &Font_16x26, 1);
		  		SSD1306_UpdateScreen();
		  }
	  }else{
		  prev = ' ';
	  }
    
    osDelay(200/ portTICK_PERIOD_MS);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_KeyPadLoop */
/**
* @brief Function implementing the KeyPadTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KeyPadLoop */
void KeyPadLoop(void *argument)
{
  /* USER CODE BEGIN KeyPadLoop */
  char prev = ' ';
  char entry[6];
  uint8_t index = 0;
  /* Infinite loop */
  for (;;)
  {
    key_pad_scan();
	  if(key_input != ' '){
		  if(prev != key_input){
		  		prev = key_input;
		  		SSD1306_GotoXY (53, 30);
		  		SSD1306_Puts ("             ", &Font_16x26, 1);
		  		SSD1306_UpdateScreen();
		  		SSD1306_GotoXY (53, 30);
		  		SSD1306_Puts (&prev, &Font_16x26, 1);
		  		SSD1306_UpdateScreen();

          if(index < 6){
            entry[index] = prev;
            index++;
          }

          if(prev == '#' || prev == '*'){
            SSD1306_Clear();
	          SSD1306_GotoXY (15,0);
            if(strcmp(entry, "980319") == 0){
              if(prev == '#'){
                //unlock
                Lock_state = 0;
	              SSD1306_Puts ("Unlocked", &Font_11x18, 1);
	              SSD1306_UpdateScreen();
              }else{
                SaveFinger_Flag = 1;
                SSD1306_Puts ("Place Finger", &Font_11x18, 1);
	              SSD1306_UpdateScreen();
              }
            }else{
              Lock_state = 1;
              SSD1306_Puts ("Incorrect Pin", &Font_11x18, 1);
	            SSD1306_UpdateScreen();
            }
            // Set all elements in the entry array to zero
            memset(entry, 0, sizeof(entry));
            index = 0;
          }


      }
    }
    osDelay(50 / portTICK_PERIOD_MS);
  }
  /* USER CODE END KeyPadLoop */
}

/* USER CODE BEGIN Header_FingerPrintLoop */
/**
* @brief Function implementing the FingerPrintTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FingerPrintLoop */
void FingerPrintLoop(void *argument)
{
  /* USER CODE BEGIN FingerPrintLoop */
  uint8_t result;
  uint8_t flag = 0;
  /* Infinite loop */
  for (;;)
  {
    if (HAL_GPIO_ReadPin(GPIOA, FInger_Sense_Pin) == GPIO_PIN_SET)
    {
      if(SaveFinger_Flag == 1){
        SSD1306_Clear();
	      SSD1306_GotoXY (15,0);
        SSD1306_Puts ("Saving...", &Font_11x18, 1);
	      SSD1306_UpdateScreen();
        result = save_fingerprint(0);
        SaveFinger_Flag = 0;
        if(result == 0){
          SSD1306_Clear();
	        SSD1306_GotoXY (15,0);
          SSD1306_Puts ("Finger Saved", &Font_11x18, 1);
	        SSD1306_UpdateScreen();
        }else{
          SSD1306_Clear();
	        SSD1306_GotoXY (15,0);
          SSD1306_Puts ("Try Again", &Font_11x18, 1);
	        SSD1306_UpdateScreen();
        }
      }else{
        if (flag == 0)
        {
          result = check_fingerprint();
          if(result == 0){
            //unlock
            Lock_state = 0;
            SSD1306_Puts ("Unlocked", &Font_11x18, 1);
	          SSD1306_UpdateScreen();
          }else{
            Lock_state = 1;
            SSD1306_Puts ("Unknown Finger", &Font_11x18, 1);
	          SSD1306_UpdateScreen();
          }
          flag = 1;
        }
        else
        {
          flag = 0;
        }
      }
    }

    // fingerprint_mode = save_fingerprint(i);//		 AS608_Add_Fingerprint();
    osDelay(50 / portTICK_PERIOD_MS);
  }
  /* USER CODE END FingerPrintLoop */
}

/* USER CODE BEGIN Header_LockControlLoop */
/**
* @brief Function implementing the LockControl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LockControlLoop */
void LockControlLoop(void *argument)
{
  /* USER CODE BEGIN LockControlLoop */
  /* Infinite loop */
  for(;;)
  {
    HAL_IWDG_Refresh(&hiwdg);
    if(Lock_state == 0){
      //while limit switch not triggered
    }else{
      //while limit switch not triggered
      stepCCV(256, 1 / portTICK_PERIOD_MS);
    }
    
    osDelay(50 / portTICK_PERIOD_MS);
  }
  /* USER CODE END LockControlLoop */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
