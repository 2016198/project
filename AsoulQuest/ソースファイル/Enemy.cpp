#include "Enemy.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Enemy::Init(GameScene* parent, int enemyType, int ScreenSizeX, int ScreenSizeY, Vector2 pos)  //�C���X�^���X�̏���������
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
void Enemy::UpDate(Vector2 PlayerPos)//�C���X�^���X�̍X�V����
{
	mTargetPos = PlayerPos;
	if (mAnimCnt % 60 > 40)
	{
		switch (mCharType)
		{
		case ENEMY_TYPE_SLIME:		//�X���C��
		case ENEMY_TYPE_R_DRAGON:   //�ԃh���S��
			if (EnemyMoveX(&mPos.x, mMoveSpeed[mCharType], mTargetPos.x, &mMoveDir) == 0)
			{
				EnemyMoveY(&mPos.y, mMoveSpeed[mCharType], mTargetPos.y, &mMoveDir);
			}
			break;
		case ENEMY_TYPE_FLAME:		//��
		case ENEMY_TYPE_B_DRAGON:   //�h���S��
			if (EnemyMoveY(&mPos.y, mMoveSpeed[mCharType], mTargetPos.y, &mMoveDir) == 0)
			{
				EnemyMoveX(&mPos.x, mMoveSpeed[mCharType], mTargetPos.x, &mMoveDir);
			}
			break;
		case ENEMY_TYPE_BEE:		//�I
		case ENEMY_TYPE_BOSS:       //�{�X
			EnemyMoveXY(&mPos.x, &mPos.y, mTargetPos.x, mTargetPos.y, mMoveSpeed[mCharType]);
			break;
		default:
			break;
		}
	}
	mPosBottom = mPos.y + mSizeOffset.y;
	mAnimCnt++;
}
void Enemy::Draw(Vector2 pos)//�C���X�^���X�̕`�揈��
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
bool Enemy::Release(void)  //�C���X�^���X�̊J������
{
	return true;
}

Vector2 Enemy::GetPos(void) //���W��Ԃ�
{
	return mPos;
}

DIR Enemy::GetDir(void)//�L�����N�^�[�̌�����Ԃ�
{
	return mMoveDir;
}

int Enemy::EnemyMoveX(int* EnemyPosX, int enemySpeed, int targetPosX, DIR* move)
{
	int diff = targetPosX - *EnemyPosX; //�������Ƃ�

	//X���W�����킹��
	if (diff < 0) //�v���C���[�����ɂ���
	{
		if (-diff > enemySpeed)  //�v���C���[�ƓG�̋������G�̃X�s�[�h��菬�����Ȃ�����
		{
			*EnemyPosX -= enemySpeed;
		}
		else
		{
			*EnemyPosX += diff;
		}
		*move = DIR::DIR_LEFT;
	}
	else if (diff > 0) //�v���C���[���E�ɂ���
	{
		if (diff > enemySpeed)  //�v���C���[�ƓG�̋������G�̃X�s�[�h��菬�����Ȃ�����
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
	int diff = targetPosY - *EnemyPosY; //�������Ƃ�

	//Y���W�����킹��
	if (diff < 0) //�v���C���[�̂ق�����ɂ���
	{
		if (-diff > enemySpeed)  //�v���C���[�ƓG�̋������G�̃X�s�[�h��菬�����Ȃ�����
		{
			*EnemyPosY -= enemySpeed;
		}
		else
		{
			*EnemyPosY += diff;
		}
		*move = DIR::DIR_UP;
	}
	else if (diff > 0) //�v���C���[�̂ق������ɂ���
	{
		if (diff > enemySpeed)  //�v���C���[�ƓG�̋������G�̃X�s�[�h��菬�����Ȃ�����
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

//�߂�l�F�v���C���[�ƓG��X���W��Y���W�̍����̑傫���ق���Ԃ�
int Enemy::EnemyMoveXY(int* enemyPosX, int* enemyPosY, int targetPosX, int targetPosY, int enemySpeed)
{
	//�����̌v�Z����
	int diffX2 = (targetPosX - *enemyPosX) * (targetPosX - *enemyPosX);
	int diffY2 = (targetPosY - *enemyPosY) * (targetPosY - *enemyPosY);

	//�����ɍ��킹�Ĉړ�������
	if (diffX2 > diffY2)
	{
		//X�����Ɉړ�������
		return EnemyMoveX(enemyPosX, enemySpeed, targetPosX, &mMoveDir);
	}
	else
	{
		//Y�����Ɉړ�������
		return EnemyMoveY(enemyPosY, enemySpeed, targetPosY, &mMoveDir);
	}
}

Vector2 Enemy::GetSize(void)//�摜�̃T�C�Y��Ԃ�
{
	return mSizeOffset;
}

void Enemy::Destroy(void)//�G������
{
	mLife -= mLifeDec;
}

int Enemy::IsAlive(void) //�����Ă邩�ǂ���
{
	return mLife;
}

bool Enemy::Collsion(Vector2 targetPos, Vector2 targetSize)//�ՓˑΏۂƂ̍��W�Ɖ摜�T�C�Y
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

int Enemy::GetType(void) //�G�̎�ނ�Ԃ�
{
	return mCharType;
}