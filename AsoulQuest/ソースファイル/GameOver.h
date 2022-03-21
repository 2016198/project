//#pragma once

//定数定義
#define GAME_OVER_SIZE_X 457
#define GAME_OVER_SIZE_Y 81

class GameOver
{
private:                   //メンバー変数
	int mScreenSizeX;              //画面のXサイズ
	int mScreenSizeY;              //画面のYサイズ
	int mImage;            //グラフィックハンドル
	int mPlayer[3];        //グラフィックハンドル
	int mCounter;          //ゲームオーバーカウンター
	int mScore;			   //スコア
	bool mInput;		   //スコアが代入されたかどうか
	int mSe;			   //効果音ハンドル

public:                    //メンバー関数
	bool Init(int ScreenSizeX, int ScreenSizeY);       //インスタンスの生成処理
	bool UpDate(void);     //インスタンスの更新処理
	void Draw(int score);       //インスタンスの描画処理
	bool Release(void);    //インスタンスの開放処理
	bool GameInit(void);   //インスタンスの初期化処理
};
