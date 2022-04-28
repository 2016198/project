#include <DxLib.h>
#include "Player.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Player:: Init(GameScene* parent)
{

	//プレイヤー画像の読み込み
	if (LoadDivGraph("image/chara/pipo-charachip001.png", 12, 3, 4, 32, 32,
		&mImage[0][0]) == -1)
	{
		return false;
	}

	//親インスタンスの格納
	mParent = parent;	
	
	mSpeed = 3;
	mPos = { 100,100 };
	mOffset = { 16,16 };
	mAnimCnt = 0;
	mANIM = 0;
	mMoveDir = DIR::DOWN;

	return true;
}
Vector2 Player::Update(void)
{
	flag_ = false;
	back = false;

	//パズルの管理フラグ
	mFlag.DrawFlag = false;
	mFlag.start = false;
	mFlag.slide = false;
	mFlag.light = false;
	mFlag.bucket = false;
	mFlag.safe = false;
	mFlag.escape = false;

	//パズル開始フラグ
	mSFlag.slide = false;
	mSFlag.light = false;
	mSFlag.bucket = false;
	mSFlag.safe = false;

	Vector2 copyPos;
	copyPos = mPos;
	mRayPos = mPos;

	DIR keyDir = DIR::MAX;
	mAnimCnt++;

	//アニメーション
	if (mAnimCnt / 20 % 4 == 0)
	{
		mANIM = 1;
	}
	else if (mAnimCnt / 20 % 4 == 1)
	{
		mANIM = 0;
	}
	else if (mAnimCnt / 20 % 4 == 2)
	{
		mANIM = 1;
	}
	else if (mAnimCnt / 20 % 4 == 3)
	{
		mANIM = 2;
	}

	//R_SHIFTキーでダッシュ
	if (CheckHitKey(KEY_INPUT_RSHIFT) == 1)
	{
		mSpeed = 6;
	}
	else
	{
		mSpeed = 3;
	}

	//WASDで移動
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		if (mPos.y - 8 > 0)
		{
			mPos.y -= mSpeed;
			mMoveDir = DIR::UP;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		if ((mPos.x - 8) > 0)
		{
			mPos.x -= mSpeed;
			mMoveDir = DIR::LEFT;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		if (mPos.y + 16 < 480 - 64)
		{
			mPos.y += mSpeed;
			mMoveDir = DIR::DOWN;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		if (mPos.x + 8 < 640 - 64)
		{
			mPos.x += mSpeed;
			mMoveDir = DIR::RIGHT;
		}
	}


	//オブジェクトの種類別の処理
	switch (mParent->GetCol(mPos))
	{
	case 228://魔法陣
	{
		mFlag.escape = true;
		if (CheckHitKey(KEY_INPUT_Z))//クリア遷移
		{
			flag_ = true;
		}
	}
	break;

	//通れないオブジェクト
	case 158:
	case 327:
	case 326:
	case 207:
	case 297:
	case 203:
	case 134:
	case 201:
	case 205:
	case 206:
	case 275:
	case 227:
	case 251:
	case 179:
		mPos = copyPos;
		break;

	//一部オブジェクトの後ろを通過したらプレイヤーが消える処理
	case 303:
	case 302:
	case 183:
		back = true;
		break;
	}

	switch (mMoveDir)
	{
	case DIR::DOWN:
		mRayPos.y += 20;
		break;
	case DIR::LEFT:
		mRayPos.x -= 20;
		break;
	case DIR::RIGHT:
		mRayPos.x += 20;
		break;
	case DIR::UP:
		mRayPos.y -= 20;
		break;
	case DIR::MAX:
		break;
	}

	//一部オブジェクトの後ろを通過したらプレイヤーが消える処理
	//プレイヤーがオブジェクトを貫通するのでもう一回処理する
	switch (mParent->GetCol(mPos))
	{
	case 303:
	case 302:
	case 183:
		back = true;
	}

	//謎解き画面に遷移するためのフラグ管理
	switch (mParent->GetEvent(mRayPos))
	{
		//バケツゲーム
	case 297:
		mFlag.DrawFlag = true;
		mFlag.bucket = true;
		break;

		//ライトブロック
	case 326:
		mFlag.DrawFlag = true;
		mFlag.light = true;
		break;

		//スライドパズル
	case 203:
		mFlag.DrawFlag = true;
		mFlag.slide = true;
		break;

		//金庫
	case 134:
		mFlag.DrawFlag = true;
		mFlag.safe = true;
		break;
	}

	//謎解き画面に遷移
	if (mFlag.slide == true && CheckHitKey(KEY_INPUT_Z))
	{
		//スライドパズル
		mSFlag.slide = true;
	}
	if (mFlag.light == true && CheckHitKey(KEY_INPUT_Z))
	{
		//ライトブロック
		mSFlag.light = true;
	}
	if (mFlag.bucket == true && CheckHitKey(KEY_INPUT_Z))
	{
		//バケツゲーム
		mSFlag.bucket = true;
	}
	if (mFlag.safe == true && CheckHitKey(KEY_INPUT_Z))
	{
		//金庫
		mSFlag.safe = true;
	}

	return mPos;

}
void Player::Draw(void)
{
	DrawGraph(mPos.x + mOffset.x, mPos.y + mOffset.y, mImage[static_cast<int>(mMoveDir)][mANIM], true);

	//イベントの呼び出しと確認
	DrawFormatString(0, 0, 0xffffff, "%d", mParent->GetEvent(mPos));
	DrawFormatString(30, 0, 0xffffff, "%d", mParent->GetEvent(mRayPos));
	DrawBox(0, 0, 100, 16, 0x000000, true);	//↑をプレイの邪魔にならないよう隠す

	if (mFlag.DrawFlag == true)
	{
		DrawString(0, 480-16, "Zキーで調べる", 0xffffff, true);
	}

	if (mParent->escapeFlag == true && mFlag.escape == true)
	{
		DrawString(0, 480 - 16, "Zキーで帰る", 0xffffff, true);

	}
}
void Player::Release(void)
{
	for (int y = 0; y < ANIM_MAX; y++)
	{
		for (int x = 0; x < static_cast<int>(DIR::MAX); x++)
		{
			DeleteGraph(mImage[x][y]);
		}
	}
}

bool Player::CheckSlide(void)
{
	if (mSFlag.slide)
	{
		return true;
	}
	return false;
}

bool Player::CheckLight(void)
{
	if (mSFlag.light)
	{
		return true;
	}
	return false;
}

bool Player::CheckBucket(void)
{
	if (mSFlag.bucket)
	{
		return true;
	}
	return false;
}

bool Player::CheckSafe(void)
{
	if (mSFlag.safe)
	{
		return true;
	}
	return false;
}

bool Player::ClearFlag(void)
{
	if (flag_)
	{
		return true;
	}
	return false;
}
