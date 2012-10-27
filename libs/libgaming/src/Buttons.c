#include <platform/Buttons.h>
#include <platform/SysTick.h>
#include <stm32f4xx/stm32f4xx_gpio.h>
#include <stm32f4xx/stm32f4xx_rcc.h>

void InitializeButtons(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Enable the GPIO_Button Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure the GPIO_LED pins */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
uint32_t GetUserButtonState(void)
{	
	uint32_t ButtonState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);	

	Delay(1);

	if(ButtonState == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
	{
		return ButtonState;
	}
	return !ButtonState; 
}