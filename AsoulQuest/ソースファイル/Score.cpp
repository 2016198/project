#include "Score.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

bool Score::Init(void)//����������
{
	mType = 0;
	mOffset.x = 0;
	mOffset.y = 0;
	mPos.x = 0;
	mPos.y = 0;
	mLife = 0;
	return true;
}

void Score::UpDate(void)  //�X�V����
{
	if (mLife == 30)
	{
		switch (mType)
		{
		case ENEMY_TYPE_SLIME:    //�X���C��
			mPos.y = mPos.y - 16;
			mColor = GetColor(100, 100, 100);
			break;
		case ENEMY_TYPE_BEE:      //�I
			mPos.y = mPos.y - 16;
			mColor = GetColor(0, 255, 0);
			break;
		case ENEMY_TYPE_FLAME:    //��
			mPos.y = mPos.y - 16;
			mColor = GetColor(255, 0, 0);
			break;
		case ENEMY_TYPE_R_DRAGON: //�ԃh���S��
			mPos.y = mPos.y - 16;
			mColor = GetColor(0, 0, 255);
			break;
		case ENEMY_TYPE_B_DRAGON: //�h���S��
			mPos.y = mPos.y - 32;
			mColor = GetColor(0, 255, 0);
			break;
		case ENEMY_TYPE_BOSS:     //�{�X
			mPos.y = mPos.y - 64;
			mColor = GetColor(200, 200, 200);
			break;
		default:
			break;
		}
		if (mEnemyLife != 0)
		{
			mType = ENEMY_TYPE_MAX;
			mColor = GetColor(0, 0, 0);
		}
	}
	mFont = GetDrawFormatStringWidth("%d", mPoint[mType]);
	mFont = mFont / 2;
}

void Score::Draw(Vector2 pos)//�`�揈��
{
	mOffset = pos;
	if (mLife > 0)
	{
		DrawCircle(mPos.x - mOffset.x, mPos.y - mOffset.y + 7, 10, GetColor(255, 255, 255), 1);
		DrawFormatString(mPos.x - mOffset.x - mFont, mPos.y - mOffset.y, mColor, "%d", mPoint[mType]);
		mLife--;
	}
	if (mLife > 15)
	{
		mPos.y -= 3;
	}
}

bool Score::Release(void)//�J������
{
	return true;
}

int Score::AddScore(int enemyType, Vector2 targetPos, int enemyLife)//�X�R�A�̉��Z
{
	mLife = 30;
	mType = enemyType;
	mPos = targetPos;
	mEnemyLife = enemyLife;
	if (enemyLife > 0)
	{
		return mPoint[ENEMY_TYPE_MAX];
	}
	return mPoint[enemyType];
}

bool Score::IsAlive(void) //�X�R�A�̕\������Ă��邩
{
	if (mLife > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
