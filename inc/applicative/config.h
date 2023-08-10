/*
 * config.h
 *
 *  Created on: 30 oct. 2022
 *      Author: Ludo
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/*** CONFIG structures ***/

/*!******************************************************************
 * \enum CONFIG_tx_mode_t
 * \brief Board TX modes.
 *******************************************************************/
typedef enum {
	CONFIG_TX_ENABLED,
	CONFIG_TX_DISABLED,
	CONFIG_TX_LAST
} CONFIG_tx_mode_t;

/*** CONFIG functions ***/

/*!******************************************************************
 * \fn CONFIG_tx_mode_t CONFIG_get_tx_mode(void)
 * \brief Get TX mode DIP switch configuration.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Current TX mode.
 *******************************************************************/
CONFIG_tx_mode_t CONFIG_get_tx_mode(void);

#endif /* __CONFIG_H__ */
