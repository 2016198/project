#include "GameOverScene.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool GameOverScene::Init(void)//初期化処理
{
	if ((image = LoadGraph("image/gameover.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	PosX = SCREEN_SIZE_X / 2;
	PosY = 0;
	en = PAI / 180;
	counter = 0;
	return true;
}

void GameOverScene::UpDate(void)//更新処理
{
	counter++;
}

void GameOverScene::Draw(void)//描画処理
{
	DrawGraph((SCREEN_SIZE_X - TITLE_SIZE_X) / 2, (SCREEN_SIZE_Y - TITLE_SIZE_Y) / 2, image, true);
	if ((counter / 50) % 2 == 0)
	{
		SetFontSize(30);
		DrawString(150, 0, "やめる   Escキー", GetColor(0, 255, 255));
		DrawString(150, 0, "\n続ける   Enterキー", GetColor(25, 255, 0));
	}
}

bool GameOverScene::Release(void)//解放処理
{
	DeleteGraph(image);
	return true;
}