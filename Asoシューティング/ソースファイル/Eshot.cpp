#include "Eshot.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Eshot::Init(void)//初期化処理
{
	Image = LoadGraph("image/eshot.png");
	if (Image == -1)
	{
		TRACE("弾の画像の読み込みに失敗しました。");
		return false;
	}
	pos.X = 0;
	pos.Y = 0;
	Alive = false;
	speed = 5;

	return true;
}

void Eshot::Setup(Vector2 ePos)//座標を与える
{
	if (Alive == false)
	{
		Alive = true;
		pos.X = ePos.X;
		pos.Y = ePos.Y;
		//PlaySoundMem(se, DX_PLAYTYPE_BACK);
	}
}

void Eshot::UpDate(Vector2 Pos)//更新処理
{
	if (pos.Y >= -E_SHOT_SIZE_Y &&  //スクリーンの中にいるとき
		pos.X >= -E_SHOT_SIZE_X &&
		pos.X <= SCREEN_SIZE_X &&
		pos.Y <= SCREEN_SIZE_Y &&
		Alive == true)          //発射しているとき
	{
		pos.Y += Pos.Yy * speed;
		pos.X += Pos.Xx * speed;
	}
	else    //画面外に出た時の処理
	{
		Alive = false;          //発射していないとき
	}
}

void Eshot::Draw(void)//描画処理
{
	if (Alive == true)
	{
		DrawGraph(pos.X, pos.Y, Image, true);                     //弾の描画
	}
}

Vector2 Eshot::GetPos(void)   //座標成分を与える
{
	return pos;
}

bool Eshot::GetAlive(void)  //撃ってるかどうかの状態を返す
{
	return Alive;
}

void Eshot::DeleteShot(void) //弾を消す処理
{
	Alive = false;
}

bool Eshot::Release(void)  //解放処理
{
	DeleteGraph(Image);
	return true;
}

bool Eshot::GameInit(void)  //ゲームオーバーの後の初期化処理
{
	pos.x = 0;
	pos.y = 0;
	Alive = false;

	return true;
}