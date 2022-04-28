#pragma once

constexpr int BUTTON_CNT = 6;	//ボタンの数
constexpr int WATER_SIZE = 30;	//水の目盛りサイズ
constexpr int KEY_SIZE = 7;		//カギのサイズ

class Bucket
{
public:
	struct Button
	{
		int x;				//x座標
		int y;				//y座標
		int size;			//増える水の量
		bool canPush;		//押せる？押せない？
		unsigned int color;	//ボタンの色

	};
	bool Init(void);						
	void Update(void);						
	void Draw(void);						
	bool Release(void);						
	bool ReturnFlag(void);

	//謎解き中に戻る
	bool Back(void);
	bool backFlag;


private:
	struct Water
	{
		Button mouse;							//マウスの座標
		Button button[BUTTON_CNT];				//ボタンの座標
		int Magnitude(int x, int y)const;		//マウスと円の当たり判定
		int water;								//水の量
		int memory;								//現在のメモリの位置
		bool add = true;						//プラスtrue:マイナスfalse
		bool lock = false;						//水の移動中はボタンを押せない
		unsigned int fontColor[11];				//文字の色
		bool Check(int x, int y, int size);		//マウスのチェック
		bool isGetKey = false;					//カギがとれるか
		int keyOffsetPos;						//カギを入手後の座標
		int timer;								//フォントの表示時間
	};

	bool clearFlag_;
	Water water_;
	int font_;
	int count;
};

