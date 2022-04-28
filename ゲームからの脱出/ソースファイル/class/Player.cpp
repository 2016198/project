#include <DxLib.h>
#include "Player.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Player:: Init(GameScene* parent)
{

	//�v���C���[�摜�̓ǂݍ���
	if (LoadDivGraph("image/chara/pipo-charachip001.png", 12, 3, 4, 32, 32,
		&mImage[0][0]) == -1)
	{
		return false;
	}

	//�e�C���X�^���X�̊i�[
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

	//�p�Y���̊Ǘ��t���O
	mFlag.DrawFlag = false;
	mFlag.start = false;
	mFlag.slide = false;
	mFlag.light = false;
	mFlag.bucket = false;
	mFlag.safe = false;
	mFlag.escape = false;

	//�p�Y���J�n�t���O
	mSFlag.slide = false;
	mSFlag.light = false;
	mSFlag.bucket = false;
	mSFlag.safe = false;

	Vector2 copyPos;
	copyPos = mPos;
	mRayPos = mPos;

	DIR keyDir = DIR::MAX;
	mAnimCnt++;

	//�A�j���[�V����
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

	//R_SHIFT�L�[�Ń_�b�V��
	if (CheckHitKey(KEY_INPUT_RSHIFT) == 1)
	{
		mSpeed = 6;
	}
	else
	{
		mSpeed = 3;
	}

	//WASD�ňړ�
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


	//�I�u�W�F�N�g�̎�ޕʂ̏���
	switch (mParent->GetCol(mPos))
	{
	case 228://���@�w
	{
		mFlag.escape = true;
		if (CheckHitKey(KEY_INPUT_Z))//�N���A�J��
		{
			flag_ = true;
		}
	}
	break;

	//�ʂ�Ȃ��I�u�W�F�N�g
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

	//�ꕔ�I�u�W�F�N�g�̌���ʉ߂�����v���C���[�������鏈��
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

	//�ꕔ�I�u�W�F�N�g�̌���ʉ߂�����v���C���[�������鏈��
	//�v���C���[���I�u�W�F�N�g���ђʂ���̂ł�����񏈗�����
	switch (mParent->GetCol(mPos))
	{
	case 303:
	case 302:
	case 183:
		back = true;
	}

	//�������ʂɑJ�ڂ��邽�߂̃t���O�Ǘ�
	switch (mParent->GetEvent(mRayPos))
	{
		//�o�P�c�Q�[��
	case 297:
		mFlag.DrawFlag = true;
		mFlag.bucket = true;
		break;

		//���C�g�u���b�N
	case 326:
		mFlag.DrawFlag = true;
		mFlag.light = true;
		break;

		//�X���C�h�p�Y��
	case 203:
		mFlag.DrawFlag = true;
		mFlag.slide = true;
		break;

		//����
	case 134:
		mFlag.DrawFlag = true;
		mFlag.safe = true;
		break;
	}

	//�������ʂɑJ��
	if (mFlag.slide == true && CheckHitKey(KEY_INPUT_Z))
	{
		//�X���C�h�p�Y��
		mSFlag.slide = true;
	}
	if (mFlag.light == true && CheckHitKey(KEY_INPUT_Z))
	{
		//���C�g�u���b�N
		mSFlag.light = true;
	}
	if (mFlag.bucket == true && CheckHitKey(KEY_INPUT_Z))
	{
		//�o�P�c�Q�[��
		mSFlag.bucket = true;
	}
	if (mFlag.safe == true && CheckHitKey(KEY_INPUT_Z))
	{
		//����
		mSFlag.safe = true;
	}

	return mPos;

}
void Player::Draw(void)
{
	DrawGraph(mPos.x + mOffset.x, mPos.y + mOffset.y, mImage[static_cast<int>(mMoveDir)][mANIM], true);

	//�C�x���g�̌Ăяo���Ɗm�F
	DrawFormatString(0, 0, 0xffffff, "%d", mParent->GetEvent(mPos));
	DrawFormatString(30, 0, 0xffffff, "%d", mParent->GetEvent(mRayPos));
	DrawBox(0, 0, 100, 16, 0x000000, true);	//�����v���C�̎ז��ɂȂ�Ȃ��悤�B��

	if (mFlag.DrawFlag == true)
	{
		DrawString(0, 480-16, "Z�L�[�Œ��ׂ�", 0xffffff, true);
	}

	if (mParent->escapeFlag == true && mFlag.escape == true)
	{
		DrawString(0, 480 - 16, "Z�L�[�ŋA��", 0xffffff, true);

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
