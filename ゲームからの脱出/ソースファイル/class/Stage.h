#pragma once
#include "Vector2.h"

//定数
constexpr int CHIP_IMAGE_MAX = 384;	//マップチップの数
constexpr int MAP_X = 18;			//マップの横サイズ
constexpr int MAP_Y = 13;			//マップの縦サイズ

class Stage
{
public:

	int mMapImage[CHIP_IMAGE_MAX];	//MapChipの格納領域

	//エフェクトの格納領域
	int pazzuleImage[3][3];
	int escapeImage[3][3];

	int animCnt;

	bool Init(void);			
	bool Update(void);			
	void PassDraw(void);			
	void NotPassDraw(void);			
	bool Release(void);			

	int GetMapChip(Vector2 pos);
	int GetEventChip(Vector2 pos);

	//エフェクトの描画
	void EventDraw(Vector2 pos);
	void EscapeDraw(Vector2 pos);

private:
	Vector2 mOffset;		//マップのオフセット

	int image;
};
