#pragma once
#include "Vector2.h"
#include "GameCommon.h"
#include "CharOrder.h"
class GameScene;

//定数定義
#define SHOT_IMAGE_COUNT 2     //ショットのアニメの数

class Shot
{
private:                              //メンバー変数
	GameScene* mParent;               //親のインスタンスのポインタ変数
	int mScreenSizeX;                 //画面のXサイズ
	int mScreenSizeY;                 //画面のYサイズ
	Vector2 mOffset;                  //オフセットの座標
	DIR mKeyDir;                      //キーの制御
	DIR mMoveDir;                     //キャラクターの向き
	Vector2 mPos;                     //キャラクターの地図上の座標
	Vector2 mSizeOffset;              //キャラクターのオフセットサイズ
	Vector2 mSize;                    //キャラクターの画像のサイズ
	int mMoveSpeed;                   //キャラクターの移動スピード
	int mLife;                        //キャラクターの体力 
	int mLifeMax;                     //キャラクターの体力最大値
	int mAnimCnt;                     //キャラクターのアニメーションの数
	int mWay;						  //3wayの傾き

public:                         //メンバー関数
	CHAR_TYPE mCharType;		//キャラクターの種類
	bool Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY);           //インスタンスの生成処理
	void UpDate(void);         //インスタンスの更新処理
	void Draw(Vector2 pos);    //インスタンスの描画処理
	bool Release(void);        //インスタンスの開放処理
	void CreateShot(Vector2 PlayerPos, DIR PlayerDir, CHAR_TYPE charType, int way);     //弾の座標と向きをターゲットにセット
	int IsAlive(void);       //弾が発射されているか
	Vector2 GetPos(void);     //弾の座標を返す
	Vector2 GetSize(void);	  //画像サイズを返す
	void Destroy(void);		  //画像を消す
};