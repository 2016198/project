#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "Shot.h"
#include "GameScene.h"

#define SHOT_IMAGE_SIZE_X 16
#define SHOT_IMAGE_SIZE_Y 16

bool Shot::Init(void)//インスタンスの初期化
{
	mPos = Vector2(100, 100);
	mMoveSpeed = 0;
	mLife = 0;
	return true;
}

Vector2 Shot::UpDate(void)//インスタンスの更新
{
	Vector2 copyPos = mPos;
	if (mLife > 0)
	{
		copyPos.x += mMoveSpeed;
		mLife--;
		switch (mParent->GetEvent(copyPos))
		{
		case 8:
		case 9:
		case 11:
		case 12:
			//壁の中に埋まって弾を消す処理
			mLife = 0;
			break;
		default:
			mPos = copyPos;
			break;
		}
	}
	return mPos;
}

void Shot::Draw(void)//インスタンスの描画
{
	if (mLife > 0)
	{
		DrawGraph(mPos.x - SHOT_IMAGE_SIZE_X / 2, mPos.y - SHOT_IMAGE_SIZE_Y / 2, mImage, true);
	}
}

bool Shot::Release(void)//インスタンスの開放
{
	DeleteGraph(mImage);
	return true;
}

void Shot::CreateShot(Vector2 targetPos, DIR targetDir)//弾の発射
{
	mPos = targetPos;
	mLife = SHOT_MAX_LIFE;
	if (targetDir == DIR::LEFT)
	{
		mMoveSpeed = -SHOT_MAX_SPEED;
	}
	else
	{
		mMoveSpeed = SHOT_MAX_SPEED;
	}
}

bool Shot::IsAlive(void)//弾が表示されているか
{
	if (mLife > 0)
	{
		return true;
	}
	return false;
}

void Shot::Destroy(void)//画像を消す
{
	mLife = 0;
}

Shot::Shot(GameScene* parent)//コンストラスタ
{
	//親のポインタ変数格納
	mParent = parent;
	//画像のロード
	mImage = LoadGraph("Image/Player/P1/Shot.png");
}

Shot::~Shot(void) //デストラスタ
{

}