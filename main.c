#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "INT_interface.h"
#include "adc.h"
#include "common_macros.h"
#include "gpio.h"
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "lm.h"
#include "functions.h"

boolean isrFlag = FALSE;
boolean system_on = FALSE;

int main()
{
	/******Initializations******/
	LCD_init();
	ADC_init();
	INT2_VidInit();
	GIE_VidEnable();
	GPIO_setupPinDirection(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(RED_LED_PORT_ID, RED_LED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(SERVO_PORT_ID, SERVO_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(OFF_PORT_ID, OFF_PIN_ID, PIN_INPUT);
	GPIO_writePin(OFF_PORT_ID, OFF_PIN_ID, LOGIC_LOW);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
	uint8 pass[4], key,i;

	/******PROGRAM******/
	while(1)
	{
		reset:
		LCD_clearScreen();
		LCD_displayString("Air Conditioning");
		LCD_displayStringRowColumn(1, 0, "Enter pass:");
		i = 4;
		while(i != 0)
		{
			key = KEYPAD_getPressedKey();
			pass[4-i] = key;
			LCD_moveCursor(1, (11 + 4 - i));
			LCD_intgerToString(key);
			--i;
		}
		_delay_ms(1000);
		LCD_clearScreen();
		for(uint8 i = 0; i<4; ++i)
		{
			if(pass[i] != i+1)
			{
				LCD_displayStringRowColumn(0 , 1, "Pass is wrong!");
				alarm_on();
				goto reset;
			}
		}
		while(1)
		{
			system_on = TRUE;
			GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
			LCD_displayStringRowColumn(0, 2, "System is on");
			LCD_displayStringRowColumn(1, 0, "Temp:");
			uint8 temp = LM35_getTemp();
			LCD_moveCursor(1, 5);
			LCD_intgerToString(temp);
			if(temp <= 27)
				pwm_timer0(0);
			else if(temp <= 40)
				pwm_timer0(166);
			else if(temp <= 50)
				pwm_timer0(207);
			else
				pwm_timer0(255);
			if(isrFlag)
			{
				pwm_timer0(0);
				isrFlag = FALSE;
				system_on = FALSE;
				goto reset;
			}
		}
	}
	return 0;
}

ISR(INT2_vect)
{
	if(system_on)
	{
		isrFlag = TRUE;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 1, "System is off!");
		LCD_displayStringRowColumn(1, 4, "Good bye");
		pwm_timer0(0);
		GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
		GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
		timer_delay(3);
		GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
	}
}
