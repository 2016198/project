#pragma once
#include <DxLib.h>
#include <memory>
#include <list>
#include "../Vector2.h"


class Safe
{
private:
	int image = LoadGraph("yaju.png");
	Vector2 mouse = {};
	const size_t pass_size = 6;			//パスワードの長さ
	const size_t pass_max_size = 20;	//入力の限界値
	std::list<int> pass;				//パスワード
	int word[6] = {						//正解のパスワード
		1,9,2,4,9,4
	};

	bool CheckBox(int x, int y, int sizeX, int sizeY);	//当たり判定四角
	bool CheckCircle(Vector2 sub, int size);			//当たり判定円
	bool PassCheck(void);								//開くかどうかの判定
	bool canOpen;										//開けられる？
	bool open;											//開いた
	bool check;											//パスワードがあっているかのチェック
	int time;											//文字の表示時間
	int error;											//エラーの表示時間
	const Vector2 pos = { 290,155 };					//文字の左上座標
	const int size = 40;								//文字の枠
	unsigned int color[12];								//色の格納
	const char* num[12] = {								//金庫に描画する文字
		"1", "2", "3",
		"4", "5", "6",
		"7", "8", "9",
		"C", "0", "E"
	};

	bool clearFlag_;
	bool backFlag;
	int count;
	int font_;

public:
	bool Init(void);
	void Update();
	void Draw();
	bool Release();
	bool ReturnFlag(void);

	//謎解き中に戻る
	bool Back(void);

};

Vector2 operator+(Vector2 a, Vector2 b);
Vector2 operator-(Vector2 a, Vector2 b);
Vector2 operator*(Vector2 a, Vector2 b);
Vector2 operator/(Vector2 a, Vector2 b);
