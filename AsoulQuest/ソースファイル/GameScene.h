#pragma once
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"
#include "LifeBar.h"
#include "Score.h"
#include "Item.h"
#include "Shop.h"
#include "Vector2.h"
#include "CharOrder.h"

//親のクラス格納変数
class SceneManager;

enum class SceneId //今どこのシーンか
{
	SCENE_BATTOL,
	SCENE_SHOP
};

class GameScene
{
private:                            //メンバー変数
	SceneManager* mParent;          //親の格納変数
	int mScreenSizeX;               //画面のXサイズ
	int mScreenSizeY;               //画面のYサイズ
	int mCounter;                   //ゲームカウンター
	bool mFadeOut;                  //true：fadeOut中
	bool mFadeIn;                   //true：fadeIn中
	int mColor;                     //色の明るさ
	SceneId mScene_id;				//現在のシーン
	int mWay;						//3wayショットがあと何回撃てるかどうか
	bool ScreenEffect(SceneId nextSceneID);      //画面切り替え時にエフェクトを行う

							//インスタンスの生成
	Stage mStage;			//マップ情報のインスタンス生成
	Player mPlayer;			//プレイヤー情報のインスタンス生成
	Shot mShot[SHOT_COUNT]; //ショット情報のインスタンス生成
	Enemy mEnemy[ENEMY_COUNT]; //敵情報のインスタンス生成
	LifeBar mLifeBar[ENEMY_COUNT];//ライフバー情報のインスタンス生成
	Score mPoint[SCORE_COUNT];        //スコア情報のインスタンス生成
	Item mItem[ITEM_COUNT];			  //アイテム情報のインスタンス生成
	Shop mShop;						  //ショップ情報のインスタンス生成
	
	Vector2 mOffset;           //オフセットの格納変数

	int mScore;			//スコア
	int mFont;			//スコアのフォントサイズ
	int mFontHigh;		//ハイスコアのフォントサイズ
	int mKillCount;		//敵を倒した数
	int mFontkill;		//フォントサイズ倒した数
	int mSeWay;			//サウンドハンドル
	int mSeHit;			//サウンドハンドル
	int mSeKill;		//サウンドハンドル
	int mSePshot;		//サウンドハンドル
	int mSeEshot;		//サウンドハンドル
	int mSeCoin;		//サウンドハンドル
	int mSeDamage;		//サウンドハンドル

	//キャラクターの並び替え
	CharOrder mCharOrder[ENEMY_COUNT + 1];  //キャラクターの並び変え用オーダー
	int mCharOrderCount;					//キャラクターオーダーカウント

	//マップ移動用変数
	bool mMapChange;				//マップの切り替え
	MAP_ID mNextMapID;				//次のマップID
	Vector2 mNextPos;				//次のマップの座標
	Vector2 mNextOffsetPos;			//次のオフセットマップの座標

	//メンバー関数
	bool LoadEnemyImage(void);			//敵の画像のロード処理
	bool LoadShotImage(void);			//弾の画像のロード処理
	bool LoadLifeBarImage(void);		//ライフバー画像のロード処理
	bool LoadItemImage(void);			//アイテムの画像の読みこみ
	void AddCharOrder(int bottomPos, int index, CHAR_TYPE charType);	    //敵の並び変え処理
	void Born(Vector2 targetPos, int Index);							//敵が復活する処理
	bool SaveData(void);				//セーブ処理
	bool LoadData(void);				//ロード処理
	 
public:                    //メンバー関数
	int mCoin;			//所持金
	bool ScoreSet(void);   //スコアのリセット処理
	bool Init(int ScreenSizeX, int ScreenSizeY, SceneManager * parent);       //インスタンスの生成処理
	bool UpDate(void);     //インスタンスの更新処理
	void Draw(void);       //インスタンスの描画処理
	bool Release(void);    //インスタンスの開放処理
	bool GameInit(void);   //インスタンスの初期化処理
	int mEnemyImage[ENEMY_TYPE_MAX][ENEMY_ANIM_COUNT * (int)DIR::DIR_MAX];   //敵の画像の格納領域
	int mP_ShotImage[SHOT_IMAGE_COUNT];                            //弾(自機)の画像の格納領域
	int mE_ShotImage[SHOT_IMAGE_COUNT];                            //弾(敵)の画像の格納領域
	int mLifeBarImage[LIFE_ANIM_COUNT];                            //ライフバーの画像の格納領域
	int mItemImage[ITEM_IMAGE_COUNT];							   //ライフバーの画像の格納領域
	int mSeBuy;													   //サウンドハンドル
	int mSeDoor;											       //サウンドハンドル

	int GetEvent(Vector2 pos);									   //プレイヤーの座標が何番のマップにいるかを返す
	int GetScore(void);											   //スコアを返す
	void BuyItem(ITEM_TYPE itemType);							   //アイテムを購入したかどうか
};