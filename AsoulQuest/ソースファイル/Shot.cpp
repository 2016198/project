#include "Shot.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "GameScene.h"

#define SHOT_LIFE_MAX 40

bool Shot::Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY)  //�C���X�^���X�̐�������
{
	mWay = 0;
	mCharType = CHAR_TYPE::PLAYER;
	mParent = parent;
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mSize.x = 12;
	mSize.y = 12;
	mPos.x = 0;
	mPos.y = 0;
	mMoveSpeed = 8;
	mSizeOffset.x = mSize.x / 2;
	mSizeOffset.y = mSize.y / 2;
	mAnimCnt = 0;
	mMoveDir = DIR::DIR_DOWN;
	mLifeMax = SHOT_LIFE_MAX;
	mLife = 0;
	return true;
}

void Shot::UpDate(void) //�C���X�^���X�̍X�V����
{
	//mMoveDir = move;
	if (mLife > 0)
	{
		switch (mMoveDir)
		{
		case DIR::DIR_UP:
			mPos.y -= mMoveSpeed;
			if (mWay == 1)
			{
				mPos.x -= 2;
			}
			else if(mWay == 2)
			{
				mPos.x += 2;
			}
			mLife--;
			break;
		case DIR::DIR_RIGHT:
			mPos.x += mMoveSpeed;
			if (mWay == 1)
			{
				mPos.y -= 2;
			}
			else if (mWay == 2)
			{
				mPos.y += 2;
			}
			mLife--;
			break;
		case DIR::DIR_DOWN:
			mPos.y += mMoveSpeed;
			if (mWay == 1)
			{
				mPos.x -= 2;
			}
			else if (mWay == 2)
			{
				mPos.x += 2;
			}
			mLife--;
			break;
		case DIR::DIR_LEFT:
			mPos.x -= mMoveSpeed; 
			if (mWay == 1)
			{
				mPos.y -= 2;
			}
			else if (mWay == 2)
			{
				mPos.y += 2;
			}
			mLife--;
			break;
		case DIR::DIR_MAX:
			break;
		default:
			break;
		}
	}
	mAnimCnt++;
}

void Shot::Draw(Vector2 pos) //�C���X�^���X�̕`�揈��
{
	mOffset.x = pos.x;
	mOffset.y = pos.y;
	if (mLife > 0)
	{
		switch (mCharType)
		{
		case CHAR_TYPE::PLAYER:
			DrawGraph(mPos.x - mOffset.x - mSizeOffset.x, mPos.y - mOffset.y - mSizeOffset.y, mParent->mP_ShotImage[(mAnimCnt / 10) % SHOT_IMAGE_COUNT], true);
			break;
		case CHAR_TYPE::ENEMY:
			DrawGraph(mPos.x - mOffset.x - mSizeOffset.x, mPos.y - mOffset.y - mSizeOffset.y, mParent->mE_ShotImage[(mAnimCnt / 10) % SHOT_IMAGE_COUNT], true);
			break;
		default:
			break;
		}	
	}
	/*DrawBox(mPos.x - mOffset.x - mSizeOffset.x,
		mPos.y - mOffset.y - mSizeOffset.y,
		mPos.x - mOffset.x + mSize.x - mSizeOffset.x,
		mPos.y - mOffset.y + mSize.y - mSizeOffset.y,
		GetColor(255, 255, 255), false);*/
}

bool Shot::Release(void) //�C���X�^���X�̊J������
{
	return true;
}

Vector2 Shot::GetPos(void)//���W��Ԃ�
{
	return mPos;
}

void Shot::CreateShot(Vector2 targetPos, DIR targetDir, CHAR_TYPE charType, int way)  //�e�𔭎˂���
{
	mCharType = charType;
	switch (charType)
	{
	case CHAR_TYPE::PLAYER:
		mLife = mLifeMax;
		mWay = 0;
		mMoveSpeed = 8;
		break;
	case CHAR_TYPE::ENEMY:
		mLife = mLifeMax * 2;
		mMoveSpeed = 4;
		break;
	default:
		break;
	}
	mPos = targetPos;
	mMoveDir = targetDir;
	mWay = way;
}

int Shot::IsAlive(void) //�e�����˂���Ă��邩
{
	return mLife;
}

Vector2 Shot::GetSize(void) //�摜�̃T�C�Y��Ԃ�
{
	return mSizeOffset;
}

void Shot::Destroy(void) //�e������
{
	mLife = 0;
}