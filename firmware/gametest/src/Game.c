#include <game/Game.h>
#include <game/Debug.h>
#include <game/Filesystem.h>

#include <stdio.h>
#include <string.h>

void Init(void);
void Update(uint32_t);
void Draw(void);

Game MyGame = { Init, Update, Draw };
Game* TheGame = &MyGame;

void Init()
{
	EnableDebugOutput(DEBUG_USART);
	printf("Init\r\n");

	InitializeFilesystem();

	//Open a file
	FILE* file = fopen("0:TESTFILE", "w+");
	if(!file) {
		perror("fopen()");
		goto fs_err;
	}
	printf("opened file: %x\r\n", (uint32_t)file);

	//Write to file
	const char* writecontent = "This is a test";
	int res = fwrite(writecontent, 1, strlen(writecontent), file);
	if(!res) {
		if(ferror(file))
			printf("Error occured\r\n");
		perror("fwrite()");
		goto fs_err;
	}
	printf("wrote file: %x\r\n", res);

	//Seek to start
	res = fseek(file, 0, SEEK_SET);
	if(res == -1) {
		perror("fseek()");
		goto fs_err;
	}
	printf("seeked file: %x\r\n", res);

	//Read file
	char readcontent[256];
	res = fread(readcontent, 1, 255, file);
	if(!res) {
		if(ferror(file))
			printf("Error occured\r\n");
		if(feof(file))
			printf("EOF occured\r\n");
		perror("fread()");
		goto fs_err;
	}
	readcontent[res] = '\0';
	printf("read file: %x\r\n", res);
	printf("content: %s\r\n", readcontent);

fs_err:
	//Close file
	res = fclose(file);
	if(res != 0) {
		perror("fclose()");
		goto fs_err;
	}
	printf("closed file: %x\r\n", res);

	DeinitializeFilesystem();
}

void Update(uint32_t delta)
{
	snes_button_state_t state = GetControllerState();
	//printf("Delta: %d\r\n", delta);
	//printf("Button A: %d\r\n", state.buttons.A);
	Delay(100);
}

void Draw()
{

}