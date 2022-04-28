#pragma once
#include "Stage.h"
#include "Player.h"
#include "Pazzule/Slide.h"
#include "Pazzule/Light.h"
#include "Pazzule/Bucket.h"
#include "Pazzule/Safe.h"
#include "Pazzule/Tips.h"

class GameScene
{
public:
	bool Init(void);
	bool Update(void);
	void Draw(void);
	bool Release(void);

	int GetEvent(Vector2 pos);
	int GetCol(Vector2 pos);	//当たり判定取得関数
	bool SafeCheck(void);		//金庫を開けられるか確認
	bool ClearCheck(void);		//各パズルのクリア確認

	struct Frag
	{
		bool slide;
		bool light;
		bool bucket;
		bool safe;
	};

	Frag flag;		//true：クリア済み
	Frag mSflag;	//true：パズル開始

	bool escapeFlag;//true：脱出可能

private:
	Stage mStage;
	Player mPlayer;

	//パズルクラス
	Slide mSlide;
	Light mLight;
	Bucket mBucket;
	Safe mSafe;

	Tips mTips;	//金庫のパスワード

	int count;

	bool safeCheck;	//金庫を開けられるか？
};