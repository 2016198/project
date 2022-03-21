#include "GameScene.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Player.h"
#include "Stage.h"
#include "Shot.h"
#include "Lift.h"
#include "KeyCheck.h"

bool GameScene::Init(void)  //�C���X�^���X�̐�������
{
	mCounter = 0;

	mLift = new Lift();
	mShot = new Shot(this);
	mStage = new Stage();
	mPlayer[static_cast<int>(PLAYER_TYPE::PLAYER1)] = new Player(this, PLAYER_TYPE::PLAYER1);
	mPlayer[static_cast<int>(PLAYER_TYPE::PLAYER2)] = new Player(this, PLAYER_TYPE::PLAYER2);
	if (!mLift->Init()) return false;
	if (!mStage->Init()) return false;
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		if (!mPlayer[p]->Init()) return false;
	}
	if (!mShot->Init()) return false;
	return true;
}

bool GameScene::UpDate(void)  //�C���X�^���X�̍X�V����
{
	Vector2 playerPos;
	mStage->UpDate();
	mLift->UpDate();
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		playerPos = mPlayer[p]->UpDate();
	}
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		if (mPlayer[p]->IsShot())
		{
			if (!mShot->IsAlive())
			{
				mShot->CreateShot(mPlayer[static_cast<int>(PLAYER_TYPE::PLAYER1)]->GetShotPos(), mPlayer[static_cast<int>(PLAYER_TYPE::PLAYER1)]->GetDir());
			}
		}
	}
	mShot->UpDate();
	mCounter++;
	return false;
}

void GameScene::Draw(void)  //�C���X�^���X�̕`�揈��
{
	SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
	ClsDrawScreen();                                //��ʏ���
	DrawBox(50, 50, 600, 440, GetColor(0, 255, 0), 1);	
	DrawFormatString(50, 50, GetColor(0, 0, 255), "%d", mCounter);
	mStage->Draw();
	mLift->Draw();
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		mPlayer[p]->Draw();
	}
	mShot->Draw();
}

bool GameScene::Release(void) //�C���X�^���X�̊J������
{
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		if (!mPlayer[p]->Release()) return false;
	}
	if (!mStage->Release()) return false;
	if (!mShot->Release()) return false;
	if (!mLift->Release()) return false;
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		delete mPlayer[p];
	}
	delete mStage;
	delete mShot;
	delete mLift;
	for (int p = 0; p < static_cast<int>(PLAYER_TYPE::MAX); p++)
	{
		mPlayer[p] = nullptr;
	}
	mStage = nullptr;
	mShot = nullptr;
	mLift = nullptr;
	return true;
}

bool GameScene::GetLiftAlive(void)//���t�g�̏���Ԃ��B
{
	return mLift->IsAlive();
}

Vector2 GameScene::GetLiftPos(void)//���t�g�̏���Ԃ��B
{
	return mLift->GetPos();
}

bool GameScene::GameInit(void)   //�C���X�^���X�̏���������
{
	mCounter = 0;
	return true;
}

int GameScene::GetEvent(Vector2 pos)//�}�b�v�̏���Ԃ�
{
	int mMapChipID;
	mMapChipID = mStage->GetMapChip(pos);
	return mMapChipID;
}