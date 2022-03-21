#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "KeyCheck.h"

bool TitleScene::Init(void)   //インスタンスの生成処理
{
	if ((mImage = LoadGraph("Image/Title.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	if ((mStartImage = LoadGraph("Image/hitstartkey.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	mCounter = 0;
	return true;
}

bool TitleScene::UpDate(void)   //インスタンスの更新処理
{
	mCounter++;
	return KeyTrgDown[KEY_SYS_START];
}

void TitleScene::Draw(void)      //インスタンスの描画処理
{
	SetDrawScreen(DX_SCREEN_BACK);                  //バックバッファに設定
	ClsDrawScreen();                                //画面消去
	DrawGraph(0, 0, mImage, true);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawGraph(210, 400, mStartImage, true);
	}
}

bool TitleScene::Release(void)   //インスタンスの開放処理
{
	DeleteGraph(mImage);
	DeleteGraph(mStartImage);
	return true;
}

bool TitleScene::GameInit(void)
{
	mCounter = 0;
	return true;
}