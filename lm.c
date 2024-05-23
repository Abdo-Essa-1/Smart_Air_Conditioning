
#include "lm.h"
#include "adc.h"

uint8 LM35_getTemp(void)
{
	uint8 temperature = 0;
	uint16 adc_value = 0;

	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);
	temperature = ((uint32) adc_value * 500 / 1023.0);

	return temperature;
}
