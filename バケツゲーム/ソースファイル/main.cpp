#include <DxLib.h>
#include <math.h>
#include <time.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "main.h"
#include "KeyCheck.h"
#include "water.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetWindowText("waterGame");
	ChangeWindowMode(true);
	DxLib_Init();
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	//‰Šú‰»ˆ—
	srand((unsigned int)time(NULL));
	KeyInit();
	Water water;
	water.Init();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//XVˆ—
		if (water.UpDate()) break;
		CheckKeyList();
		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		//•`‰æˆ—
		water.Draw();
		ScreenFlip();
	}
	water.Release();
	DxLib_End();
	return 0;
}