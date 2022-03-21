#pragma once
#include "Vector2.h"
class GameScene;

//定数定義
#define SERIHU_COUNT 7

//アイテムの種類
enum class ITEM_TYPE
{
	SHIELD,
	HEART,
	WAY
};

class Shop
{
private:					//メンバー変数
	int mImage;				//グラフィックハンドル
	int mArrowImage;		//グラフィックハンドル
	GameScene* mParent;		//親のインスタンス変数
	int mCnt;				//ゲームカウント
	int mPosX;				//セリフの目隠し座標
	bool mBack;				//shopを出たかどうか
	bool mPush;				//何かボタンを押したか
	bool mBuy;				//商品を買ったかどうか
	bool mNoBuy;			//お金が足りないとき
	const char* mSerihu[SERIHU_COUNT] =
	{ 
		"いらっしゃいませ～",
		"お金が足り ないです",
		"3wayショット10回分(30回分までもてる)",
		"疲れたらこれで回復しろよ～",
		"あなたを少しだけ攻撃から守ります",
		"もう帰っちゃうの？",
		"まいどあり～"
	};	//店主のセリフ

public:                     //メンバー関数
	bool Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY);        //インスタンスの初期化処理
	int mScreenSizeX;       //画面のXサイズ
	int mScreenSizeY;       //画面のYサイズ
	bool UpDate(void);      //インスタンスの更新処理
	void Draw(void);	    //インスタンスの描画処理
	bool Release(void);     //インスタンスの開放処理
	bool GameInit(GameScene* parent);	//ゲームの初期化
	int mShopImage;			//グラフィックハンドル
};
