//#pragma once

//定数定義
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

class XY  //座標とマス値
{
public:
	int x;
	int y;
	int masu;
};

void Pattan(int num);//	乱数
void Move(int pase);//ピースの移動
bool Check(int x, int y, int size);//カーソルのチェック

enum class GAMEMODE
{
	PUZZLE,
	LIGHT
};
