#ifndef INT_INTERFACE_H_
#define INT_INTERFACE_H_

void INT2_VidInit();
void GIE_VidEnable();
void GIE_vidDisable ();
void INT2_Callback(void(*pfun)(void));

#endif /* INT_INTERFACE_H_ */
