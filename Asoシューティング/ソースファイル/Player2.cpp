#include "Player2.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "main.h"

bool Player2::Init(Vector2 Init)  //PlayerクラスのInit関数の中身
{
	Image = LoadGraph("image/player.png");
	if (Image == -1)
	{
		TRACE("プレイヤー画像の読み込みに失敗しました。");
		return false;
	}
	life = PLAYER_LIFE;
	pos.x = Init.x;
	pos.y = Init.y;
	/*pos_x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	pos_y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;*/
	Speed = 4;
	Alive = true;
	shotFlag = false;
	return true;
}

void Player2::Update(void)   //PlayerクラスのUpDate関数の中身
{
	if (Alive == false)
	{
		pos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
		pos.y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
		life--;
		Alive = true;
		//enemyAlive = false;
	}

	if (Alive == true)
	{
		if (CheckHitKey(KEY_INPUT_LEFT) && pos.x >= 0)   //自機の移動処理
		{
			pos.x = pos.x - Speed;  //左
		}
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) && pos.x <= SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			pos.x = pos.x + Speed;  //右
		}
		if (pos.x > SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			pos.x = SCREEN_SIZE_X - PLAYER_SIZE_X;
		}
		if (CheckHitKey(KEY_INPUT_UP) && pos.y >= 0)
		{
			pos.y = pos.y -Speed;  //上
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) && pos.y <= SCREEN_SIZE_Y - PLAYER_SIZE_Y)
		{
			pos.y = pos.y + Speed;  //下
		}
		if (pos.y > SCREEN_SIZE_Y - PLAYER_SIZE_Y)
		{
			pos.y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
		}
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		shotFlag = true;
	}
	else
	{
		shotFlag = false;
	}
}

void Player2::Draw(void)//描画処理
{
	DrawGraph(pos.x, pos.y, Image, true);   //自機
}

void Player2::Drawen(void)//円の描画処理
{
	DrawCircle(pos.x + PLAYER_SIZE_X / 2, pos.y + PLAYER_SIZE_Y / 2, PLAYER_SIZE_X / 2 + 10, GetColor(255, 255, 255), 0);
}

//弾を発射していればtrueを返す。
bool Player2::IsShot(void)
{
	return shotFlag;
}

//プレイヤーの座標を返す
Vector2 Player2::GetPos(void)
{
	return pos;
}

void Player2::DeletePlayer(void) //プレイヤーを消す
{
	 Alive = false;
}

//プレイヤーの生きてるか
bool Player2::GetAlive(void)
{
	return Alive;
}

bool Player2::Release(void) //インスタンスの解放処理
{
	DeleteGraph(Image);
	return true;
}

bool Player2::Death(void) //プレイヤー全滅処理
{
	if (life <= 0)
	{
		return true;
	}
	return false;
}

int Player2::GetLife(void) //残機を返す
{
	return life;
}

bool Player2::GameInit(Vector2 Init)  //PlayerクラスのInit関数の中身
{
	life = 3;
	pos.x = Init.x;
	pos.y = Init.y;
	/*pos_x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	pos_y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;*/
	Speed = 4;
	Alive = true;
	shotFlag = false;
	return true;
}
