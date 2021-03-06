#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"			
#include "GameCommon.h"
#include "KeyCheck.h"
#include "Stage.h"

//通過可能レイヤ―
int mMap1[MAP_Y][MAP_X] =
{
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120, 49, 120,120,120,120,120, 120,120, 49,120,120, 120,120,120,

	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120, 49, 120,120,120,120,120, 120,120, 49,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,

	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120,
	120,120,120,120,120, 120,120,120,120,120, 120,120,120,120,120, 120,120,120
};

//通過不可レイヤー
int mMap2[MAP_Y][MAP_X] =
{
	179,179,179,179,  0,  0,0,303,  0,303,  0,0,  0,134,177,    0,181,182,
	203,203,203,203,  0,  0,0,327,  0,327,  0,0,  0,158,201,  297,205,206,
	  0,  0,  0,  0,  0,  0,0,  0,  0,  0,  0,0,  0,  0,  0,    0,  0,  0,
	  0,  0,  0,  0,302,  0,0,  0,  0,  0,  0,0,302,  0,  0,    0,  0,  0,
	  0,  0,  0,  0,326,  0,0,  0,  0,  0,  0,0,326,  0,  0,    0,  0,  0,

  	  0,  0,  0,  0,  0,  0,0,  0,  0,  0,  0,0,  0,  0,  0,    0,  0,  0,
	  0,  0,  0,  0,  0,  0,0,  0,228,  0,  0,0,  0,  0,  0,    0,  0,  0,
	  0,  0,  0,  0,302,  0,0,  0,  0,  0,  0,0,302,  0,  0,    0,  0,  0,
	  0,  0,  0,  0,326,  0,0,  0,  0,  0,  0,0,326,  0,  0,    0,  0,  0,
	  0,  0,  0,  0,  0,  0,0,  0,  0,  0,  0,0,  0,  0,  0,    0,  0,  0,

	227,  0,  0,  0,  0,  0,0,  0,  0,  0,  0,0,  0,  0,  0,    0,  0,  0,
	251,  0,  0,  0,  0,  0,0,  0,  0,  0,  0,0,  0,  0,  0,    0,  0,183,
	275,  0,  0,  0,  0,  0,0,  0,  0,  0,  0,0,  0,  0,  0,    0,  0,207

};

//イベント用レイヤー
int eventMap[MAP_Y][MAP_X] =
{
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,134,0,   0,0,0,
	0,0,203,0,0, 0,0,0,0,0, 0,0,  0,  0,0, 297,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,

	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,326,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,

	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0,
	0,0,  0,0,0, 0,0,0,0,0, 0,0,  0,  0,0,   0,0,0
};

bool Stage::Init(void)
{
	mOffset.x = 32;
	mOffset.y = 32;

	//マップチップ画像
	if (LoadDivGraph("image/map/MapChip.png", CHIP_IMAGE_MAX, 24, 16, 32, 32, &mMapImage[0]) == -1)
	{
		return false;
	}

	//エフェクト画像
	LoadDivGraph("image/effect/pazzule.png",
				3,3,1,
				32,32,
				&pazzuleImage[0][0],true);

	LoadDivGraph("image/effect/escape.png",
				3, 3, 1,
				64, 114,
				&escapeImage[0][0], true);

	animCnt = 0;
	return true;
}
bool Stage::Update(void)
{
	animCnt++;
	return true;

}
void Stage::PassDraw(void)
{
	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + mOffset.x, y * CHIP_SIZE_Y + mOffset.y, mMapImage[mMap1[y][x]], true);
		}
	}
}
void Stage::NotPassDraw(void)
{
	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + mOffset.x, y * CHIP_SIZE_Y + mOffset.y, mMapImage[mMap2[y][x]], true);
		}
	}
}

bool Stage::Release(void)
{
	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			DeleteGraph(mMapImage[mMap1[y][x]]);
			DeleteGraph(mMapImage[mMap2[y][x]]);
		}
	}
	return true;

}

int Stage::GetMapChip(Vector2 pos)
{
	//?@マップ座標をマップチップ配列のindexに変換する
	//?Aマップチップ配列の中にあるマップチップ番号を返す
	return mMap2[pos.y / 32][pos.x / 32];
}

int Stage::GetEventChip(Vector2 pos)
{
	return eventMap[pos.y / 32][pos.x / 32];
}

void Stage::EventDraw(Vector2 pos)//表示したい座標を引数で渡す
{
	for (int i = 0; i < 3; i++)
	{
		DrawGraph(pos.x, pos.y, pazzuleImage[i][animCnt / 15 % 3], true);
	}
}

void Stage::EscapeDraw(Vector2 pos)//表示したい座標を引数で渡す
{
	for (int i = 0; i < 3; i++)
	{
		DrawGraph(pos.x, pos.y, escapeImage[i][animCnt / 15 % 3], true);
	}
}
