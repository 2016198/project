#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "KeyCheck.h"
#include "SceneManager.h"

bool TitleScene::Init(int ScreenSizeX, int ScreenSizeY, SceneManager* parent)   //インスタンスの生成処理
{
	mParent = parent;
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	if ((mImage = LoadGraph("image/title.bmp")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	mCounter = 0;
	return true;
}

bool TitleScene::UpDate(void)   //インスタンスの更新処理
{
	if (KeyTrgDown[KEY_SYS_RESET] && mReset == false)
	{
		mParent->ScoreReset();
		mReset = true;
	}
	mCounter++;
	return KeyTrgDown[KEY_SYS_START];
}

void TitleScene::Draw(void)      //インスタンスの描画処理
{
	SetDrawScreen(DX_SCREEN_BACK);                  //バックバッファに設定
	ClsDrawScreen();                                //画面消去
	DrawBox(50, 50, 600, 440, GetColor(255, 0, 255), 1);
	DrawGraph((mScreenSizeX - TITLE_SIZE_X) / 2, (mScreenSizeY - TITLE_SIZE_Y) / 2, mImage, 0);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawString(250, 370, "space : スタート", GetColor(255, 255, 255));
		DrawString(250, 370, "\n\nEsc   :   終わる", GetColor(255, 255, 255));
	}
	DrawString(210, 100, "zキーでハイスコアのリセット",GetColor(0,0,0));
	if (mReset == true)
	{
		DrawString(200, 370, "ハイスコアをリセットしました。", GetColor(255, 255, 0));
	}
}

bool TitleScene::Release(void)   //インスタンスの開放処理
{
	DeleteGraph(mImage);
	return true;
}

bool TitleScene::GameInit(void)
{
	mReset = false;
	mCounter = 0;
	return true;
}