#include "LifeBar.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool LifeBar::init(GameScene* parent, int type)  //�C���X�^���X�̐�������
{
	mParent = parent;
	mPos.x = 0;
	mPos.y = 0;
	mOffset.x = 0;
	mOffset.y = 0;
	mSizeOffset.x = 12;
	mSizeOffset.y = 5;
	mType = type;
	return true;
}

void LifeBar::UpDate(Vector2 pos)//�C���X�^���X�̍X�V����
{
	mPos = pos;
	switch (mType)
	{
	case ENEMY_TYPE_SLIME:    //�X���C��
		mPos.y = mPos.y - 16;
		break;
	case ENEMY_TYPE_BEE:      //�I
		mPos.y = mPos.y - 16;
		break;
	case ENEMY_TYPE_FLAME:    //��
		mPos.y = mPos.y - 16;
		break;
	case ENEMY_TYPE_R_DRAGON: //�ԃh���S��
		mPos.y = mPos.y - 16;
		break;
	case ENEMY_TYPE_B_DRAGON: //�h���S��
		mPos.y = mPos.y - 32;
		break;
	case ENEMY_TYPE_BOSS:  //�{�X
		mPos.y = mPos.y - 64;
		break;
	case ENEMY_TYPE_MAX:  //�v���C���[
		mPos.y = mPos.y - 16;
		break;
	default:
		break;
	}
}

void LifeBar::Draw(int life, Vector2 pos)//�C���X�^���X�̕`�揈��
{
	mOffset = pos;
	if (life > 0)
	{
		switch (life / (LIFE_COUNT / (LIFE_ANIM_COUNT + 1)))
		{
		case 4:
			DrawGraph(mPos.x - mOffset.x - mSizeOffset.x, mPos.y - mOffset.y - mSizeOffset.y, mParent->mLifeBarImage[0], true);
			break;
		case 3:
			DrawGraph(mPos.x - mOffset.x - mSizeOffset.x, mPos.y - mOffset.y - mSizeOffset.y, mParent->mLifeBarImage[1], true);
			break;
		case 2:
			DrawGraph(mPos.x - mOffset.x - mSizeOffset.x, mPos.y - mOffset.y - mSizeOffset.y, mParent->mLifeBarImage[2], true);
			break;
		case 1:
		case 0:
			DrawGraph(mPos.x - mOffset.x - mSizeOffset.x, mPos.y - mOffset.y - mSizeOffset.y, mParent->mLifeBarImage[3], true);
			break;
		default:
			break;
		}
	}
}

bool LifeBar::Release(void)//�C���X�^���X�̊J������
{
	return true;
}