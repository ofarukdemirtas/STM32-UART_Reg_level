/*
 * my_UART.c
 *
 *  Created on: Aug 18, 2024
 *      Author: faruk
 */

#include "stm32f4xx.h"  // Include the header file for the STM32F4 series
#include <stdlib.h> // this is for realloc

#define UART_BAUDRATE 9600
#define UART_TX_PIN 2  // PA2 -> USART1_TX
#define UART_RX_PIN 3  // PA3 -> USART1_RX

void UART_Init(void) {
	  // Enable the clock for GPIOA
	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	    // Enable the clock for USART2
	   	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	    // Configure PA2 (USART2_TX) and PA3 (USART2_RX) in Alternate Function mode
	    GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);   // Clear mode
	    GPIOA->MODER |= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);  // Set to AF mode
	    GPIOA->AFR[0] |= (0x07 << 4*2) | (0x07 << 4*3); // AF7 for PA2 and PA3 (USART2)


    // Configure the baud rate
    USART2->BRR = 0x123F;  // BRR = (292 << 4) | 15

    // Configure word length
    USART2->CR1 &= ~USART_CR1_M;  // Clear the M bit for 8-bit word length
        // USART2->CR1 |= USART_CR1_M;  // Uncomment this line for 9-bit word length

        // Enable USART2, enable transmitter and receiver
        USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}



// Sending one Byte
void uart_send_char(char c) {
    while (!(USART2->SR & USART_SR_TXE));  // wait for flag
    USART2->DR = c;  // send data
}

// sending more than one byte actually string
void uart_send_string(char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}

// receiving one byte
char uart_receive_char(void) {
    while (!(USART2->SR & USART_SR_RXNE));  //wait for flag
    return USART2->DR;  // receive data
}

// receiving more than one byte with buffer
void uart_receive_string(char *buffer, int max_length) {
    int i = 0;
    char c;
    while (i < max_length - 1) {
        c = uart_receive_char();
        if (c == '\r' || c == '\n') break;  // stop receiving when click enter
        buffer[i++] = c;
    }
    buffer[i] = '\0';  //add null character at the end of the string
}
// receiving more than one byte with dyanamic buffer
char* uart_receive_string_dynamic(void) {
    char *buffer = NULL;
    int size = 0;
    char c;

    while (1) {
        //  receving one byte
       /* while (!(USART2->SR & USART_SR_RXNE));  //wait for flag
        c = USART2->DR;  // receive data */
    	c= uart_receive_char();
        if (c == '\r' || c == '\n') break;  // stop receiving when click enter

        // increase the cache size for each new character
        char *new_buffer = (char *)realloc(buffer, size + 1);
        if (new_buffer == NULL) {
            free(buffer);  // if there is error free the cache previous buffer
            return NULL;
        }

        buffer = new_buffer;
        buffer[size++] = c;
    }

    //add null character at the end of the string
    char *final_buffer = (char *)realloc(buffer, size + 1);
    if (final_buffer == NULL) {
        free(buffer);
        return NULL;
    }
    buffer = final_buffer;
    buffer[size] = '\0';

    return buffer;
}

