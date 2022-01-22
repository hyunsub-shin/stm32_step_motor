/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN Private defines */
#define AT24C_ADDR	0x50<<1
#define TCA9539_1	0x74<<1
#define TCA9539_2	0x75<<1

#define Contrl_Reg0	0x00
#define Contrl_Reg1	0x01
#define Contrl_Reg2	0x02
#define Contrl_Reg3	0x03
#define Contrl_Reg4	0x04
#define Contrl_Reg5	0x05
#define Contrl_Reg6	0x06
#define Contrl_Reg7	0x07
/* USER CODE END Private defines */

void MX_I2C1_Init(void);
void MX_I2C2_Init(void);

/* USER CODE BEGIN Prototypes */
uint16_t read_tca1_reg(uint16_t reg_addr);
uint16_t write_tca1_reg(uint16_t reg_addr, uint16_t data);
uint16_t read_tca2_reg(uint16_t reg_addr);
uint16_t write_tca2_reg(uint16_t reg_addr, uint16_t data);
uint16_t read_eeprom(uint16_t addr);
uint16_t write_eeprom(uint16_t addr, uint16_t data);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
