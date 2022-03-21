//#pragma once
#include "gamecommon.h"

//定数定義
#define GAME_OVER_SIZE_X 457
#define GAME_OVER_SIZE_Y 81

class GameOver
{
private:                   //メンバー変数
	int mImage;            //グラフィックハンドル
	int mCounter;          //ゲームオーバーカウンター


public:                    //メンバー関数
	bool Init(void);       //インスタンスの生成処理
	bool UpDate(void);     //インスタンスの更新処理
	void Draw(void);       //インスタンスの描画処理
	bool Release(void);    //インスタンスの開放処理
	bool GameInit(void);   //インスタンスの初期化処理
};
