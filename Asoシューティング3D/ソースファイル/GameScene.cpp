#include <cmath>
#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "SpaceDome.h"
#include "Stage.h"
#include "PlayerShip.h"
#include "SpeechBalloon.h"
#include "RockManager.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager)
{
}

void GameScene::Init(void)
{
	mPlayerShip = new PlayerShip(mSceneManager);
	mPlayerShip->Init();

	mSpaceDome = new SpaceDome(mSceneManager, mPlayerShip->GetTranceform());
	mSpaceDome->Init();

	mStage = new Stage(mSceneManager, mPlayerShip->GetTranceform());
	mStage->Init();

	mRockManager = new RockManager(mSceneManager, mPlayerShip->GetTranceform());
	mRockManager->Init();

	//�J�������[�h�̐ݒ�
	auto camera = mSceneManager->GetCamera();
	camera->SetShip(mPlayerShip->GetTranceform());
	camera->ChangeMode(Camera::MODE::FOLLOW_SPRING);

	mStepShipDestroy = 0.0f;
}

void GameScene::Update(void)
{
	// �V�[���J��
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}
	//�v���C���[�̍X�V���ɂ���
	//�v���C���[�@�̈ړ��ɍ��킹�ď������邽��
	mPlayerShip->Update();

	//���@�ƃX�e�[�W�Ƃ̏Փ˔���
	if (mPlayerShip->IsDestroy())
	{
		mStepShipDestroy += mSceneManager->GetDeltaTime();
		if (mStepShipDestroy > TIME_RESTART)
		{
			mSceneManager->ChangeScene(
				SceneManager::SCENE_ID::GAME, true);
		}
	}
	else
	{
		auto info = MV1CollCheck_Sphere(
			mStage->GetModelDungeon(), -1,
			mPlayerShip->GetTranceform()->pos,
			PlayerShip::COLLISION_RADIUS);

		if (info.HitNum > 0)
		{
			//�Փ˂��Ă���
			mPlayerShip->Destroy();
		}

		//�������蔻�茋�ʂ̃|���S���z��̌�n��������
		MV1CollResultPolyDimTerminate(info);
	}

	mSpaceDome->Update();
	mStage->Update();

	mRockManager->Update();
}

void GameScene::Draw(void)
{
	//�w�i�̕`��
	mSpaceDome->Draw();

	//�X�e�[�W�̕`��
	mStage->Draw();

	//�v���C���[�V�b�v�̕`��
	mPlayerShip->Draw();

	//��̕`��
	mRockManager->Draw();

	//2D�n�AUI�n
	mPlayerShip->GetSpeechBalloon()->Draw();
}

void GameScene::Release(void)
{
	mRockManager->Release();
	delete mRockManager;
	mRockManager = nullptr;

	mSpaceDome->Release();
	delete mSpaceDome;
	mSpaceDome = nullptr;

	mStage->Release();
	delete mStage;
	mStage = nullptr;

	mPlayerShip->Release();
	delete mPlayerShip;
	mPlayerShip = nullptr;
}
