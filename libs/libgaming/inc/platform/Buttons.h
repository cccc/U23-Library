#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <stm32f4xx/stm32f4xx.h>

void InitializeButtons(void);
uint32_t GetUserButtonState(void);

#endif
