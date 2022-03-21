#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Common/KeyCheck.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/GravityManager.h"
#include "../Object/Common/Capsule.h"
#include "../Object/Common/Collider.h"
#include "../Object/SkyDome.h"
#include "../Object/Stage.h"
#include "../Object/Tank.h"
#include "../Object/Planet.h"
#include "TankScene.h"

TankScene::TankScene(SceneManager* manager) : SceneBase(manager)
{
	mSkyDome = nullptr;
	mStage = nullptr;
	mTank = nullptr;
}

void TankScene::Init(void)
{
	//�^���N
	mTank = new Tank(mSceneManager);
	mTank->Init();

	// �X�J�C�h�[��
	mSkyDome = new SkyDome(mSceneManager, nullptr);
	mSkyDome->Init();

	mStage = new Stage(mSceneManager, mTank);
	mStage->Init();

	// �X�e�[�W�̐ݒ�
	mStage->ChangeStage(Stage::NAME::MAIN_PLANET);

	//mSceneManager->GetCamera()->SetTransform(mPlayer->GetTransform());
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

}

void TankScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

	mSkyDome->Update();

	mStage->Update();

	mTank->Update();
}

void TankScene::Draw(void)
{
	mSkyDome->Draw();

	mStage->Draw();

	mTank->Draw();

	// �f�o�b�O�\��
	DrawDebug();

}

void TankScene::DrawDebug(void)
{
	// �w���v
	DrawFormatString(840, 20, 0x000000, "�O���ړ��@�@�FW�L�[");
	DrawFormatString(840, 40, 0x000000, "����ړ��@�@�FS�L�[");
	DrawFormatString(840, 60, 0x000000, "���E��]�@�@�F�����L�[");
	DrawFormatString(840, 80, 0x000000, "�㉺��]�@  �F�����L�[");
	DrawFormatString(840, 100, 0x000000, "���ˁI      �FN�L�[");
	DrawFormatString(840, 120, 0x000000, "�^�C�g����  �F�X�y�[�X");
}

void TankScene::Release(void)
{
	mSkyDome->Release();
	delete mSkyDome;
	mSkyDome = nullptr;

	mStage->Release();
	delete mStage;
	mStage = nullptr;

	mTank->Release();
	delete mTank;
	mTank = nullptr;
}
