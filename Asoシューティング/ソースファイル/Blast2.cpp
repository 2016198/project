#include "DxLib.h"
#include "Blast2.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Blast2::Init(void)//初期化処理
{
	if (LoadDivGraph("image/blast.png",
		BLAST_COUNT_X * BLAST_COUNT_Y,
		BLAST_COUNT_X,
		BLAST_COUNT_Y,
		BLAST_SIZE_X,
		BLAST_SIZE_Y,
		&Image[0]) == -1)
	{
		TRACE("読み込み失敗。");
		return false;
	}
	PosX = 0;
	PosY = 0;
	No = 0;
	Alive = false;
	return true;
}

void Blast2::UpDate(void)//更新処理
{
	if (Alive == true)    //爆発アニメーションの処理
	{
		No++;
		if (No / 2 > (BLAST_COUNT_X * BLAST_COUNT_Y) - 1)
		{
			Alive = false;              //アニメーションの終わり
		}
	}
}

void Blast2::Setup(Vector2 Pos)//座標の受け取り処理
{
	PosX = Pos.x;
	PosY = Pos.y;
	No = 0;
	Alive = true;
}

void Blast2::Draw(void)//描画処理
{
	if (Alive == true)
	{
		DrawGraph(PosX - 16, PosY - 16, Image[No / 2], true);     //爆発のアニメーションのスタート設定処理
	}
}

bool Blast2::GetAlive(void)//表示されてるかのチェック
{
	return Alive;
}

bool Blast2::Release(void)//解放処理
{
	for (int g = 0; g < BLAST_COUNT_X * BLAST_COUNT_Y; g++)
	{
		DeleteGraph(Image[g]);
	}
	return true;
}

bool Blast2::GameInit(void)//ゲームオーバーの初期化処理
{
	PosX = 0;
	PosY = 0;
	No = 0;
	Alive = false;
	return true;
}