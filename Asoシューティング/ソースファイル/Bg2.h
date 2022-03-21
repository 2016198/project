//#pragma once

//定数定義
#define BG_SIZE_X 640          //背景のサイズX
#define BG_SIZE_Y 960          //背景のサイズY

class Bg2  //メンバー変数
{
private:
	int Image;               //グラフィックハンドル
	int PosY1;               //背景１のY座標
	int PosY2;               //背景２のY座標
	int Speed;               //背景の移動速度

public:		//メンバー関数
	bool Init(void);              //インスタンスの生成時処理
	void UpDate(void);            //インスタンスの更新処理
	void Draw(void);              //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
	bool GameInit(void);          //背景の初期化処理
};
