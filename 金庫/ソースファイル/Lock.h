#pragma once
#include <memory>
#include <list>

struct vector2
{
	int x, y;
};

class Lock
{
private:

	vector2 mouse = {};
	int cake;											//グラフィックハンドル
	const size_t pass_size = 6;							//パスワードの長さ
	const size_t pass_max_size = 20;					//入力の最大値
	std::list<int> pass;								//パスワード
	int word[6] = {										//模範解答(正解のパスワード)
		4,7,1,3,5,6
	};

	bool CheckBox(int x, int y, int sizeX, int sizeY);	//当たり判定四角
	bool CheckCircle(vector2 sub, int size);			//当たり判定円
	bool PassCheck(void);								//そのまんま
	bool canOpen;										//開けられる?
	bool open;											//開いてる？
	bool check;											//パスワードがあっているかのチェック
	int time;											//文字の表示時間
	int error;											//エラーの表示時間
	const vector2 pos = { 290, 155 };					//文字たちの左上座標
	const int size = 40;								//文字たちの枠
	unsigned int color[12];								//色
	const char* num[12] = {								//文字たち
		"1", "2", "3",
		"4", "5", "6",
		"7", "8", "9",
		"C", "0", "E"
	};
	
public:

	bool Init();
	void UpDate();
	void Draw();
	bool Release();
};

vector2 operator+(vector2 a, vector2 b);
vector2 operator-(vector2 a, vector2 b);
vector2 operator*(vector2 a, vector2 b);
vector2 operator/(vector2 a, vector2 b);

