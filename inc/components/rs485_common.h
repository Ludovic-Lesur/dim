/*
 * rs485_common.h
 *
 *  Created on: 13 Nov. 2022
 *      Author: Ludo
 */

#ifndef __RS485_COMMON_H__
#define __RS485_COMMON_H__

#include "types.h"

/*** RS485 common macros ***/

// Addressing.
#define RS485_ADDRESS_MASK			0x7F
#define RS485_ADDRESS_LAST			RS485_ADDRESS_MASK
#define RS485_ADDRESS_SIZE_BYTES	1
// Framing.
#define RS485_FRAME_END				STRING_CHAR_CR

/*** RS485 common types ***/

typedef uint8_t	RS485_address_t;

typedef enum {
	RS485_MODE_DIRECT = 0,
	RS485_MODE_ADDRESSED,
	RS485_MODE_LAST
} RS485_mode_t;

typedef enum {
	RS485_FRAME_FIELD_INDEX_DESTINATION_ADDRESS = 0,
	RS485_FRAME_FIELD_INDEX_SOURCE_ADDRESS = (RS485_FRAME_FIELD_INDEX_DESTINATION_ADDRESS + RS485_ADDRESS_SIZE_BYTES),
	RS485_FRAME_FIELD_INDEX_DATA = (RS485_FRAME_FIELD_INDEX_SOURCE_ADDRESS + RS485_ADDRESS_SIZE_BYTES)
} RS485_frame_field_index_t;

typedef struct {
	RS485_address_t address;
	uint8_t board_id;
} RS485_node_t;

#endif /* __RS485_COMMON_H__ */
