//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

//親のインスタンス
class GameScene;

class Player
{
	enum class ACTION	//プレイヤーのアクション
	{
		IDLE,		//0
		JUMP,		//1
		RUN,		//2
		DAMAGED,	//3
		MAX			//4
	};

	//弾の発射状態
	enum class SHOT_STYLE
	{
		NORMAL,		//発射していない
		SHOT,		//発射している
		MAX
	};

	//プレイヤーのスピード
	static constexpr float MAX_MOVE_SPEED = 3.5f;	//最大値
	static constexpr float MOVE_ADD = 0.25f;		//加速
	static constexpr float MOVE_DEC = 0.05f;		//減速

	//ジャンプ
	static constexpr float GRAVITY = 0.5f;		//重力加速度
	static constexpr float V0 = 10.0f;			//初速
	static constexpr int JUMP_POWER_MAX = 10;	//ジャンプ力の最大値

	//アニメーション
	static constexpr int ANIM_MAX = 4;			//アニメーションの数
	static constexpr int ANIM_LOCK_FLAME = 60;	//アニメーション用変数

private:						//メンバー変数
	GameScene* mParent;			//親のインスタンス格納変数
	PLAYER_TYPE mPlayerType;	//プレイヤーの種別(PLAYER1 or PLAYER2)
	Vector2 mPos;				//プレイヤーの座標
	ACTION mAction;				//プレイヤーの状態
	//int mShot;					//プレイヤーが発射したかどうか
	DIR mDir;					//プレイヤーの向き
	Vector2 mHitLT;				//mHitLeftTopプレイヤーの当たり判定の左上
	Vector2 mHitRB;				//mHitRightBottomプレイヤーの当たり判定の右上
	float mMoveSpeed;			//プレイヤーの速さ
	int mAnimCount;				//アニメーション変数
	int mAnimLockCnt;			//アニメーションロック変数
	//					↓アクション　　						↓ショット　			↓アニメ
	int mActionImage[static_cast<int>(ACTION::MAX)][static_cast<int>(SHOT_STYLE::MAX)][ANIM_MAX]; //プレイヤーの画像

	bool mIsDrop;				//落下中かどうか
	float mJumpSpeed;			//ジャンプのスピード
	int mJumpPower;				//ジャンプのパワー
	bool mIsJump;				//ジャンプしているかどうか
	bool mIsRun;				//走っているかどうか

	bool mIsLift;				//リフトに乗っているか
	bool mIsShot;				//弾を撃ったかどうか
	//関数
	bool LoadImages(PLAYER_TYPE playerType);		//プレイヤーの画像の読み込み
	void MoveX(void);			//左右移動の処理
	void JumpY(void);			//ジャンプの処理

public:
	Player(GameScene* parent, PLAYER_TYPE playerType);	//コンストラスタ

	bool IsShot(void);			//弾を撃ったかどうか
	bool IsJump(void);			//ジャンプをしているかどうか
	DIR GetDir(void);			//プレイヤーの向きをもらう
	Vector2 RiadLift(Vector2 liftPos, Vector2 copyPosB);	//リフトに乗った時の処理
	Vector2 GetShotPos(void);	//弾の発射中心位置

	bool Init(void);			//インスタンスの生成
	Vector2 UpDate(void);		//インスタンスの更新
	void Draw(void);			//インスタンスの描画
	bool Release(void);			//インスタンスの開放

	~Player(void);				//デストラスタ

};
