/*
 * drv8880.h
 *
 *  Created on: Dec 17, 2020
 *      Author: USER
 */

#ifndef INC_DRV8880_H_
#define INC_DRV8880_H_


void drv8880_init();
void drv8880_enable();
void drv8880_disable();
void drv8880_dir(uint8_t dir);
void drv8880_sleep(uint8_t status);


#endif /* INC_DRV8880_H_ */
