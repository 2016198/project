#pragma once
#include "../GameCommon.h"
#include "../Vector2.h"

//定数
static const int P = 9;			//ピースの数
#define SIZE 50		//ピースの大きさ


class Light
{
private:
	//変数
	Vector2 masu[P];		//マスの座標
	Vector2 mouse;			//マウスの座標
	int gameCnt = 0;	//ゲームカウント
	int clear;			//クリア条件
	bool Chach[P];		//カーソルが触れているか
	int Light[P];		//光っているかどうか
	unsigned int color[P];//色

	void Pattan(int pase);				//光るパターン
	bool Check(int x, int y, int size);	//カーソルのチェック

	bool clearFlag_;
	bool backFlag;

	int font_;

public:
	bool Init(void);
	void Update(void);
	void Draw(void);
	bool Release(void);
	bool ReturnFlag(void);

	//謎解き中に戻る
	bool Back(void);

};

