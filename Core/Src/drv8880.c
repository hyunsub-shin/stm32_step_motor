/*
 * drv8880.c
 *
 *  Created on: Dec 17, 2020
 *      Author: USER
 */

#include "main.h"
#include "drv8880.h"

uint8_t drv8880_state = 0;
volatile uint32_t step_cnt = 800;
volatile uint32_t shot_cnt = 1;
uint16_t accel_tbl[90] = {0};

void drv8880_init()
{
	// Smart Tune mode Enable
	HAL_GPIO_WritePin(M_ATE_GPIO_Port, M_ATE_Pin, GPIO_PIN_SET);

	// driver disable
	HAL_GPIO_WritePin(M_EN_GPIO_Port, M_EN_Pin, GPIO_PIN_RESET);

	// sleep mode
	HAL_GPIO_WritePin(M_nSLEEP_GPIO_Port, M_nSLEEP_Pin, GPIO_PIN_RESET);

	// Microstepping 1/4 step
	HAL_GPIO_WritePin(M_M0_GPIO_Port, M_M0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_M1_GPIO_Port, M_M1_Pin, GPIO_PIN_SET);

	// Torque 50%
	HAL_GPIO_WritePin(M_TRQ0_GPIO_Port, M_TRQ0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_TRQ1_GPIO_Port, M_TRQ1_Pin, GPIO_PIN_SET);

	// Decay Slow Mode // Mixed mode 30% Fast
	HAL_GPIO_WritePin(M_DEC0_GPIO_Port, M_DEC0_Pin, GPIO_PIN_RESET);//GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_DEC1_GPIO_Port, M_DEC1_Pin, GPIO_PIN_RESET);//GPIO_PIN_SET);

	// Motor Dir 0
	HAL_GPIO_WritePin(M_DIR_GPIO_Port, M_DIR_Pin, GPIO_PIN_RESET);

	for(int i=0;i<90;i++)
	{
		accel_tbl[i] = 1100+i*100;
//		printf("accel_tbl[i] = %d\n", accel_tbl[i]);
	}
}

void drv8880_enable()
{
	HAL_GPIO_WritePin(M_EN_GPIO_Port, M_EN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M_nSLEEP_GPIO_Port, M_nSLEEP_Pin, GPIO_PIN_SET);

	drv8880_state = 1;
}

void drv8880_disable()
{
	HAL_GPIO_WritePin(M_EN_GPIO_Port, M_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_nSLEEP_GPIO_Port, M_nSLEEP_Pin, GPIO_PIN_RESET);

	drv8880_state = 0;
}

void drv8880_dir(uint8_t dir)
{
	if(dir == 1)
	{
		HAL_GPIO_WritePin(M_DIR_GPIO_Port, M_DIR_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(M_DIR_GPIO_Port, M_DIR_Pin, GPIO_PIN_RESET);
	}
}

void drv8880_sleep(uint8_t status)
{
	if(status == 1)
	{
		HAL_GPIO_WritePin(M_nSLEEP_GPIO_Port, M_nSLEEP_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(M_nSLEEP_GPIO_Port, M_nSLEEP_Pin, GPIO_PIN_RESET);
	}
}
