#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"std_types.h"
#include "INT_cfg.h"
#include "INT_interface.h"
#include "gpio.h"
#include "common_macros.h"
#include "lcd.h"
#include "functions.h"

void INT2_VidInit()
{

#if INT2_SENSE_CONTROL==FALLING_EDGE
	CLEAR_BIT(MCUCSR,6);

#elif INT2_SENSE_CONTROL==RISING_EDGE
	SET_BIT(MCUCSR,6);

#endif
	/*Enable External Interrupt Request 2 */
	SET_BIT(GICR,5);
}

/*Function to enable the general interrupt*/
void GIE_VidEnable()
{
	SET_BIT(SREG,7);
}
/*Function to disable the general interrupt*/
void GIE_vidDisable ()
{
	CLEAR_BIT(SREG,7);
}
/*Interrupt service routine for INT2*/
