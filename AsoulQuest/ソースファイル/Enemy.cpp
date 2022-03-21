#include "Enemy.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Enemy::Init(GameScene* parent, int enemyType, int ScreenSizeX, int ScreenSizeY, Vector2 pos)  //インスタンスの初期化処理
{
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	switch (enemyType)
	{
	case ENEMY_TYPE_SLIME:
		mSize.x = 24;
		mSize.y = 32;
		mLifeDec = 50;
		break;
	case ENEMY_TYPE_BEE:
		mSize.x = 24;
		mSize.y = 32;
		mLifeDec = 25;
		break;
	case ENEMY_TYPE_FLAME:
		mSize.x = 24;
		mSize.y = 32;
		mLifeDec = 25;
		break;
	case ENEMY_TYPE_R_DRAGON:
		mSize.x = 24;
		mSize.y = 32;
		mLifeDec = 20;
		break;
	case ENEMY_TYPE_B_DRAGON:
		mSize.x = 48;
		mSize.y = 64;
		mLifeDec = 10;
		break;
	case ENEMY_TYPE_BOSS:
		mSize.x = 96;
		mSize.y = 128;
		mLifeDec = 2;
		break;
	case ENEMY_TYPE_MAX:
		break;
	default:
		break;
	}
	mParent = parent;
	mPos.x = pos.x;
	mPos.y = pos.y;
	mSizeOffset.x = mSize.x / 2;
	mSizeOffset.y = mSize.y / 2;
	mMoveDir = DIR::DIR_DOWN;
	mAnimCnt = 0;
	mCharType = enemyType;
	mLifeMax = LIFE_COUNT;
	mLife = mLifeMax;
	mPosBottom = mPos.y + mSizeOffset.y;
	return true;
}
void Enemy::UpDate(Vector2 PlayerPos)//インスタンスの更新処理
{
	mTargetPos = PlayerPos;
	if (mAnimCnt % 60 > 40)
	{
		switch (mCharType)
		{
		case ENEMY_TYPE_SLIME:		//スライム
		case ENEMY_TYPE_R_DRAGON:   //赤ドラゴン
			if (EnemyMoveX(&mPos.x, mMoveSpeed[mCharType], mTargetPos.x, &mMoveDir) == 0)
			{
				EnemyMoveY(&mPos.y, mMoveSpeed[mCharType], mTargetPos.y, &mMoveDir);
			}
			break;
		case ENEMY_TYPE_FLAME:		//炎
		case ENEMY_TYPE_B_DRAGON:   //青ドラゴン
			if (EnemyMoveY(&mPos.y, mMoveSpeed[mCharType], mTargetPos.y, &mMoveDir) == 0)
			{
				EnemyMoveX(&mPos.x, mMoveSpeed[mCharType], mTargetPos.x, &mMoveDir);
			}
			break;
		case ENEMY_TYPE_BEE:		//蜂
		case ENEMY_TYPE_BOSS:       //ボス
			EnemyMoveXY(&mPos.x, &mPos.y, mTargetPos.x, mTargetPos.y, mMoveSpeed[mCharType]);
			break;
		default:
			break;
		}
	}
	mPosBottom = mPos.y + mSizeOffset.y;
	mAnimCnt++;
}
void Enemy::Draw(Vector2 pos)//インスタンスの描画処理
{
	mOffset.x = pos.x;
	mOffset.y = pos.y;
	if (mLife > 0)
	{
		DrawGraph(mPos.x - mSizeOffset.x - mOffset.x,
			mPos.y - mSizeOffset.y - mOffset.y,
			mParent->mEnemyImage[mCharType][(mAnimCnt / 10) % 4 + ((int)mMoveDir * 4)],
			true);
	}
	/*DrawBox(mPos.x - mOffset.x - mSizeOffset.x,
		mPos.y - mOffset.y - mSizeOffset.y,
		mPos.x - mOffset.x + mSize.x - mSizeOffset.x,
		mPos.y - mOffset.y + mSize.y - mSizeOffset.y,
		GetColor(255, 255, 255), false);*/
}
bool Enemy::Release(void)  //インスタンスの開放処理
{
	return true;
}

Vector2 Enemy::GetPos(void) //座標を返す
{
	return mPos;
}

DIR Enemy::GetDir(void)//キャラクターの向きを返す
{
	return mMoveDir;
}

int Enemy::EnemyMoveX(int* EnemyPosX, int enemySpeed, int targetPosX, DIR* move)
{
	int diff = targetPosX - *EnemyPosX; //差分をとる

	//X座標を合わせる
	if (diff < 0) //プレイヤーが左にいる
	{
		if (-diff > enemySpeed)  //プレイヤーと敵の距離が敵のスピードより小さくなったら
		{
			*EnemyPosX -= enemySpeed;
		}
		else
		{
			*EnemyPosX += diff;
		}
		*move = DIR::DIR_LEFT;
	}
	else if (diff > 0) //プレイヤーが右にいる
	{
		if (diff > enemySpeed)  //プレイヤーと敵の距離が敵のスピードより小さくなったら
		{
			*EnemyPosX += enemySpeed;
		}
		else
		{
			*EnemyPosX += diff;
		}
		*move = DIR::DIR_RIGHT;
	}
	return diff;
}

int Enemy::EnemyMoveY(int* EnemyPosY, int enemySpeed, int targetPosY, DIR* move)
{
	int diff = targetPosY - *EnemyPosY; //差分をとる

	//Y座標を合わせる
	if (diff < 0) //プレイヤーのほうが上にいる
	{
		if (-diff > enemySpeed)  //プレイヤーと敵の距離が敵のスピードより小さくなったら
		{
			*EnemyPosY -= enemySpeed;
		}
		else
		{
			*EnemyPosY += diff;
		}
		*move = DIR::DIR_UP;
	}
	else if (diff > 0) //プレイヤーのほうが下にいる
	{
		if (diff > enemySpeed)  //プレイヤーと敵の距離が敵のスピードより小さくなったら
		{
			*EnemyPosY += enemySpeed;
		}
		else
		{
			*EnemyPosY += diff;
		}
		*move = DIR::DIR_DOWN;
	}
	return diff;
}

//戻り値：プレイヤーと敵のX座標とY座標の差分の大きいほうを返す
int Enemy::EnemyMoveXY(int* enemyPosX, int* enemyPosY, int targetPosX, int targetPosY, int enemySpeed)
{
	//距離の計算する
	int diffX2 = (targetPosX - *enemyPosX) * (targetPosX - *enemyPosX);
	int diffY2 = (targetPosY - *enemyPosY) * (targetPosY - *enemyPosY);

	//距離に合わせて移動させる
	if (diffX2 > diffY2)
	{
		//X方向に移動させる
		return EnemyMoveX(enemyPosX, enemySpeed, targetPosX, &mMoveDir);
	}
	else
	{
		//Y方向に移動させる
		return EnemyMoveY(enemyPosY, enemySpeed, targetPosY, &mMoveDir);
	}
}

Vector2 Enemy::GetSize(void)//画像のサイズを返す
{
	return mSizeOffset;
}

void Enemy::Destroy(void)//敵を消す
{
	mLife -= mLifeDec;
}

int Enemy::IsAlive(void) //生きてるかどうか
{
	return mLife;
}

bool Enemy::Collsion(Vector2 targetPos, Vector2 targetSize)//衝突対象との座標と画像サイズ
{
	if (targetPos.x + targetSize.x / 2 > mPos.x - mSize.x / 2  &&
		targetPos.x - targetSize.x / 2 < mPos.x + mSize.x / 2 &&
		targetPos.y + targetSize.y / 2 > mPos.y - mSize.y / 2 &&
		targetPos.y - targetSize.y / 2 < mPos.y + mSize.y / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Enemy::GetType(void) //敵の種類を返す
{
	return mCharType;
}