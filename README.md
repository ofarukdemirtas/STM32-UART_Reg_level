STM32 UART Library
==================

This is a custom UART communication library for STM32F4 microcontrollers, designed to handle basic UART transmission and reception using the USART2 peripheral on pins PA2 (TX) and PA3 (RX).

Features
--------

-   **UART Initialization**: Set up and configure the UART peripheral with a user-defined baud rate.
-   **UART Transmit**: Send individual characters or strings over UART.
-   **UART Receive**: Receive individual characters or strings over UART.
-   **Dynamic Memory Allocation**: Dynamically allocate memory for received strings.

Requirements
------------

-   STM32F4xx microcontroller
-   STM32CubeIDE or any ARM GCC compiler toolchain
-   ARM CMSIS and STM32 HAL libraries

Pin Configuration
-----------------

This library uses **USART2** with the following pin mappings:

-   **PA2** (Alternate Function 7): UART2 TX (Transmit)
-   **PA3** (Alternate Function 7): UART2 RX (Receive)

Usage
-----

### 1\. Clone the Repository

`git clone https://github.com/yourusername/stm32-uart-library.git`

### 2\. Include the Files

Include the `my_UART.c` and `my_UART.h` files in your STM32 project.

### 3\. Initialize UART

Before using UART, make sure to initialize it in your `main.c` file:

`int main(void) {
    // System initialization code here

    UART_Init();  // Initialize the UART

    while (1) {
        // Your application code here
    }
}
`

### 4\. Sending Data

You can send characters or strings over UART with the following functions:

`uart_send_char('A');           // Send a single character
uart_send_string("Hello!\n");   // Send a string`

### 5\. Receiving Data

You can receive characters or strings over UART with dynamic memory allocation:

`char *received_string = uart_receive_dynamic_string();   // Receive a string dynamically
uart_send_string(received_string);  // Send the received string back
free(received_string);  // Free the dynamically allocated memory`

### 6\. Customizing the Baud Rate

You can set the baud rate of UART by modifying the `UART_BAUDRATE` define in `my_UART.c`:


`#define UART_BAUDRATE 9600  // Default baud rate is 9600`

### Example

In the main loop, the library can send and receive data like this:



`int main(void) {
    SysClockConfig();
    UART_Init();  // Initialize UART

    while (1) {
        char *received_data = uart_receive_dynamic_string();  // Receive data dynamically
        uart_send_string("Received: ");
        uart_send_string(received_data);  // Echo the received string back
        free(received_data);  // Free the memory allocated for the received string
    }
}
`

Function Descriptions
---------------------

-   **UART_Init()**: Initializes UART with the configured baud rate, word length, and enables the UART peripheral.
-   **uart_send_char(char c)**: Sends a single character via UART.
-   **uart_send_string(char *str)**: Sends a null-terminated string via UART.
-   **uart_receive_char()**: Receives a single character from UART.
-   **uart_receive_dynamic_string()**: Receives a string of unknown length dynamically (allocates memory for it).

License
-------

This project is licensed under the MIT License - see the <LICENSE> file for details.

Contributing
------------

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
