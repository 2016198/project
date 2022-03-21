#include "Bg2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Bg2::Init(void)//初期化処理
{
	PosY1 = 0;
	PosY2 = -BG_SIZE_Y;
	Speed = 2;
	Image = LoadGraph("image/haikei.png");
	if (Image == -1)
	{
		TRACE("背景の読み込みに失敗しました。");
		return false;
	}
	return true;
}
void Bg2::UpDate(void)//更新処理
{
	//TRACE("Y=%d  ", playerPosY);  //デバッグ用
	//TRACE("X=%d\n", playerPosX);  //デバッグ用

	PosY1 += Speed;      //背景の移動
	PosY2 += Speed;      //背景の移動

	if (PosY1 >= SCREEN_SIZE_Y)
	{
		PosY1 -= BG_SIZE_Y * 2;
		TRACE("背景1を戻しました。\n");
	}

	if (PosY2 >= SCREEN_SIZE_Y)
	{
		PosY2 -= BG_SIZE_Y * 2;
		TRACE("背景2を戻しました。\n");
	}
}

void Bg2::Draw(void)//描画処理
{
	DrawGraph(0, PosY1, Image, true);														         //背景１
	DrawGraph(0, PosY2, Image, true);			                                                     //背景２
}

bool Bg2::Release(void)//解放処理
{
	DeleteGraph(Image);
	return true;
}

bool Bg2::GameInit(void)//ゲームオーバーの初期化処理
{
	PosY1 = 0;
	PosY2 = -BG_SIZE_Y;
	Speed = 2;

	return true;
}