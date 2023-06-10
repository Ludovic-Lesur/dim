/*
 * node.h
 *
 *  Created on: 18 Feb. 2023
 *      Author: Ludo
 */

#ifndef __NODE_H__
#define __NODE_H__

#include "dinfox_common.h"
#include "lptim.h"
#include "lpuart.h"
#include "node_common.h"
#include "string.h"
#include "types.h"

/*** NODES macros ***/

#define NODES_LIST_SIZE_MAX		32

/*** NODE structures ***/

typedef enum {
	NODE_SUCCESS = 0,
	NODE_ERROR_NOT_SUPPORTED,
	NODE_ERROR_NULL_PARAMETER,
	NODE_ERROR_PROTOCOL,
	NODE_ERROR_NODE_ADDRESS,
	NODE_ERROR_REGISTER_ADDRESS,
	NODE_ERROR_REGISTER_FORMAT,
	NODE_ERROR_STRING_DATA_INDEX,
	NODE_ERROR_REPLY_TYPE,
	NODE_ERROR_ACCESS,
	NODE_ERROR_NONE_RADIO_MODULE,
	NODE_ERROR_SIGFOX_PAYLOAD_TYPE,
	NODE_ERROR_SIGFOX_PAYLOAD_EMPTY,
	NODE_ERROR_SIGFOX_LOOP,
	NODE_ERROR_SIGFOX_SEND,
	NODE_ERROR_DOWNLINK_NODE_ADDRESS,
	NODE_ERROR_DOWNLINK_BOARD_ID,
	NODE_ERROR_DOWNLINK_OPERATION_CODE,
	NODE_ERROR_ACTION_INDEX,
	NODE_ERROR_LBUS_MODE,
	NODE_ERROR_BASE_LPUART = 0x0100,
	NODE_ERROR_BASE_LPTIM = (NODE_ERROR_BASE_LPUART + LPUART_ERROR_BASE_LAST),
	NODE_ERROR_BASE_STRING = (NODE_ERROR_BASE_LPTIM + LPTIM_ERROR_BASE_LAST),
	NODE_ERROR_BASE_LAST = (NODE_ERROR_BASE_STRING + STRING_ERROR_BASE_LAST)
} NODE_status_t;

typedef struct {
	NODE_t list[NODES_LIST_SIZE_MAX];
	uint8_t count;
} NODE_list_t;

/*** NODES global variables ***/

NODE_list_t NODES_LIST;

/*** NODE functions ***/

void NODE_init(void);
NODE_status_t NODE_set_protocol(NODE_protocol_t protocol);
NODE_status_t NODE_scan(void);
NODE_status_t NODE_send_command(NODE_command_parameters_t* command_params);

#define NODE_status_check(error_base) { if (node_status != NODE_SUCCESS) { status = error_base + node_status; goto errors; }}
#define NODE_error_check() { ERROR_status_check(node_status, NODE_SUCCESS, ERROR_BASE_NODE); }
#define NODE_error_check_print() { ERROR_status_check_print(node_status, NODE_SUCCESS, ERROR_BASE_NODE); }

#endif /* __NODE_H__ */
