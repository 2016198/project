#pragma once
#include "Vector2.h"
#include "GameCommon.h"

class GameScene;

class Player
{
public:
	bool Init(GameScene* parent);				
	Vector2 Update(void);					
	void Draw(void);					
	void Release(void);					

	//パズルを始めるか調べる
	bool CheckSlide(void);	
	bool CheckLight(void);
	bool CheckBucket(void);
	bool CheckSafe(void);

	bool ClearFlag(void);	//true：魔法陣が光ってGameClearシーンに遷移する準備ができる

	bool back;

	//パズルの管理フラグ
	struct Flag
	{
		bool DrawFlag;
		bool start;
		bool slide;
		bool light;
		bool bucket;
		bool safe;
		bool escape;
	};

	//パズル開始用フラグ
	struct startFlag
	{
		bool slide;
		bool light;
		bool bucket;
		bool safe;
	};

	Flag mFlag;
	startFlag mSFlag;

private:

	//GameSceneの情報格納用
	GameScene* mParent;

	int mImage[static_cast<int>(DIR::MAX)][ANIM_MAX];	//プレイヤー画像格納用

	int mSpeed;

	//プレイヤー座標系
	Vector2 mPos;	
	Vector2 mRayPos;	//当たり判定のチェック用
	Vector2 mOffset;	//Stageに乗るよう座標をずらして描画させる

	int mANIM;
	DIR mMoveDir;							
	int mAnimCnt;							

	bool flag_;

};