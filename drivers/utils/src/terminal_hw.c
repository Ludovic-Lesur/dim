/*
 * terminal_hw.c
 *
 *  Created on: 29 sep. 2024
 *      Author: Ludo
 */

#include "terminal_hw.h"

#ifndef EMBEDDED_UTILS_DISABLE_FLAGS_FILE
#include "embedded_utils_flags.h"
#endif
#include "error.h"
#include "gpio_mapping.h"
#include "lmac.h"
#include "nvic_priority.h"
#include "terminal_instance.h"
#include "types.h"
#include "usart.h"

#if (!(defined EMBEDDED_UTILS_TERMINAL_DRIVER_DISABLE) && (EMBEDDED_UTILS_TERMINAL_INSTANCES_NUMBER > 0))

#define TERMINAL_HW_USART_INSTANCE      USART_INSTANCE_USART2

/*** TERMINAL HW functions ***/

/*******************************************************************/
TERMINAL_status_t TERMINAL_HW_init(uint8_t instance, uint32_t baud_rate, TERMINAL_rx_irq_cb_t rx_irq_callback) {
    // Local variables.
    TERMINAL_status_t status = TERMINAL_SUCCESS;
    LMAC_status_t lmac_status = LMAC_SUCCESS;
    USART_status_t usart_status = USART_SUCCESS;
    USART_configuration_t usart_config;
    // Check instance.
    switch (instance) {
    case TERMINAL_INSTANCE_LMAC:
        lmac_status = LMAC_init(baud_rate, rx_irq_callback);
        LMAC_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
        break;
    case TERMINAL_INSTANCE_CLI:
        // Init USART.
        usart_config.baud_rate = baud_rate;
        usart_config.nvic_priority = NVIC_PRIORITY_CLI;
        usart_config.rxne_callback = rx_irq_callback;
        usart_status = USART_init(TERMINAL_HW_USART_INSTANCE, &GPIO_AT_USART, &usart_config);
        USART_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
        break;
    default:
        status = TERMINAL_ERROR_INSTANCE;
        goto errors;
    }
errors:
    return status;
}

/*******************************************************************/
TERMINAL_status_t TERMINAL_HW_de_init(uint8_t instance) {
    // Local variables.
    TERMINAL_status_t status = TERMINAL_SUCCESS;
    LMAC_status_t lmac_status = LMAC_SUCCESS;
    USART_status_t usart_status = USART_SUCCESS;
    // Check instance.
    switch (instance) {
    case TERMINAL_INSTANCE_LMAC:
        lmac_status = LMAC_de_init();
        LMAC_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
        break;
    case TERMINAL_INSTANCE_CLI:
        // Release USART.
       usart_status = USART_de_init(TERMINAL_HW_USART_INSTANCE, &GPIO_AT_USART);
       USART_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
       break;
    default:
        status = TERMINAL_ERROR_INSTANCE;
        goto errors;
    }
errors:
    return status;
}

/*******************************************************************/
TERMINAL_status_t TERMINAL_HW_enable_rx(uint8_t instance) {
    // Local variables.
    TERMINAL_status_t status = TERMINAL_SUCCESS;
    LMAC_status_t lmac_status = LMAC_SUCCESS;
    USART_status_t usart_status = USART_SUCCESS;
    // Check instance.
    switch (instance) {
    case TERMINAL_INSTANCE_LMAC:
        lmac_status = LMAC_enable_rx();
        LMAC_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
        break;
    case TERMINAL_INSTANCE_CLI:
        // Release USART.
       usart_status = USART_enable_rx(TERMINAL_HW_USART_INSTANCE);
       USART_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
       break;
    default:
        status = TERMINAL_ERROR_INSTANCE;
        goto errors;
    }
errors:
    return status;
}

/*******************************************************************/
TERMINAL_status_t TERMINAL_HW_disable_rx(uint8_t instance) {
    // Local variables.
    TERMINAL_status_t status = TERMINAL_SUCCESS;
    LMAC_status_t lmac_status = LMAC_SUCCESS;
    USART_status_t usart_status = USART_SUCCESS;
    // Check instance.
    switch (instance) {
    case TERMINAL_INSTANCE_LMAC:
        lmac_status = LMAC_disable_rx();
        LMAC_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
        break;
    case TERMINAL_INSTANCE_CLI:
        // Release USART.
       usart_status = USART_disable_rx(TERMINAL_HW_USART_INSTANCE);
       USART_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
       break;
    default:
        status = TERMINAL_ERROR_INSTANCE;
        goto errors;
    }
errors:
    return status;
}

/*******************************************************************/
TERMINAL_status_t TERMINAL_HW_write(uint8_t instance, uint8_t* data, uint32_t data_size_bytes) {
    // Local variables.
    TERMINAL_status_t status = TERMINAL_SUCCESS;
    LMAC_status_t lmac_status = LMAC_SUCCESS;
    USART_status_t usart_status = USART_SUCCESS;
    // Check instance.
    switch (instance) {
    case TERMINAL_INSTANCE_LMAC:
        lmac_status = LMAC_write(data, data_size_bytes);
        LMAC_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
        break;
    case TERMINAL_INSTANCE_CLI:
        // Release USART.
       usart_status = USART_write(TERMINAL_HW_USART_INSTANCE, data, data_size_bytes);
       USART_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
       break;
    default:
        status = TERMINAL_ERROR_INSTANCE;
        goto errors;
    }
errors:
    return status;
}

#ifdef EMBEDDED_UTILS_TERMINAL_MODE_BUS
/*******************************************************************/
TERMINAL_status_t TERMINAL_HW_set_destination_address(uint8_t instance, uint8_t destination_address) {
    // Local variables.
    TERMINAL_status_t status = TERMINAL_SUCCESS;
    LMAC_status_t lmac_status = LMAC_SUCCESS;
    // Check instance.
    if (instance == TERMINAL_INSTANCE_LMAC) {
        lmac_status = LMAC_set_destination_address(destination_address);
        LMAC_exit_error(TERMINAL_ERROR_BASE_HW_INTERFACE);
    }
    else {
        status = TERMINAL_ERROR_INSTANCE;
        goto errors;
    }
errors:
    return status;
}
#endif

#endif /* EMBEDDED_UTILS_TERMINAL_DRIVER_DISABLE */
