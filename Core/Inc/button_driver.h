/*
 * button_driver.h
 *
 *  Created on: Aug 8, 2024
 *      Author: faruk
 */

#ifndef INC_BUTTON_DRIVER_H_
#define INC_BUTTON_DRIVER_H_

#include <stdint.h>

#define BUTTON_ON 1
#define BUTTON_OFF 0

void button_init(void);
int32_t button_get_state(void);


#endif /* INC_BUTTON_DRIVER_H_ */
