#include "Shot2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Shot2::Init(void) //初期化処理
{
	Image = LoadGraph("image/shot.png");
	if (Image == -1)
	{
		TRACE("弾の画像の読み込みに失敗しました。");
		return false;
	}
	pos.x = 0;
	pos.y = 0;
	Speed = 10;
	Alive = false;

	return true;
}

void Shot2::Setup(Vector2 pPos) //自機の座標にセットする
{
	if (Alive == false)
	{
		Alive = true;
		pos.x = pPos.x;
		pos.y = pPos.y;
		//PlaySoundMem(se, DX_PLAYTYPE_BACK);
	}
}

void Shot2::UpDate(int i)  //更新処理  ("i"は３WAYショット用の変数)
{
	if (pos.y >= -P_SHOT_SIZE_Y && Alive == true)          //発射しているとき
	{
		pos.y -= Speed;
		pos.x += i;
	}
	else    //画面外に出た時の処理
	{
		Alive = false;          //発射していないとき
	}
}

void Shot2::Draw(void)//描画処理
{
	if (Alive == true)
	{
		DrawGraph(pos.x, pos.y, Image, true);                     //弾の描画
	}
}

Vector2 Shot2::GetPos(void)   //座標成分を与える
{
	return pos;
}

bool Shot2::GetAlive(void)   //弾を撃ってるかどうか
{
	return Alive;
}

void Shot2::DeleteShot(void) //弾を消す
{
	Alive = false;
}

bool Shot2::Release(void) //インスタンスの解放
{
	DeleteGraph(Image);
	return true;
}

bool Shot2::GameInit(void)//ゲームオーバー後の初期化処理
{
	pos.x = 0;
	pos.y = 0;
	Speed = 10;
	Alive = false;

	return true;
}