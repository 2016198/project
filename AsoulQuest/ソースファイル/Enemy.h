#pragma once
#include "GameCommon.h"
#include "Vector2.h"
class GameScene;

//定数定義
#define ENEMY_ANIM_COUNT 4       //敵のアニメーションの最大値

class Enemy
{

private:
	int mScreenSizeX;              //画面のXサイズ
	int mScreenSizeY;              //画面のYサイズ
	Vector2 mSizeOffset;           //キャラクターのオフセットサイズ
	GameScene* mParent;                              //親のインスタンスのポインタ変数
	int mMoveSpeed[ENEMY_TYPE_MAX] = {               //敵のスピード
		2, 3, 3, 3, 4, 1
	};
	
	Vector2 mSize;										   //画像のサイズ
	Vector2 mPos;                                          //座標成分
	DIR mMoveDir;                                          //キャラクターの向き
	Vector2 mOffset;                                       //オフセットの座標
	int mLife;									   		   //キャラクターの体力
	int mLifeMax;									       //キャラクターの体力最大値
	int mAnimCnt;										   //キャラクターのアニメーションの数
	int mCharType;                                         //キャラクターの種類
	int mLifeDec;                                          //弾が一発当たったら減る数
	Vector2 mTargetPos;									   //対象の座
	int EnemyMoveX(int* EnemyPosX, int enemySpeed, int targetPosX, DIR* move);								//X座標を合わせる
	int EnemyMoveY(int* EnemyPosX, int enemySpeed, int targetPosY, DIR* move);								//Y座標を合わせる
	int EnemyMoveXY(int* enemyPosX, int* enemyPosY, int targetPosX, int targetPosY, int enemySpeed);        //距離が長いほうから合わせる

public:
	int mPosBottom;																					   //敵の足元の座標
	bool Init(GameScene* parent, int enemyType, int ScreenSizeX, int ScreenSizeY, Vector2 pos);        //インスタンスの生成
	void UpDate(Vector2 PlayerPos);                                                                    //インスタンスの更新処理
	void Draw(Vector2 pos);                                                                            //インスタンスの描画処理
	bool Release(void);                                                                                //インスタンスの開放処理
	Vector2 GetPos(void);																			   //座標を返す
	DIR GetDir(void);																				   //キャラクターの向きを変えす
	Vector2 GetSize(void);																			   //画像サイズを返す
	int GetType(void);																				   //敵の種類を返す
	void Destroy(void);		      																	   //画像を消す
	int IsAlive(void);                                                                                 //生きてるかどうか
	bool Collsion(Vector2 targetPos, Vector2 targetSize);											   //敵の当たり判定
};