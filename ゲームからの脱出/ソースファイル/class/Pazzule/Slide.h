#pragma once
class Slide
{
	class XY  //座標とマス値
	{
	public:
		int x;
		int y;
		int masu;
	};

	void Pattan(int num);				//ピースのパターン(乱数使用)
	void Move(int pase);				//ピースの移動
	bool Check(int x, int y, int size);	//カーソルのチェック

	enum class GAMEMODE
	{
		PUZZLE,
		LIGHT
	};

	//定数
	static const int P = 8;	//ピースの数
	#define SIZE 50			//ピースの大きさ


public:
	bool Init(void);
	void Update(void);
	void Draw(void);
	bool ReturnFlag(void);

	//謎解き中に戻る
	bool Back(void);


private:

//変数
	XY p[P];			//ピースの座標
	XY masu[P + 1];		//マスの座標
	int emptyMasu;		//空のマス
	int X, Y, cnt;		//マウスの座標
	int gameCnt = 0;	//ゲームカウント
	XY Random[P + 1];	//乱数
	bool Chach[P + 1];	//カーソルが触れているか
	int num_;			//乱数

	bool clearFlag_;
	bool backFlag;

	int font_;

};

