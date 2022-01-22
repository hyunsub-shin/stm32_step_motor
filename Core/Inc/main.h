/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define U_LIMIT_Pin GPIO_PIN_13
#define U_LIMIT_GPIO_Port GPIOC
#define U_LIMIT_EXTI_IRQn EXTI15_10_IRQn
#define STATUS0_Pin GPIO_PIN_14
#define STATUS0_GPIO_Port GPIOC
#define STATUS1_Pin GPIO_PIN_15
#define STATUS1_GPIO_Port GPIOC
#define M_DEC0_Pin GPIO_PIN_0
#define M_DEC0_GPIO_Port GPIOC
#define M_DEC1_Pin GPIO_PIN_1
#define M_DEC1_GPIO_Port GPIOC
#define M_FAULTn_Pin GPIO_PIN_2
#define M_FAULTn_GPIO_Port GPIOC
#define M_nSLEEP_Pin GPIO_PIN_3
#define M_nSLEEP_GPIO_Port GPIOC
#define ADC_POSITION_Pin GPIO_PIN_1
#define ADC_POSITION_GPIO_Port GPIOA
#define DAC_OUT1_Pin GPIO_PIN_4
#define DAC_OUT1_GPIO_Port GPIOA
#define M_EN_Pin GPIO_PIN_4
#define M_EN_GPIO_Port GPIOC
#define M_M0_Pin GPIO_PIN_5
#define M_M0_GPIO_Port GPIOC
#define MEMS_INT1_Pin GPIO_PIN_0
#define MEMS_INT1_GPIO_Port GPIOB
#define MEMS_INT1_EXTI_IRQn EXTI0_IRQn
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOB
#define MEMS_INT2_EXTI_IRQn EXTI1_IRQn
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define M_M1_Pin GPIO_PIN_6
#define M_M1_GPIO_Port GPIOC
#define M_DIR_Pin GPIO_PIN_7
#define M_DIR_GPIO_Port GPIOC
#define M_STEP_Pin GPIO_PIN_8
#define M_STEP_GPIO_Port GPIOC
#define M_TRQ0_Pin GPIO_PIN_9
#define M_TRQ0_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define M_ATE_Pin GPIO_PIN_15
#define M_ATE_GPIO_Port GPIOA
#define M_TRQ1_Pin GPIO_PIN_10
#define M_TRQ1_GPIO_Port GPIOC
#define CART_nDET_Pin GPIO_PIN_11
#define CART_nDET_GPIO_Port GPIOC
#define L_LIMIT_Pin GPIO_PIN_12
#define L_LIMIT_GPIO_Port GPIOC
#define L_LIMIT_EXTI_IRQn EXTI15_10_IRQn
#define SHOT_SWn_Pin GPIO_PIN_2
#define SHOT_SWn_GPIO_Port GPIOD
#define SHOT_SWn_EXTI_IRQn EXTI2_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
