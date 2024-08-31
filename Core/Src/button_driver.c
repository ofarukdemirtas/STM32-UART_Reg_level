/*
 * button_driver.c
 *
 *  Created on: Aug 8, 2024
 *      Author: faruk
 */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "button_driver.h"

void button_init()
{
	//BUTTON ==>  GPIOC - 13. pin

	// Enable Clock
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// Select Mode: Input
	// Bit 26: 0
	// Bit 27: 0
	GPIOC->MODER   &= ~(3UL << 26);  // set 00 ==> Input

	// Pull-up pull-down
	// Bit 26: 0
	// Bit 27: 0
    GPIOC->PUPDR   &= ~(3UL << 26);  // 00 ==> // No pull-up, no pull-down

}
int32_t button_get_state(void)
{
	//BUTTON ==>  GPIOC - 13. pin
	if( ((GPIOC->IDR & (1<<13)) == 0 ))
	{
		return BUTTON_ON;
	}
	else
	{
		return BUTTON_OFF;
	}
}



