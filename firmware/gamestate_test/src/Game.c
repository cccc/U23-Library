#include <game/Game.h>
#include <game/Debug.h>
#include <game/Filesystem.h>
#include <game/Font.h>
#include <serencode.h>

#include <stdio.h>
#include <string.h>

void Init(struct Gamestate*);
void OnEnter(struct Gamestate*);
void OnLeave(struct Gamestate*);
void Update(uint32_t);
void Draw(Bitmap* surface);

Gamestate InitState = { Init, OnEnter, OnLeave, Update, Draw };
extern Gamestate RedState;
Game* TheGame = &(Game) {&InitState};

void Init(struct Gamestate* state)
{
	EnableDebugOutput(DEBUG_USART);
	printf("Init State\r\n");
}

void OnEnter(struct Gamestate* state)
{
	setFont(fontblack8);
}

void OnLeave(struct Gamestate* state)
{
	setFont(fontwhite8);
}

int myframe = 0;

void Update(uint32_t delta)
{
	static uint8_t cycle = 0;
	printf("Soll: %d\r\n", cycle);
	snes_button_state_t state = GetControllerState1();
	myframe++;
	if (state.buttons.Up)
		ChangeState(&RedState);
	if (state.buttons.Down)
	{
		RumbleSetDutyCycle(cycle);
		printf("Soll: %d\r\n", cycle);
		cycle++;
		cycle = cycle % 100;
	}

	se_start_frame(4);
	se_puti16(cycle);
	se_puti16(RumbleCounter);
}

void Draw(Bitmap* surface)
{
	ClearBitmap(surface);
	DrawFilledRectangle(surface, 30, 30, 100, 100, RGB(0,myframe%256,0));
	setFont(fontwhite16);
	DrawText(surface, "TEST\nBLA", 10, 10);
	setFont(fontblack8);
	DrawText(surface, "TEST", 10, 30);
}
