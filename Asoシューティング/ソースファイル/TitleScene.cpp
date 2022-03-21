#include "TitleScene.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool TitleScene::Init()//初期化処理
{
	if ((tImage = LoadGraph("image/titleM.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	if ((LImage = LoadGraph("image/titleL.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	if ((RImage = LoadGraph("image/titleR.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	en = PAI / 180; 
	plus = 0;
	minus = 0;

	return true;
}

void TitleScene::UpDate()//更新処理
{
	plus += 2;
	minus -= 2;
}

void TitleScene::Draw()//描画処理
{
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0f, en * (plus % 360), RImage, true);
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0f, en * (minus % 360), LImage, true);
	DrawGraph((SCREEN_SIZE_X - TITLE_SIZE_X) / 2, (SCREEN_SIZE_Y - TITLE_SIZE_Y) / 2, tImage, true);
	if ((plus / 50) % 2 == 0)
	{
		SetFontSize(17);
		DrawString(200, 20, "エンターキーでスタート！", GetColor(255, 0, 255));
	}
}

bool TitleScene::Release()//解放処理
{
	DeleteGraph(RImage);
	DeleteGraph(LImage);
	DeleteGraph(tImage);
	return true;
}

bool TitleScene::GameInit()//ゲームオーバーの初期化処理
{
	plus = 0;
	minus = 0;
	return true;
}