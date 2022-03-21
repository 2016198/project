#include "GameOver.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

bool GameOver::Init(void)  //インスタンスの生成処理
{
	mCounter = 0;
	if ((mImage = LoadGraph("Image/gameover.png")) == -1)
	{
		return false;
	}
	return true;
}

bool GameOver::UpDate(void)  //インスタンスの更新処理
{
	mCounter++;
	return KeyTrgDown[KEY_SYS_START];
}

void GameOver::Draw(void)  //インスタンスの描画処理
{
	SetDrawScreen(DX_SCREEN_BACK);                  //バックバッファに設定
	ClsDrawScreen();                                //画面消去
	DrawBox(50, 50, 700, 440, GetColor(0, 255, 255), 1);
	DrawGraph((SCREEN_SIZE_X - GAME_OVER_SIZE_X) / 2, (SCREEN_SIZE_Y - GAME_OVER_SIZE_Y) / 2, mImage, true);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawString(300, 370, "space : タイトル画面へ", GetColor(2, 2, 2));
		DrawString(300, 370, "\n\nEsc   :   終わる", GetColor(5, 5, 5));
	}
}

bool GameOver::Release(void)  //インスタンスの開放処理
{
	DeleteGraph(mImage);
	return true;
}

bool GameOver::GameInit(void)
{
	mCounter = 0;
	return true;
}