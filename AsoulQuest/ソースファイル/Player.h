#pragma once
#include "Vector2.h"
#include "GameCommon.h"
class GameScene;

//定数定義	
#define PLAYER_ANIM_COUNT 4 //自機のアニメの最大値

class Player
{
private:                              //メンバー変数
	GameScene* mParent;               //親のインスタンスのポインタ変数
	int mScreenSizeX;                 //画面のXサイズ
	int mScreenSizeY;                 //画面のYサイズ
	int mImage[(int)DIR::DIR_MAX][PLAYER_ANIM_COUNT];    //グラフィックハンドル
	int mDeathImage[3];				  //グラフィックハンドル
	Vector2 mOffset;                  //オフセットの座標
	DIR mKeyDir;                      //キーの制御
	int mCharType;                    //キャラクターの種類
	DIR mMoveDir;                     //キャラクターの向き
	Vector2 mPos;                     //キャラクターの地図上の座標
	Vector2 mSizeOffset;              //キャラクターのオフセットサイズ
	Vector2 mSize;                    //キャラクターの画像のサイズ
	int mMoveSpeed;                   //キャラクターの移動スピード
	int mLifeMax;                     //キャラクターの体力最大値
	int mLifeTime;					  //毒沼にいる時間
	int mAnimCnt;                     //キャラクターのアニメーションの数

	Vector2 mCopyPos;				  //１フレーム前のプレイヤーの座標
	int mPush;                        //キーを押している時間
	bool mShotFlag;					  //プレイヤーが球を発射したか（true:発射）
	bool mWayShotFlag;				  //プレイヤーが3wayを発射したか（true:発射）

public:                        //メンバー関数
	int mPosBottom;            //自機の足元の座標
	bool Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY);           //インスタンスの生成
	void UpDate(void);         //インスタンスの更新処理
	void Draw(void);           //インスタンスの描画処理
	bool Release(void);        //インスタンスの開放処理
	Vector2 GetOffsetPos(void);//座標(背景)を返す
	Vector2 GetPos(void);      //座標を返す
	Vector2 GetSize(void);     //画像のサイズを返す
	DIR GetDir(void);          //自機の向きを返す
	bool IsShot(void);         //プレイヤーが球を発射したかどうか
	bool IsWayShot(void);	   //3wayを撃ったか
	int IsAlive(void);         //生きてる証拠だよ
	void SetPos(Vector2 pos, Vector2 offsetPos);  //プレイヤーの座標をセット
	void Destroy(void);								//プレイヤーのライフを減らす
	void S_Destroy(void);							//シールドの耐久値を減らす
	bool Collsion(Vector2 targetPos, Vector2 targetSize); //衝突判定
	bool GameInit(void);							//プレイヤーの初期化
	void GetShield(void);				//盾を手に入れたら
	void GetHeart(void);			//ハートを手に入れたら
	void UndoPos(void);				//プレイヤーの座標を戻す
	int mLife;                        //キャラクターの体力 
	int mShield;					//シールド耐久値
};