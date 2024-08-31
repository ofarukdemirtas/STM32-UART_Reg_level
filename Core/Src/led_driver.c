/*
 * led_driver.c
 *
 *  Created on: Aug 7, 2024
 *      Author: faruk
 */


#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void user_led_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Select mode
    GPIOA->MODER |= (1 << 10);  // Set the 10th bit to 1
    GPIOA->MODER &= ~(1 << 11) ; // Set the 11th bit to 0

    /* Select output Type -Push Pull
        0: Output push-pull (reset state)
        1: Output open-drain
        */
    GPIOA->OTYPER &= ~(1 << 5);

   /*  Select speed
        00: Low speed
        01: Medium speed
        10: Fast speed
        11: High speed */

    GPIOA->OSPEEDR &= ~(1 << 11); // Bit 11: 0
    GPIOA->OSPEEDR &= ~(1 << 10); // Bit 10: 0

}
void user_led_toggle()
{
	GPIOA->ODR ^= (1<<5); // xor process
}


void user_led_set()
{
	// Bit 5 : 1
	GPIOA->BSRR = (1<<5);
}

void user_led_reset()
{
	// Bit 5 : 1
	GPIOA->BSRR = (1<<21);
}
