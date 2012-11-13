#include <platform/Rumble.h>
#include <stdio.h>

uint8_t _dutyCycle = 0;
uint8_t RumbleCounter = 0;

void InitializeRumble()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(GPIO_RUMBLE_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_RUMBLE_PIN;

	GPIO_Init(GPIO_RUMBLE_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(GPIO_RUMBLE_PORT, GPIO_RUMBLE_PIN);
}

void RumbleSetDutyCycle(uint8_t dutycycle)
{
	_dutyCycle = dutycycle;
}

void EnableRumble()
{
	GPIO_SetBits(GPIO_RUMBLE_PORT, GPIO_RUMBLE_PIN);
}

void DisableRumble()
{
	GPIO_ResetBits(GPIO_RUMBLE_PORT, GPIO_RUMBLE_PIN);
}

void HandleRumbleTimerIRQ() {
	if (_dutyCycle >= 0)
	{
		if (_dutyCycle > 100) {
			_dutyCycle = 100;
		}

		if (_dutyCycle > RumbleCounter) {
			GPIO_SetBits(GPIO_RUMBLE_PORT, GPIO_RUMBLE_PIN);
		} else {
		 	GPIO_ResetBits(GPIO_RUMBLE_PORT, GPIO_RUMBLE_PIN);
		}

		RumbleCounter++;
		RumbleCounter % 100;
	}
}