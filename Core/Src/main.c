/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "command.h"
#include <stdio.h>
#include "drv8880.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUF_SIZE 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t motor_dir = 0;
extern volatile uint32_t step_cnt;
extern volatile uint32_t shot_cnt;
extern uint8_t drv8880_state;
extern unsigned char nexMessage[10];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* TIM6 : DAC Trigger */
//  HAL_TIM_Base_Start(&htim6);
//  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char commandline[25];
	uint16_t tmp = 0;
	uint16_t freq = 0;

	uint16_t value=0;
	uint16_t buffer[BUF_SIZE];

	for(int i=0;i<BUF_SIZE;i++)
	{
		value = (uint16_t)rint((sinf(((2*3.141592)/BUF_SIZE)*i)+1)*2048);
		buffer[i]=value <4096 ? value : 4095;
	}
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_DAC_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  printf("\n\nSTM32F103RG Test Ver0.1\n");

  printf(" - SysClk Freq. : %d\n", HAL_RCC_GetSysClockFreq());
  printf(" - HCLK Freq. : %d\n", HAL_RCC_GetHCLKFreq());
  printf(" - PCLK1 Freq. : %d\n", HAL_RCC_GetPCLK1Freq());
  printf(" - PCLK2 Freq. : %d\n", HAL_RCC_GetPCLK2Freq());

  HAL_UART_Receive_IT(&huart2, nexMessage, 10);

  HAL_GPIO_WritePin(STATUS0_GPIO_Port, STATUS0_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(STATUS1_GPIO_Port, STATUS1_Pin, GPIO_PIN_RESET);

  // Step Motor driver initial
  drv8880_init();

//  printf("DAC_OUT1 Start...\n");
//  /* TIM6 : DAC Trigger */
//  HAL_TIM_Base_Start(&htim6);
////  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
//  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)buffer, BUF_SIZE, DAC_ALIGN_12B_R);

//  printf("TIM3 OC Start...\n");
//  HAL_TIM_Base_Start_IT(&htim3);
//  HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_1);
//  HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_2);

  if(HAL_GPIO_ReadPin(L_LIMIT_GPIO_Port, L_LIMIT_Pin))
  {
	  motor_dir = 0;
	  printf("motor dir %d\n", motor_dir);
  }
  else if(HAL_GPIO_ReadPin(U_LIMIT_GPIO_Port, U_LIMIT_Pin))
  {
	  motor_dir = 1;
	  printf("motor dir %d\n", motor_dir);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/*	if(drv8880_state == 1)
	{
		HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
	}
	else
	{
		HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_3);
	}
*/

	  //If there is no '\n' in Ture Studio, printf will not be printed.
	  DebugUart_PutStr("\nTEST> ");
	  GetCommand(commandline, 25);
	  if(MyStrNCmp(commandline, "led", 3) == 0)
	  {
	  	  sscanf(commandline, "%*s %d", &tmp);
	  	  if(tmp==1)
	  		HAL_GPIO_WritePin(STATUS0_GPIO_Port, STATUS0_Pin, GPIO_PIN_SET);
	  	  else
	  		  HAL_GPIO_WritePin(STATUS0_GPIO_Port, STATUS0_Pin, GPIO_PIN_RESET);
	  }
	  else if(MyStrNCmp(commandline, "motor", 5) == 0)
	  {
		  printf("motor step_cnt %d\n", step_cnt);
		  HAL_GPIO_WritePin(STATUS1_GPIO_Port, STATUS1_Pin, GPIO_PIN_SET);

	  	  sscanf(commandline, "%*s %d", &tmp);
	  	  if(tmp==1)
	  	  {
			  printf("drv8880 enable\n");
			  drv8880_enable();
			  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
	  	  }
	  	  else
	  	  {
	  		  HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_3);
	  		  printf("drv8880 disable\n");
	  		  drv8880_disable();
	  	  }
	  }
	  else if(MyStrNCmp(commandline, "dir", 3) == 0)
	  {
	  	  sscanf(commandline, "%*s %d", &motor_dir);
	  	  printf("motor dir is %d\n", motor_dir);
	  	  drv8880_dir(motor_dir);
	  }
	  else if(MyStrNCmp(commandline, "step", 4) == 0)
	  {
	  	  sscanf(commandline, "%*s %d", &step_cnt);
	  	  printf("motor step cnt is %d\n", step_cnt);
	  }
	  else if(MyStrNCmp(commandline, "shot", 4) == 0)
	  {
	  	  sscanf(commandline, "%*s %d", &shot_cnt);
	  	  printf("shot cnt is %d\n", shot_cnt);
	  }
	  else if(MyStrNCmp(commandline, "freq", 4) == 0)
	  {
	  	  sscanf(commandline, "%*s %d", &freq);

	  	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (1000000/freq)/2);
//	  	  htim3.Instance->CCR3 = (1000000/freq)/2;
	  	  __HAL_TIM_SET_AUTORELOAD(&htim3, 1000000/freq - 1);
//	  	  htim3.Instance->ARR = 1000000/freq - 1;

	  	  printf("motor freq is %d Hz\n", freq);
	  }
	  else if(MyStrNCmp(commandline, "sleep", 5) == 0)
	  {
	  	  sscanf(commandline, "%*s %d", &tmp);
	  	  printf("Motor Sleep is %d\n", tmp);
	  	  drv8880_sleep(tmp);
	  }
	  else if(MyStrNCmp(commandline, "microstep", 9) == 0)
	  {
		  sscanf(commandline, "%*s %d", &tmp);
		  switch(tmp)
		  {
		  	  case 0:
		  		  HAL_GPIO_WritePin(M_M0_GPIO_Port, M_M0_Pin, GPIO_PIN_RESET);
		  		  HAL_GPIO_WritePin(M_M1_GPIO_Port, M_M1_Pin, GPIO_PIN_RESET);
		  		  printf("full step mode\n");
		  		  break;
		  	  case 2:
		  		  HAL_GPIO_WritePin(M_M0_GPIO_Port, M_M0_Pin, GPIO_PIN_RESET);
		  		  HAL_GPIO_WritePin(M_M1_GPIO_Port, M_M1_Pin, GPIO_PIN_SET);
		  		  printf("1/2 step mode\n");
		  		  break;
		  	  case 4:
		  		  HAL_GPIO_WritePin(M_M0_GPIO_Port, M_M0_Pin, GPIO_PIN_SET);
		  		  HAL_GPIO_WritePin(M_M1_GPIO_Port, M_M1_Pin, GPIO_PIN_SET);
		  		  printf("1/4 step mode\n");
		  		  break;
		  	  default:
		  		  printf("select 0(full step), 2(1/2 step), 4(1/4 step)\n");
		  		  break;
		  }
	  }
	  else if(MyStrNCmp(commandline, "torq", 4) == 0)
	  {
		  sscanf(commandline, "%*s %d", &tmp);
		  switch(tmp)
		  {
		  	  case 25:
		  		  HAL_GPIO_WritePin(M_TRQ0_GPIO_Port, M_TRQ0_Pin, GPIO_PIN_SET);
		  		  HAL_GPIO_WritePin(M_TRQ1_GPIO_Port, M_TRQ1_Pin, GPIO_PIN_SET);
		  		  printf("torque 25%%\n");
		  		  break;
		  	  case 50:
		  		  HAL_GPIO_WritePin(M_TRQ0_GPIO_Port, M_TRQ0_Pin, GPIO_PIN_RESET);
		  		  HAL_GPIO_WritePin(M_TRQ1_GPIO_Port, M_TRQ1_Pin, GPIO_PIN_SET);
		  		  printf("torque 50%%\n");
		  		  break;
		  	  case 75:
		  		  HAL_GPIO_WritePin(M_TRQ0_GPIO_Port, M_TRQ0_Pin, GPIO_PIN_SET);
		  		  HAL_GPIO_WritePin(M_TRQ1_GPIO_Port, M_TRQ1_Pin, GPIO_PIN_RESET);
		  		  printf("torque 75%%\n");
		  		  break;
		  	  case 100:
		  		  HAL_GPIO_WritePin(M_TRQ0_GPIO_Port, M_TRQ0_Pin, GPIO_PIN_RESET);
		  		  HAL_GPIO_WritePin(M_TRQ1_GPIO_Port, M_TRQ1_Pin, GPIO_PIN_RESET);
		  		  printf("torque 100%%\n");
		  		  break;
		  	  default:
		  		  printf("select 25, 50, 75, 100\n");
		  		  break;
		  }
	  }
	  else if(MyStrNCmp(commandline, "tca1r", 5) == 0)
	  {
		  uint16_t addr;

	  	  sscanf(commandline, "%*s %x", &addr);
	  	  printf("reg[%x] data[%x]\n",addr, read_tca1_reg(addr));
	  }
	  else if(MyStrNCmp(commandline, "tca1w", 5) == 0)
	  {
		  uint16_t addr, data;

	  	  sscanf(commandline, "%*s %x %x", &addr, &data);
	  	  printf("addr = %x\ndata = %x\n", addr, data);
	  	  write_tca1_reg(addr, data);
	  }
	  else if(MyStrNCmp(commandline, "tca2r", 5) == 0)
	  {
		  uint16_t addr;

	  	  sscanf(commandline, "%*s %x", &addr);
	  	  printf("reg[%x] data[%x]\n",addr, read_tca2_reg(addr));
	  }
	  else if(MyStrNCmp(commandline, "tca2w", 5) == 0)
	  {
		  uint16_t addr, data;

	  	  sscanf(commandline, "%*s %x %x", &addr, &data);
	  	  printf("addr = %x\ndata = %x\n", addr, data);
	  	  write_tca2_reg(addr, data);
	  }
	  else if(MyStrNCmp(commandline, "eepr", 4) == 0)
	  {
		  uint16_t addr;

	  	  sscanf(commandline, "%*s %x", &addr);
	  	  printf("Addr[%x] data[%x]\n",addr, read_eeprom(addr));
	  }
	  else if(MyStrNCmp(commandline, "eepw", 4) == 0)
	  {
		  uint16_t addr, data;

	  	  sscanf(commandline, "%*s %x %x", &addr, &data);
	  	  printf("addr = %x\ndata = %x\n", addr, data);
	  	  write_eeprom(addr, data);
	  }
	  else if(MyStrNCmp(commandline, "scan", 4) == 0)
	  {
		  uint16_t data1, data2, data3;

	  	  sscanf(commandline, "%*s %d %d %d", &data1, &data2, &data3);
	  	  printf("data1 = %x\ndata2 = %x\ndata3 = %x\n", data1, data2, data3);
	  }
	  else
	  {
	  	  printf("command error\n");
	  }

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
