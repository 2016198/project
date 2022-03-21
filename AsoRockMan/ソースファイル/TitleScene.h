//#pragma once

//定数定義
#define TITLE_SIZE_X 600
#define TITLE_SIZE_Y 250

class TitleScene   //クラス化
{
private:				 //メンバー変数
	int mScreenSizeX;    //画面のXサイズ
	int mScreenSizeY;    //画面のYサイズ
	int mImage;			 //タイトルイメージ
	int mStartImage;     //グラフィックハンドル
	int mCounter;        //タイトルカウンター

public:
	bool Init(void);       //インスタンスの生成処理
	bool UpDate(void);     //インスタンスの更新処理
	void Draw(void);       //インスタンスの描画処理
	bool Release(void);    //インスタンスの開放処理
	bool GameInit(void);   //インスタンスの初期化処理
};