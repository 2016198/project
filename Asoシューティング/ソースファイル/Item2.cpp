#include "Item2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Item2::Init(void)
{
	game = 0;
	en = PAI / 180;
	pos.x = 0;
	pos.y = 0;
	alive = false;
	speed = 2;
	if ((image = LoadGraph("image/item.png")) == -1)
	{
		TRACE("“Ç‚Ýž‚ÝŽ¸”s");
		return false;
	}
	return true;
}

void Item2::UpDate(void)
{
	game += 5;
	if (alive == true)
	{
		pos.y += speed;
	}
	if (pos.y >= SCREEN_SIZE_Y)
	{
		alive = false;
	}
}

void Item2::Draw(void)
{
	if (alive == true)
	{
		DrawRotaGraph(pos.x + ITEM_SIZE_X / 2, pos.y + ITEM_SIZE_Y / 2, 1.0f, en * (game % 360), image, true);
	}
}

void Item2::SetItem(Vector2	ePos)
{
	if (alive == false)
	{
		alive = true;
		pos.y = ePos.y;
		pos.x = ePos.x;
	}
}

Vector2 Item2::GetPos(void)
{
	return pos;
}

bool Item2::GetAlive(void)
{
	return alive;
}

void Item2::DeleteItem(void)
{
	alive = false;
}

bool Item2::Release(void)
{
	DeleteGraph(image);
	return true;
}

bool Item2::GameInit(void)
{
	game = 0;
	en = PAI / 180;
	pos.x = 0;
	pos.y = 0;
	alive = false;
	speed = 2;
	return true;
}