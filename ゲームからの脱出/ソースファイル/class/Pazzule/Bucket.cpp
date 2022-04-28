#include <DxLib.h>
#include <math.h>
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include "Bucket.h"
#include "../KeyCheck.h"

bool Bucket::Init(void)
{
	font_ = CreateFontToHandle("HGSｺﾞｼｯｸE", 40, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 4);
	count = 0;
	for (int b = 0; b < BUTTON_CNT; b++)
	{
		water_.button[b].x = 450;
		water_.button[b].y = 100 + 40 * b;
		water_.button[b].canPush = true;
	}
	water_.button[0].size = 0;
	water_.button[1].size = 2;
	water_.button[2].size = 6;
	water_.button[3].size = 5;
	water_.button[4].size = 4;
	water_.button[5].size = 3;

	water_.fontColor[10] = 0xff00ff;
	for (int l = 1; l < 10; l++)
	{
		water_.fontColor[l] = 0xffffff;
	}
	water_.fontColor[0] = 0x666666;
	water_.timer = 0;
	GetMousePoint(&water_.mouse.x, &water_.mouse.y);
	water_.keyOffsetPos = 0;
	water_.water = 0;
	water_.memory = 0;

	clearFlag_ = false;
	backFlag = false;
	return true;
}

void Bucket::Update(void)
{
	//bool flag = false;
	if (water_.lock == false)
	{
		for (int c = 1; c < BUTTON_CNT; c++)
		{
			water_.add ?//プラス？マイナス？
				water_.button[c].size + water_.water > 10 ?//押せる？押せない？
				water_.button[c].canPush = false :
				water_.button[c].canPush = true :
				water_.button[c].size - water_.water > 0 ?//押せる？押せない？
				water_.button[c].canPush = false :
				water_.button[c].canPush = true;
			water_.button[c].canPush ?//色チェンジ
				water_.button[c].color = 0xffffff :
				water_.button[c].color = 0x114514;
		}
		water_.add ?//プラス？マイナス？
			water_.button[0].color = 0xaa0000 :
			water_.button[0].color = 0x0000aa;
	}
	GetMousePoint(&water_.mouse.x, &water_.mouse.y);
	if (water_.Check(250, 390 - water_.memory, KEY_SIZE))
	{
		if (keyTrgDown[MOUSE_LEFT])
		{
			water_.timer = 30;
		}
	}

	water_.isGetKey = water_.water == 10;

	if (keyTrgDown[KEY_P1_X])
	{
		backFlag = true;
	}
	count++;
}

void Bucket::Draw(void)
{
	DrawBox(0, 0, 640, 480, 0x000000, true);
	for (int w = 0; w < BUTTON_CNT; w++)
	{
		if (water_.lock == false)
		{
			if (water_.button[w].canPush)//押せるかどうかチェック
			{
				if (water_.Check(water_.button[w].x, water_.button[w].y, 15))//マウスカーソルチェック
				{
					DrawCircle(water_.button[w].x, water_.button[w].y, 20, water_.button[w].color);
					if (keyTrgDown[MOUSE_LEFT])
					{
						w == 0 ?
							water_.add = !water_.add :
							water_.add ?
							water_.water += water_.button[w].size :
							water_.water -= water_.button[w].size;	//水の増加：減らす
					}
				}
			}
		}

		if (w != 0)
		{
			DrawCircle(water_.button[w].x, water_.button[w].y, 15, water_.button[w].color);
			DrawFormatString(water_.button[w].x - 8, water_.button[w].y - 8, 0x000000, "%d", water_.button[w].size * 10);
		}
	}

	DrawCircle(water_.button[0].x, water_.button[0].y, 15, water_.button[0].color);
	water_.add ?
		DrawString(water_.button[0].x - 4, water_.button[0].y - 8, "+", 0x000000) ://プラスの時
		DrawString(water_.button[0].x - 4, water_.button[0].y - 8, "-", 0x000000); //マイナスの時
	DrawLine(100, 70, 100, 400, 0xffff00, 5);
	DrawLine(400, 400, 100, 400, 0xffff00, 5);
	DrawLine(400, 400, 400, 70, 0xffff00, 5);
	//DrawFormatString(0, 0, 0xffffff, "%d %d", mouse.x, mouse.y);//マウス座標の確認(デバッグ用)
	if (water_.water * WATER_SIZE > water_.memory)
	{
		water_.memory += WATER_SIZE / 10;
		water_.lock = true;
	}
	else
	{
		if (water_.water * WATER_SIZE < water_.memory)
		{
			water_.memory -= WATER_SIZE / 10;
			water_.lock = true;
		}
		else
		{
			water_.lock = false;
		}
	}

	DrawBox(399, 399, 102, 390 - water_.memory, 0x1111ff, 1);
	DrawCircle(250, 390 - water_.memory - water_.keyOffsetPos, KEY_SIZE, 0xff0000);//カギ
	if (water_.timer > 0)
	{
		water_.isGetKey ?
			water_.keyOffsetPos += 6, clearFlag_ = true :
			DrawString(0, 0, "手が届かない", 0xffffff);
		water_.timer--;
	}

	int width;
	for (int p = 0; p <= 10; p++)
	{
		width = GetDrawFormatStringWidth("%d", p * 10);
		DrawFormatString(90 - width, 380 - p * WATER_SIZE, water_.fontColor[p], "%d", p * 10);
	}
	if (!clearFlag_)
	{
		if (count / 30 % 2 == 0)
		{
			DrawExtendString(220, 0, 2.0f, 2.0f, "マウスで操作", 0xffffff);
			DrawExtendString(230, 410, 1.5f, 1.5f, "＋ーで水量調節", 0xffffff);
			DrawExtendString(250, 434, 1.5f, 1.5f, "Xキーで戻る", 0xffffff);

		}
	}
	else
	{
		DrawStringToHandle(50, 200, "金庫のカギをゲットした!", 0xffff00, font_);
		if (count / 30 % 2 == 0)
		{
			DrawExtendString(200, 420, 1.5f, 1.5f, "Spaceキーで戻る", 0xffffff);

		}
	}
}

bool Bucket::Release(void)
{
	return true;
}

bool Bucket::ReturnFlag(void)
{
	if (clearFlag_)
	{
		backFlag = false;
		return true;
	}
	return false;
}

bool Bucket::Back(void)
{
	if (backFlag)
	{
		backFlag = false;
		return true;
	}
	return false;
}

int Bucket::Water::Magnitude(int x, int y) const
{
	return (int)(hypot(x,y));
}

bool Bucket::Water::Check(int x, int y, int size)
{
	if (Magnitude(mouse.x - x, mouse.y - y) <= size)
	{
		return true;
	}
	return false;
}
