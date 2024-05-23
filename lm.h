#ifndef LM_H_
#define LM_H_

#include "std_types.h"

#define SENSOR_CHANNEL_ID 0
// 0 -> 150  150*10mv = 1.5v
#define SENSOR_MAX_VOLT 1.5
#define SENSOR_MAX_TEMP 150

uint8 LM35_getTemp(void);

#endif /* LM_H_ */
