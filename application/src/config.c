/*
 * config.c
 *
 *  Created on: 30 oct. 2022
 *      Author: Ludo
 */

#include "config.h"

#include "gpio.h"
#include "lptim.h"
#include "mapping.h"

/*** CONFIG local macros ***/

#define GPIO_TX_MODE	GPIO_MODE0

/*** CONFIG functions ***/

/*******************************************************************/
CONFIG_tx_mode_t CONFIG_get_tx_mode(void) {
	// Local variables.
	CONFIG_tx_mode_t tx_mode = CONFIG_TX_DISABLED;
	// Activate pull up.
	GPIO_configure(&GPIO_TX_MODE, GPIO_MODE_INPUT, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_UP);
	LPTIM1_delay_milliseconds(100, 0);
	// Read GPIO.
	if (GPIO_read(&GPIO_TX_MODE) == 0) {
		tx_mode = CONFIG_TX_ENABLED;
	}
	// Disable pull-up.
	GPIO_configure(&GPIO_TX_MODE, GPIO_MODE_ANALOG, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE);
	// Return mode.
	return tx_mode;
}
