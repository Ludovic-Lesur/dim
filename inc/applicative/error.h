/*
 * error.h
 *
 *  Created on: 12 mar. 2022
 *      Author: Ludo
 */

#ifndef __ERROR_H__
#define __ERROR_H__

// Peripherals.
#include "adc.h"
#include "iwdg.h"
#include "lptim.h"
#include "lpuart.h"
#include "nvm.h"
#include "rcc.h"
#include "rtc.h"
#include "usart.h"
// Utils.
#include "math.h"
#include "parser.h"
#include "string.h"
// Components.
#include "power.h"
// Nodes.
#include "lbus.h"
#include "node.h"

/*!******************************************************************
 * \enum ERROR_base_t
 * \brief Board error bases.
 *******************************************************************/
typedef enum {
	SUCCESS = 0,
	ERROR_TX_DISABLED,
	// Peripherals.
	ERROR_BASE_ADC1 = 0x0100,
	ERROR_BASE_FLASH = (ERROR_BASE_ADC1 + ADC_ERROR_BASE_LAST),
	ERROR_BASE_IWDG = (ERROR_BASE_FLASH + FLASH_ERROR_BASE_LAST),
	ERROR_BASE_LPTIM1 = (ERROR_BASE_IWDG + IWDG_ERROR_BASE_LAST),
	ERROR_BASE_LPUART1 = (ERROR_BASE_LPTIM1 + LPTIM_ERROR_BASE_LAST),
	ERROR_BASE_NVM = (ERROR_BASE_LPUART1 + LPUART_ERROR_BASE_LAST),
	ERROR_BASE_RCC = (ERROR_BASE_NVM + NVM_ERROR_BASE_LAST),
	ERROR_BASE_RTC = (ERROR_BASE_RCC + RCC_ERROR_BASE_LAST),
	ERROR_BASE_USART2 = (ERROR_BASE_RTC + RTC_ERROR_BASE_LAST),
	// Utils.
	ERROR_BASE_MATH = (ERROR_BASE_USART2 + USART_ERROR_BASE_LAST),
	ERROR_BASE_PARSER = (ERROR_BASE_MATH + MATH_ERROR_BASE_LAST),
	ERROR_BASE_STRING = (ERROR_BASE_PARSER + PARSER_ERROR_BASE_LAST),
	// Components.
	ERROR_BASE_POWER = (ERROR_BASE_STRING + STRING_ERROR_BASE_LAST),
	// Nodes.
	ERROR_BASE_NODE = (ERROR_BASE_POWER + POWER_ERROR_BASE_LAST),
	// Last index.
	ERROR_BASE_LAST = (ERROR_BASE_NODE + NODE_ERROR_BASE_LAST)
} ERROR_base_t;

/*!******************************************************************
 * \enum ERROR_code_t
 * \brief Board error code type.
 *******************************************************************/
typedef uint16_t ERROR_code_t;

/*** ERROR functions ***/

/*!******************************************************************
 * \fn void ERROR_stack_init(void)
 * \brief Init error stack.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		none
 *******************************************************************/
void ERROR_stack_init(void);

/*!******************************************************************
 * \fn void ERROR_stack_add(ERROR_code_t code)
 * \brief Add error to stack.
 * \param[in]  	code: Error to stack.
 * \param[out] 	none
 * \retval		none
 *******************************************************************/
void ERROR_stack_add(ERROR_code_t code);

/*!******************************************************************
 * \fn ERROR_code_t ERROR_stack_read(void)
 * \brief Read error stack.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Last error code stored.
 *******************************************************************/
ERROR_code_t ERROR_stack_read(void);

/*!******************************************************************
 * \fn uint8_t ERROR_stack_is_empty(void)
 * \brief Check if error stack is empty.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		1 if the error stack is empty, 0 otherwise.
 *******************************************************************/
uint8_t ERROR_stack_is_empty(void);

#endif /* __ERROR_H__ */
