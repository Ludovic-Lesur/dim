/*
 * pwr.h
 *
 *  Created on: 25 oct. 2022
 *      Author: Ludo
 */

#ifndef __PWR_H__
#define __PWR_H__

/*** PWR functions ***/

void PWR_init(void);
void PWR_enter_sleep_mode(void);
void PWR_enter_stop_mode(void);
void PWR_software_reset(void);

#endif /* __PWR_H__ */
