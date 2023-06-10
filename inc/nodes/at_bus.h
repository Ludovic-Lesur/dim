/*
 * at_bus.h
 *
 *  Created on: 18 feb. 2023
 *      Author: Ludo
 */

#ifndef __AT_BUS_H__
#define __AT_BUS_H__

#include "node.h"
#include "types.h"

/*** AT BUS macros ***/

#define AT_BUS_DEFAULT_TIMEOUT_MS	100

/*** AT BUS functions ***/

void AT_BUS_init(void);
NODE_status_t AT_BUS_send_command(NODE_command_parameters_t* command_params);
NODE_status_t AT_BUS_scan(NODE_t* nodes_list, uint8_t nodes_list_size, uint8_t* nodes_count);
NODE_status_t AT_BUS_task(void);
void AT_BUS_fill_rx_buffer(uint8_t rx_byte);

#endif /* __AT_BUS_H__ */
