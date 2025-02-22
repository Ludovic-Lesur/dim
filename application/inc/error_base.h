/*
 * error.h
 *
 *  Created on: 12 mar. 2022
 *      Author: Ludo
 */

#ifndef __ERROR_BASE_H__
#define __ERROR_BASE_H__

// Peripherals.
#include "adc.h"
#include "flash.h"
#include "iwdg.h"
#include "lptim.h"
#include "lpuart.h"
#include "nvm.h"
#include "rcc.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
// Utils.
#include "math.h"
#include "parser.h"
#include "string.h"
// Middleware.
#include "analog.h"
#include "cli.h"
#include "power.h"
// Nodes.
#include "node.h"

/*!******************************************************************
 * \enum ERROR_base_t
 * \brief Board error bases.
 *******************************************************************/
typedef enum {
    SUCCESS = 0,
    // Peripherals.
    ERROR_BASE_ADC1 = 0x0100,
    ERROR_BASE_FLASH = (ERROR_BASE_ADC1 + ADC_ERROR_BASE_LAST),
    ERROR_BASE_IWDG = (ERROR_BASE_FLASH + FLASH_ERROR_BASE_LAST),
    ERROR_BASE_LPTIM = (ERROR_BASE_IWDG + IWDG_ERROR_BASE_LAST),
    ERROR_BASE_LPUART = (ERROR_BASE_LPTIM + LPTIM_ERROR_BASE_LAST),
    ERROR_BASE_NVM = (ERROR_BASE_LPUART + LPUART_ERROR_BASE_LAST),
    ERROR_BASE_RCC = (ERROR_BASE_NVM + NVM_ERROR_BASE_LAST),
    ERROR_BASE_RTC = (ERROR_BASE_RCC + RCC_ERROR_BASE_LAST),
    ERROR_BASE_TIM_CALIBRATION = (ERROR_BASE_RTC + RTC_ERROR_BASE_LAST),
    ERROR_BASE_USART_AT = (ERROR_BASE_TIM_CALIBRATION + TIM_ERROR_BASE_LAST),
    // Utils.
    ERROR_BASE_MATH = (ERROR_BASE_USART_AT + USART_ERROR_BASE_LAST),
    ERROR_BASE_PARSER = (ERROR_BASE_MATH + MATH_ERROR_BASE_LAST),
    ERROR_BASE_STRING = (ERROR_BASE_PARSER + PARSER_ERROR_BASE_LAST),
    // Middleware.
    ERROR_BASE_ANALOG = (ERROR_BASE_STRING + STRING_ERROR_BASE_LAST),
    ERROR_BASE_CLI = (ERROR_BASE_ANALOG + ANALOG_ERROR_BASE_LAST),
    ERROR_BASE_POWER = (ERROR_BASE_CLI + CLI_ERROR_BASE_LAST),
    // Nodes.
    ERROR_BASE_NODE = (ERROR_BASE_POWER + POWER_ERROR_BASE_LAST),
    // Last index.
    ERROR_BASE_LAST = (ERROR_BASE_NODE + NODE_ERROR_BASE_LAST)
} ERROR_base_t;

#endif /* __ERROR_BASE_H__ */
