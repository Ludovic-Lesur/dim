/*
 * usart.c
 *
 *  Created on: 25 oct. 2022
 *      Author: Ludo
 */

#include "usart.h"

#include "at_usb.h"
#include "gpio.h"
#include "lptim.h"
#include "mapping.h"
#include "nvic.h"
#include "rcc.h"
#include "rcc_reg.h"
#include "usart_reg.h"
#include "types.h"

/*** USART local macros ***/

#define USART_BAUD_RATE			9600
#define USART_TIMEOUT_COUNT		100000
#define USART_STRING_SIZE_MAX	1000

/*** USART local functions ***/

/* USART2 INTERRUPT HANDLER.
 * @param:	None.
 * @return:	None.
 */
void __attribute__((optimize("-O0"))) USART2_IRQHandler(void) {
	// RXNE interrupt.
	if (((USART2 -> ISR) & (0b1 << 5)) != 0) {
		// Transmit incoming byte to AT command manager.
		AT_USB_fill_rx_buffer(USART2 -> RDR);
		// Clear RXNE flag.
		USART2 -> RQR |= (0b1 << 3);
	}
	// Overrun error interrupt.
	if (((USART2 -> ISR) & (0b1 << 3)) != 0) {
		// Clear ORE flag.
		USART2 -> ICR |= (0b1 << 3);
	}
}

/* FILL USART TX BUFFER WITH A NEW BYTE.
 * @param tx_byte:	Byte to append.
 * @return status:	Function execution status.
 */
static USART_status_t _USART2_fill_tx_buffer(uint8_t tx_byte) {
	// Local variables.
	USART_status_t status = USART_SUCCESS;
	uint32_t loop_count = 0;
	// Fill transmit register.
	USART2 -> TDR = tx_byte;
	// Wait for transmission to complete.
	while (((USART2 -> ISR) & (0b1 << 7)) == 0) {
		// Wait for TXE='1' or timeout.
		loop_count++;
		if (loop_count > USART_TIMEOUT_COUNT) {
			status = USART_ERROR_TX_TIMEOUT;
			goto errors;
		}
	}
errors:
	return status;
}

/*** USART functions ***/

/* CONFIGURE USART2 PERIPHERAL.
 * @param:	None.
 * @return:	None.
 */
void USART2_init(void) {
	// Enable peripheral clock.
	RCC -> CR |= (0b1 << 1); // Enable HSI in stop mode (HSI16KERON='1').
	RCC -> CCIPR |= (0b10 << 2); // Select HSI as USART clock.
	RCC -> APB1ENR |= (0b1 << 17); // USART2EN='1'.
	RCC -> APB1SMENR |= (0b1 << 17); // Enable clock in sleep mode.
	// Configure TX and RX GPIOs.
	GPIO_configure(&GPIO_USART2_TX, GPIO_MODE_ALTERNATE_FUNCTION, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_HIGH, GPIO_PULL_NONE);
	GPIO_configure(&GPIO_USART2_RX, GPIO_MODE_ALTERNATE_FUNCTION, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_HIGH, GPIO_PULL_NONE);
	// Configure peripheral.
	USART2 -> CR3 |= (0b1 << 12) | (0b1 << 23); // No overrun detection (OVRDIS='1') and clock enable in stop mode (UCESM='1').
	USART2 -> BRR = ((RCC_HSI_FREQUENCY_KHZ * 1000) / (USART_BAUD_RATE)); // BRR = (fCK)/(baud rate). See p.730 of RM0377 datasheet.
	// Enable transmitter and receiver.
	USART2 -> CR1 |= (0b1 << 5) | (0b11 << 2); // TE='1', RE='1' and RXNEIE='1'.
	// Set interrupt priority.
	NVIC_set_priority(NVIC_INTERRUPT_USART2, 3);
	// Enable peripheral.
	USART2 -> CR1 |= (0b11 << 0);
}

/* ENABLE USART INTERRUPT.
 * @param:	None.
 * @return:	None.
 */
void USART2_enable_interrupt(void) {
	// Clear flag and enable interrupt.
	USART2 -> RQR |= (0b1 << 3);
	NVIC_enable_interrupt(NVIC_INTERRUPT_USART2);
}

/* DISABLE USART INTERRUPT.
 * @param:	None.
 * @return:	None.
 */
void USART2_disable_interrupt(void) {
	// Disable interrupt.
	NVIC_disable_interrupt(NVIC_INTERRUPT_USART2);
}

/* SEND A BYTE ARRAY THROUGH USART2.
 * @param tx_string:	Byte array to send.
 * @return status:		Function execution status.
 */
USART_status_t USART2_send_string(char_t* tx_string) {
	// Local variables.
	USART_status_t status = USART_SUCCESS;
	uint32_t char_count = 0;
	// Check parameter.
	if (tx_string == NULL) {
		status = USART_ERROR_NULL_PARAMETER;
		goto errors;
	}
	// Loop on all characters.
	while (*tx_string) {
		// Fill TX buffer with new byte.
		status = _USART2_fill_tx_buffer((uint8_t) *(tx_string++));
		if (status != USART_SUCCESS) goto errors;
		// Check character count.
		char_count++;
		if (char_count > USART_STRING_SIZE_MAX) {
			status = USART_ERROR_STRING_SIZE;
			break;
		}
	}
errors:
	return status;
}
