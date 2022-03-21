#include "Player.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Player::Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY)  //インスタンスの生成
{
	mLifeTime = 0;
	mShield = 0;
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mParent = parent;
	mMoveDir = DIR::DIR_DOWN;
	mAnimCnt = 0;
	mPos.x = 110;
	mPos.y = 110;
	mSize.x = 24;
	mSize.y = 32;
	mSizeOffset.x = mSize.x / 2;
	mSizeOffset.y = mSize.y / 2;
	mOffset.x = 0;
	mOffset.y = 0;
	mMoveSpeed = 3;
	if ((LoadDivGraph("image/bakuha.bmp", 3, 3, 1, mSize.x, mSize.y, &mDeathImage[0])) == -1)
	{
		return false;
	}
	LoadDivGraph("image/player.bmp",
		PLAYER_ANIM_COUNT * (int)DIR::DIR_MAX,
		PLAYER_ANIM_COUNT,
		(int)DIR::DIR_MAX,
		mSize.x,
		mSize.y,
		&mImage[0][0]);
	mLifeMax = LIFE_COUNT;
	mLife = mLifeMax;
	mPosBottom = mPos.y + mSizeOffset.y;
	return true;
}

void Player::UpDate(void)   //インスタンスの更新
{
	mKeyDir = DIR::DIR_MAX;
	mCopyPos = mPos;
	if (KeyNow[KEY_P1_DOWN])
	{
		mKeyDir = DIR::DIR_DOWN;
	}
	if (KeyNow[KEY_P1_UP])
	{
		mKeyDir = DIR::DIR_UP;
	}
	if (KeyNow[KEY_P1_LEFT])
	{
		mKeyDir = DIR::DIR_LEFT;
	}
	if (KeyNow[KEY_P1_RIGHT])
	{
		mKeyDir = DIR::DIR_RIGHT;
	}
	//プレイヤーの移動処理
	if (mKeyDir != DIR::DIR_MAX)
	{
		if (KeyNow[KEY_P1_DOWN] && mKeyDir == DIR::DIR_DOWN)
		{
			if (mOffset.y < MAP_Y * CHIP_SIZE_Y - mScreenSizeY)
			{
				if (mPos.y - mOffset.y >= mScreenSizeY * 3 / 4)
				{
					mOffset.y += mMoveSpeed;
				}
			}
			else
			{
				mOffset.y = MAP_Y * CHIP_SIZE_Y - mScreenSizeY;
			}
			if (mPos.y < MAP_Y * CHIP_SIZE_Y)
			{
				mPos.y += mMoveSpeed;
				mMoveDir = DIR::DIR_DOWN;
			}
			else
			{
				mPos.y = MAP_Y * CHIP_SIZE_Y;
			}
		}
		if (KeyNow[KEY_P1_UP] && mKeyDir == DIR::DIR_UP)
		{
			if (mOffset.y > 0)
			{
				if (mPos.y - mOffset.y <= mScreenSizeY / 4)
				{
					mOffset.y -= mMoveSpeed;
				}
			}
			else
			{
				mOffset.y = 0;
			}
			if (mPos.y > 0)
			{
				mPos.y -= mMoveSpeed;
				mMoveDir = DIR::DIR_UP;
			}
			else
			{
				mPos.y = 0;
			}
		}
		if (KeyNow[KEY_P1_LEFT] && mKeyDir == DIR::DIR_LEFT)
		{
			if (mOffset.x > 0)
			{
				if (mPos.x - mOffset.x <= mScreenSizeX / 4)
				{
					mOffset.x -= mMoveSpeed;
				}
			}
			else
			{
				mOffset.x = 0;
			}
			if (mPos.x > 0)
			{
				mPos.x -= mMoveSpeed;
				mMoveDir = DIR::DIR_LEFT;
			}
			else
			{
				mPos.x = 0;
			}
		}
		if (KeyNow[KEY_P1_RIGHT] && mKeyDir == DIR::DIR_RIGHT)
		{
			if (mOffset.x < MAP_X * CHIP_SIZE_X - mScreenSizeX)
			{
				if (mPos.x - mOffset.x >= mScreenSizeX * 3 / 4)
				{
					mOffset.x += mMoveSpeed;
				}
			}
			else
			{
				mOffset.x = MAP_X * CHIP_SIZE_X - mScreenSizeX;
			}
			if (mPos.x < MAP_X * CHIP_SIZE_X)
			{
				mPos.x += mMoveSpeed;
				mMoveDir = DIR::DIR_RIGHT;
			}
			else
			{
				mPos.x = MAP_X * CHIP_SIZE_X;
			}
		}
	}
	switch (mParent->GetEvent(mPos))     //マップの情報を受けとる
	{
	case 0:
	case 14:
		mMoveSpeed = 5;
		break;
	case 1:
	case 3:
	case 4:
	case 11:
	case 12:
	case 2:
	case 61:
	case 9:
		UndoPos();
		break;
	case 21:
	case 22:
	case 23:
	case 30:
	case 31:
	case 32:
	case 39:
	case 40:
	case 41:
	case 58:
		mMoveSpeed = 8;
		break;
	case 24:
	case 25:
	case 26:
	case 33:
	case 34:
	case 35:
	case 42:
	case 43:
	case 44:
		mLifeTime++;
		if (mLifeTime % 100 == 1)
		{
			mLife--;
		}
		break;
	default:
		break;
	}
	mShotFlag = KeyTrgDown[KEY_P1_A];
	mWayShotFlag = KeyTrgDown[KEY_P1_B];
	mPosBottom = mPos.y + mSizeOffset.y;
	mAnimCnt++;
}

void Player::Draw(void)  //インスタンスの描画
{
	if (mShield > 0)
	{
		DrawCircle(mPos.x - mOffset.x, mPos.y - mOffset.y + 2, 14, GetColor(rand() % 256, rand() % 256, rand() % 256), false);
	}
	if (mLife > 0)
	{
		DrawGraph(mPos.x - mSizeOffset.x - mOffset.x, mPos.y - mSizeOffset.y - mOffset.y, mImage[(int)mMoveDir][(mAnimCnt / 10) % 4], true);
	}
	else
	{
		DrawGraph(mPos.x - mSizeOffset.x - mOffset.x, mPos.y - mSizeOffset.y - mOffset.y, mDeathImage[0], true);
	}
	
	/*DrawCircle(mPos.x - mOffset.x, mPos.y - mOffset.y, 1, GetColor(255, 255, 255));
	DrawBox(640 / 4, 480 / 4, 640 * 3 / 4, 480 * 3 / 4, GetColor(255, 255, 0), 0);
	DrawLine(320, 0, 320, 480, GetColor(255, 255, 0));
	DrawLine(0, 240, 640, 240, GetColor(255, 255, 0));*/
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d:::%d", mPos.x, mPos.y);
	//DrawFormatString(0, 0, GetColor(150, 0, 255), "\nCHIP::%d", mParent->GetEvent(mPos));
}

bool Player::Release(void) //インスタンスの開放
{
	for (int x = 0; x < (int)DIR::DIR_MAX; x++)
	{
		for (int y = 0; y < PLAYER_ANIM_COUNT; y++)
		{
			DeleteGraph(mImage[x][y]);
		}
	}
	for (int p = 0; p < 3; p++)
	{
		DeleteGraph(mDeathImage[p]);
	}
	return true;
}

Vector2 Player::GetOffsetPos(void)  //座標(背景)を返す
{
	return mOffset;
}

Vector2 Player::GetPos(void)  //座標(自機)を返す
{
	return mPos;
}

DIR Player::GetDir(void)  //向きを返す
{
	return mMoveDir;
}

bool Player::IsShot(void) //弾を撃ったか
{
	return mShotFlag;
}

bool Player::IsWayShot(void) //3wayを撃ったか
{
	return mWayShotFlag;
}

int Player::IsAlive(void)//生きてる証拠だよ
{
	return mLife;
}

Vector2 Player::GetSize(void) //画像のサイズを返す
{
	return mSizeOffset;
}

void Player::SetPos(Vector2 pos, Vector2 offsetPos) //座標を受け取る
{
	mPos = pos;
	mOffset = offsetPos;
}

void Player::Destroy(void) //弾に当たった時の処理
{
	mLife -= 10;
}

void Player::S_Destroy(void) //弾に当たった時の処理(シールドを持っているとき)
{
	mShield -= 10;
}

void Player::GetShield(void)	//盾を入手したら
{
	mShield = 100;
}

void Player::GetHeart(void)	//ハートを入手したら
{
	mLife = mLifeMax;
}

bool Player::Collsion(Vector2 targetPos, Vector2 targetSize)//衝突対象との座標と画像サイズ
{
	if (targetPos.x + targetSize.x / 2 > mPos.x - mSize.x / 2 &&
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

bool Player::GameInit(void)	//プレイヤーの初期化
{
	mLifeTime = 0;
	mShield = 0;
	mMoveDir = DIR::DIR_DOWN;
	mAnimCnt = 0;
	mPos.x = 110;
	mPos.y = 110;
	mSize.x = 24;
	mSize.y = 32;
	mSizeOffset.x = mSize.x / 2;
	mSizeOffset.y = mSize.y / 2;
	mOffset.x = 0;
	mOffset.y = 0;
	mMoveSpeed = 3;

	mLifeMax = LIFE_COUNT;
	mLife = mLifeMax;
	mPosBottom = mPos.y + mSizeOffset.y;
	return true;
}

void Player::UndoPos(void)//プレイヤーの座標を戻す
{
	mPos = mCopyPos;
}
