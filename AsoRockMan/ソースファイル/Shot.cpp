#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "Shot.h"
#include "GameScene.h"

#define SHOT_IMAGE_SIZE_X 16
#define SHOT_IMAGE_SIZE_Y 16

bool Shot::Init(void)//�C���X�^���X�̏�����
{
	mPos = Vector2(100, 100);
	mMoveSpeed = 0;
	mLife = 0;
	return true;
}

Vector2 Shot::UpDate(void)//�C���X�^���X�̍X�V
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
			//�ǂ̒��ɖ��܂��Ēe����������
			mLife = 0;
			break;
		default:
			mPos = copyPos;
			break;
		}
	}
	return mPos;
}

void Shot::Draw(void)//�C���X�^���X�̕`��
{
	if (mLife > 0)
	{
		DrawGraph(mPos.x - SHOT_IMAGE_SIZE_X / 2, mPos.y - SHOT_IMAGE_SIZE_Y / 2, mImage, true);
	}
}

bool Shot::Release(void)//�C���X�^���X�̊J��
{
	DeleteGraph(mImage);
	return true;
}

void Shot::CreateShot(Vector2 targetPos, DIR targetDir)//�e�̔���
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

bool Shot::IsAlive(void)//�e���\������Ă��邩
{
	if (mLife > 0)
	{
		return true;
	}
	return false;
}

void Shot::Destroy(void)//�摜������
{
	mLife = 0;
}

Shot::Shot(GameScene* parent)//�R���X�g���X�^
{
	//�e�̃|�C���^�ϐ��i�[
	mParent = parent;
	//�摜�̃��[�h
	mImage = LoadGraph("Image/Player/P1/Shot.png");
}

Shot::~Shot(void) //�f�X�g���X�^
{

}