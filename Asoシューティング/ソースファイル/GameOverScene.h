//#pragma once

//定数定義
#define PAI 3.1415926535       //円周率 
#define TITLE_SIZE_X 320       //文字のサイズX
#define TITLE_SIZE_Y 80        //文字のサイズY

class GameOverScene
{
private:
	int image;                    //グラフィックハンドル
	int PosX;                     //座標X
	int PosY;                     //座標Y
	int counter;                  //ゲームオーバーカウンター
	double en;                    //回転速度
public:
	bool Init(void);              //インスタンスの生成時処理
	void UpDate(void);            //インスタンスの更新処理
	void Draw(void);              //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
};
