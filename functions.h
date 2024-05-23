/*******************************************************************************
 *
 * functions.c
 *
 *  Created on: Apr 29, 2023
 *      Author: Abdo Essa
 *
 *******************************************************************************/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define GREEN_LED_PORT_ID              PORTA_ID
#define GREEN_LED_PIN_ID               PIN7_ID

#define RED_LED_PORT_ID                PORTB_ID
#define RED_LED_PIN_ID                 PIN6_ID

#define SERVO_PORT_ID                  PORTB_ID
#define SERVO_PIN_ID                   PIN3_ID

#define OFF_PORT_ID                    PORTB_ID
#define OFF_PIN_ID                     PIN2_ID

#define BUZZER_PORT_ID                 PORTB_ID
#define BUZZER_PIN_ID                  PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * If password is not correct light red led and buzzer for 5 sec using timer 0
 */
void alarm_on(void);

/*
 * Description :
 * turn off the red led and buzzer
 */
void alarm_off(void);

/*
 * Description :
 * the required delay time
 */
void timer_delay(uint8 t);

/*
 * Description :
 * adjust pwm to operate servo at suitable angle
 */
void pwm_timer0(uint8 pwm);

#endif /* FUNCTIONS_H_ */
