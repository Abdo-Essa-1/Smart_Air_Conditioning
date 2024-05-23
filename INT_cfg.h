#define FALLING_EDGE 0
#define RISING_EDGE 1
#define INT2_SENSE_CONTROL RISING_EDGE


#define SREG *((uint8*)0x5F)
void __vector_1(void)  __attribute__((signal));
