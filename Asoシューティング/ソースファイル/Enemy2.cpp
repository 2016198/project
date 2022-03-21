#include "Enemy2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Enemy2::Init(void)//初期化処理
{
	//グラフィックの読み込み
	Image = LoadGraph("image/enemy.png");
	if (Image == -1)
	{                               //代入　=
		TRACE("敵画像の読み込みに失敗しました。");
		return false;
	}
	shotFlag = false;
	Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
	Pos.y = -ENEMY_SIZE_Y;
	Pos.X = Pos.x;
	Pos.Y = Pos.y;
	Speed = 3;
	gamecounter = 0;
	Alive = true;
	TRACE("敵の位置を初期化");
	TRACE("座標%d\n", Pos.x);
	return true;
}

void Enemy2::UpDate(bool bossMode, bool bossHunt)//更新処理
{
	gamecounter++;
	Pos.X = Pos.x;
	Pos.Y = Pos.y;
	if (bossMode == false && bossHunt == false)  //bossが登場してないとき
	{
		if (Alive == true)
		{
			Pos.y = Speed + Pos.y;      //敵の移動処理
			if (gamecounter % 100 == 0) //約１．５秒ごとに弾を撃つ
			{
				shotFlag = true;
			}
			else
			{
				shotFlag = false;
			}
		}
		else
		{
			Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
			Pos.y = -ENEMY_SIZE_Y;
			Alive = true;
			TRACE("敵の位置を初期化");
			TRACE("座標%d\n", Pos.x);
		}
		if (Pos.y >= SCREEN_SIZE_Y)
		{
			Pos.y = 0 - ENEMY_SIZE_Y;
			Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);                //rand()乱数
			TRACE("敵の位置を初期化");
			TRACE("座標%d\n", Pos.x);
		}
	}
	else
	{
		if (Alive == true)
		{
			Pos.y = Speed + Pos.y;        //敵の移動処理
			if (gamecounter % 100 == 0) //約１．５秒ごとに弾を撃つ
			{
				shotFlag = true;
			}
			else
			{
				shotFlag = false;
			}
		}
	}
}

void Enemy2::Draw(void)//描画処理
{
	if (Alive == true)
	{
		DrawGraph(Pos.x, Pos.y, Image, true);                     //描画
	}
}

//敵の座標を返す
Vector2 Enemy2::GetPos(void)
{
	return Pos;
}

void Enemy2::DeleteEnemy(void)//敵を消す
{
	Alive = false;
}

//敵がいきてるか
bool Enemy2::GetAlive(void)
{
	return Alive;
}

bool Enemy2::IsShot(void)//弾が撃たれてるかどうかのチェック
{
	return shotFlag;
}

bool Enemy2::Release(void)//解放処理
{
	DeleteGraph(Image);
	return true;
}

bool Enemy2::GameInit(void)//ゲームオーバーの初期化処理
{
	gamecounter = 0;
	shotFlag = false;
	Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
	Pos.y = -ENEMY_SIZE_Y;
	Speed = 3;
	Alive = true;
	TRACE("敵の位置を初期化");
	TRACE("座標%d\n", Pos.x);
	return true;
}