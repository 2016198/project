#include "main.h"
#pragma once

//定数
#define P 9			//ピースの数
#define SIZE 50		//ピースの大きさ

class Vec  //座標
{
public:
	int x;
	int y;
};

class Light
{
private:
	//変数
	Vec masu[P];		//マスの座標
	Vec mouse;			//マウスの座標
	int gameCnt = 0;	//ゲームカウント
	int clear;			//クリア条件
	bool Chach[P];		//カーソルが触れているか
	int Light[P];		//光っているかどうか
	unsigned int color[P];//色

	void Pattan(int pase);				//光るパターン
	bool Check(int x, int y, int size);	//カーソルのチェック

public:
	bool Init(void);
	void UpDate(void);
	void Draw(void);
	bool Release(void);
};

