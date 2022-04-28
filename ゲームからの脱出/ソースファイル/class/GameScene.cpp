#include <DxLib.h>			
#include "KeyCheck.h"
#include "GameScene.h"

bool GameScene::Init(void)
{
	KeyInit();	//�L�[���Ǘ��֐��̏�����

	//�e�V�[���̏�����
	if (!mStage.Init())
	{
		return false;
	}
	if (!mPlayer.Init(this))
	{
		return false;
	}
	if (!mSlide.Init())
	{
		return false;
	}
	if (!mLight.Init())
	{
		return false;
	}
	if (!mBucket.Init())
	{
		return false;
	}
	if (!mSafe.Init())
	{
		return false;
	}
	if (!mTips.Init())
	{
		return false;
	}

	//�t���O�̏�����
	escapeFlag = false;

	mSflag.slide = false;
	mSflag.light = false;
	mSflag.bucket = false;
	mSflag.safe = false;

	flag.slide = false;
	flag.light = false;
	flag.bucket = false;
	flag.safe = false;

	count = 0;

	safeCheck = false;

	return true;

}
bool GameScene::Update(void)
{
	CheckKeyList();
	mStage.Update();
	mPlayer.Update();

	//�X���C�h�p�Y��
	if (mSflag.slide)
	{
		mSlide.Update();
	}

	//���C�g�u���b�N
	if (mSflag.light)
	{
		mLight.Update();
	}

	//�o�P�c�Q�[��
	if (mSflag.bucket)
	{
		mBucket.Update();
	}

	//����
	if (mSflag.safe)
	{
		mSafe.Update();
	}

	//���ɂ��J�����߂̃q���g
	mTips.Update();

	//�N���A��������������N���A
	if (mPlayer.ClearFlag() == true && escapeFlag == true)
	{
		return false;
	}

	return true;
}
void GameScene::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);					//�`�悷���ʂ𗠂̉�ʂɐݒ�
	ClearDrawScreen();								//�`�悷���ʂ̓��e������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	//�`�悷���ʂ̃u�����h���[�h�̐ݒ�

	mStage.PassDraw();

	if (!mPlayer.back)
	{
		mPlayer.Draw();
	}

	mStage.NotPassDraw();

	if (!mSlide.ReturnFlag())
	{
		mStage.EventDraw({ 32 * 3,32 * 2 });
	}

	if (!mLight.ReturnFlag())
	{
		mStage.EventDraw({ 32*13,32*9 });
	}

	if (!mBucket.ReturnFlag())
	{
		mStage.EventDraw({ 32*16,32*2 });
	}

	if (!mSafe.ReturnFlag() && mTips.MatchFlag())
	{
		mStage.EventDraw({ 32*14,32 });
	}

	if (!mPlayer.back)
	{
		mPlayer.Draw();
	}

	if (mSafe.ReturnFlag())
	{
		escapeFlag = true;
		mStage.EscapeDraw({ 32 * 8 + 16,32 * 5 - 8 });
	}

	//�X���C�h�p�Y��
	if (mSflag.slide)
	{
		if (!mSlide.Back())
		{
			mSlide.Draw();
		}
		else
		{
			mSflag.slide = false;
		}
	}

	//���C�g�u���b�N
	if (mSflag.light)
	{
		if (!mLight.Back())
		{
			mLight.Draw();
		}
		else
		{
			mSflag.light = false;
		}
	}
	
	//�o�P�c�Q�[��
	if (mSflag.bucket)
	{
		if (!mBucket.Back())
		{
			mBucket.Draw();
		}
		else
		{
			mSflag.bucket = false;
		}

	}

	//����
	if (mSflag.safe)
	{
		DrawBox(0, 0, 640, 480, 0x000000, true);//��ʂ̓_�Ŗh�~

		if (!mSafe.Back())
		{
			mSafe.Draw();
		}
		else 
		{
			if (mTips.ReturnFlag())
			{
				mSflag.safe = false;
			}
		}
	}

	//�p�X���[�h�̃q���g�`��
	if (mSlide.ReturnFlag() && mSflag.slide == false)
	{
		mTips.SlideDraw();
	}

	if (mLight.ReturnFlag() && mSflag.light == false)
	{
		mTips.LightDraw();
	}

	if (mTips.MatchFlag()&&!mSflag.bucket)
	{
		mTips.MatchDraw();
	}

	//�o�P�c�Q�[���ŕ\�������Ȃ�
	if (!mSflag.bucket)	
	{
		//�p�X���[�h�����ɕ\��
		mTips.InventoryDraw();	
	}

	//��������ĂȂ��ƊJ�����Ȃ�����ׂ̏���
	if (!mBucket.ReturnFlag() && mPlayer.CheckSafe())
	{
		safeCheck = true;
		DrawString(0, 0, "�����Ȃ�", 0xffffff);
	}

	//�X�e�[�W�f�o�b�O�p�̃O���b�h�\��
	//for (int y = 0; y < 14; y++)
	//{
	//	for (int x = 0; x < 19; x++)
	//	{
	//		DrawLine(32+x * 32, 0, 32+x * 32, 480, 0x00ff00);
	//		DrawLine(0, 32+y*32, 640, 32+y*32, 0x00ff00);
	//	}
	//}
}
bool GameScene::Release(void)
{
	mStage.Release();
	mPlayer.Release();
	return true;

}

int GameScene::GetEvent(Vector2 pos)
{
	int mapChipID;	//�}�b�v�`�b�vID���i�[����ϐ�
	mapChipID = mStage.GetEventChip(pos);	//�C�x���g�𔭐�������}�b�v�`�b�v���i�[����

	//�v���C���[���Œ��ׂāA�����̃p�Y�����N���A���Ă��Ȃ�������J�n����
	if (mPlayer.CheckSlide() && !mSlide.ReturnFlag())
	{
		mSflag.slide = true;//�X���C�h�p�Y��
	}

	if (mPlayer.CheckLight() && !mLight.ReturnFlag())
	{
		mSflag.light = true;//���C�g�u���b�N
	}

	if (mPlayer.CheckBucket() && !mBucket.ReturnFlag())
	{
		mSflag.bucket = true;//�o�P�c�Q�[��
	}

	if (mPlayer.CheckSafe() && !mSafe.ReturnFlag())
	{
		//�o�P�c�Q�[���N���A�ς݊��A�S�q���g���W�ς݂ŊJ�n�ł���
		if (mBucket.ReturnFlag() && mTips.MatchFlag())
		{
			mSflag.safe = true;//����
		}
	}

	//�e�p�Y���N���A��̏���
	if (CheckHitKey(KEY_INPUT_SPACE) && mSlide.ReturnFlag())
	{
		mSflag.slide = false;
		flag.light = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && mLight.ReturnFlag())
	{
		mSflag.light = false;
		flag.light = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && mBucket.ReturnFlag())
	{
		mSflag.bucket = false;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && mSafe.ReturnFlag())
	{
		mSflag.safe = false;
		escapeFlag = true;
	}
	return 	mapChipID;
}

int GameScene::GetCol(Vector2 pos)
{
	int mapChipID;	//�}�b�v�`�b�vID���i�[����ϐ�
	mapChipID = mStage.GetMapChip(pos);

	return mapChipID;
}

bool GameScene::SafeCheck(void)
{
	if (safeCheck)
	{
		safeCheck = false;
		return true;
	}
	return false;
}

bool GameScene::ClearCheck(void)
{
	if (flag.slide)
	{
		flag.slide = false;
		return true;
	}
	if (flag.light)
	{
		flag.light = false;
		return true;
	}
	if (flag.bucket)
	{
		flag.bucket = false;
		return true;
	}
	if (flag.safe)
	{
		flag.safe = false;
		return true;
	}
	return false;
}
