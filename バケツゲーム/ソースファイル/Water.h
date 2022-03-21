//#pragma once
constexpr int BUTTON_CNT = 6;	//ボタンの数
constexpr int WATER_SIZE = 30;	//水の目盛りサイズ
constexpr int KEY_SIZE = 7;	//カギのサイズ

struct Button
{
	int x;				//x座標
	int y;				//y座標
	int size;			//増える水の量
	bool canPush;		//押せる？押せない？
	unsigned int color;	//ボタンの色
};

class Water
{
private:
	Button mouse;							//マウスの座標
	Button button[BUTTON_CNT];				//ボタンの座標
	int Magnitude(int x, int y)const;		//マウスと円の当たり判定
	int water = 0;							//水の量
	int memory = 0;							//現在のメモリの位置
	bool add = true;						//プラスtrue:マイナスfalse
	bool lock = false;						//水の移動中はボタンを押せない
	unsigned int fontColor[11];				//文字の色
	bool Check(int x, int y, int size);		//マウスのチェック
	bool isGetKey = false;					//カギがとれるか
	int keyOffsetPos = 0;					//カギを入手後の座標
	int timer;								//フォントの表示時間

public:
	bool Init(void);						//初期化処理
	bool UpDate(void);						//更新処理
	void Draw(void);						//描画処理
	bool Release(void);						//解放処理
};

