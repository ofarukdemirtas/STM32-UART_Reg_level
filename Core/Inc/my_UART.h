/*
 * my_UART.h
 *
 *  Created on: Aug 18, 2024
 *      Author: faruk
 */

#ifndef INC_MY_UART_H_
#define INC_MY_UART_H_


void UART_Init(void);
char uart_receive_char(void) ;
void uart_receive_string(char *buffer, int max_length) ;
void uart_send_string(char *str) ;
void uart_send_char(char c) ;

char* uart_receive_string_dynamic(void) ;

#endif /* INC_MY_UART_H_ */
