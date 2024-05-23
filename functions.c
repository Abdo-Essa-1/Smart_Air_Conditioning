/*******************************************************************************
 *
 * functions.c
 *
 *  Created on: Apr 29, 2023
 *      Author: Abdo Essa
 *
 *******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>/* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "functions.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * If password is not correct light red led and buzzer for 5 sec using timer 0
 */
void alarm_on(void)
{
	GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
	timer_delay(5);
	alarm_off();
}

/*
 * Description :
 * turn off the red led and buzzer
 */
void alarm_off(void)
{
	GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

/*
 * Description :
 * the required delay time
 */
void timer_delay(uint8 t)
{
	uint8 overflow = 4 * t;
	label :
	TCCR0 =0 ; //initial values for all controls
	//	TCCR0 |= 0x05; //3ayz a5alle prescaling FCPU/1024, cs02 cs01 cs00 1 0 1
	//	TCCR0 &= ~(1<<WGM01) & ~(1<<WGM00);//normal mode
	//	TCCR0 |= (1<<FOC0); //non pwm
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
	while(!(TIFR &(1<<TOV0))); //Tool ma mafesh flag =1 , infinite loop (estanna) (polling)
	//tb lw 5allas w 3amal flag =1, keda ana 5alast overflow wa7d fe 1/4 sanya
	--overflow;

	TIFR |=(1<<TOV0); //lazm a clear el flag b 1
	TCNT0 =0; // Warg3 a3edd tany ml awl

	if(overflow != 0)
		goto label;
}

/*
 * Description :
 * adjust pwm to operate servo at suitable angle
 */
void pwm_timer0(uint8 pwm)
{
	TCCR0 = 0;
	TCNT0 = 0;
	TCCR0 = (1<<WGM01) | (1<<WGM00) |(1<<COM01) |(1<<CS01); //3ayz compare mode with pwm, prescaler 8
	OCR0 = pwm;
}
