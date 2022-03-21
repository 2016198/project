#include "SceneManager.h"
#include "Camera.h"
#include "KeyCheck.h"
#include "GameCommon.h"
#include "PlayerShip.h"
#include "BossShip.h"
#include "RockManager.h"
#include "SpaceDome.h"
#include "PlayerShot.h"
#include "Turret.h"
#include "TurretShot.h"
#include "AsoUtility.h"
#include "BattleScene.h"

BattleScene::BattleScene(SceneManager* manager) : SceneBase(manager)
{
}

void BattleScene::Init(void)
{
	mEndImg = LoadGraph("Image/EndLogo.png");

	mPlayerShip = new PlayerShip(mSceneManager);
	mPlayerShip->Init();

	mSpaceDome = new SpaceDome(
		mSceneManager, mPlayerShip->GetTranceform());
	mSpaceDome->Init();
	
	mRockManager = new RockManager(
		mSceneManager, mPlayerShip->GetTranceform());
	mRockManager->Init();

	mBossShip = new BossShip(mSceneManager, mPlayerShip);
	mBossShip->Init();

	//�J�������[�h�̐ݒ�
	auto camera = mSceneManager->GetCamera();
	camera->SetShip(mPlayerShip->GetTranceform());
	camera->ChangeMode(Camera::MODE::FOLLOW_SPRING);

	mStepShipDestroy = 0.0f;
}

void BattleScene::Update(void)
{
	//�V�[���J��
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	//���@�ƃX�e�[�W�Ƃ̏Փ˔���
	if (mPlayerShip->IsDestroy())
	{
		mStepShipDestroy += mSceneManager->GetDeltaTime();
		if (mStepShipDestroy > TIME_RESTART)
		{
			mSceneManager->ChangeScene(
				SceneManager::SCENE_ID::BATTLE, true);
		}
	}
	else
	{
		//�{�X
		if (mBossShip->IsAlive())
		{
			auto info = MV1CollCheck_Sphere(
				mBossShip->GetTranceform()->modelId, -1,
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
	}

	mPlayerShip->Update();
	mBossShip->Update();

	mRockManager->Update();
	mSpaceDome->Update();

	//�C��̒e�̍X�V����
	auto turrets = mBossShip->GetTurrets();
	for (const auto turret : turrets)
	{
		auto tShots = turret->GetShots();
		for (const auto shot : tShots)
		{
			if (!shot->IsAlive())
			{
				continue;
				//���[�v�𔲂����ɂ���ȉ��̏����͎��s���Ȃ�
			}

			//�v���C���[�ƒe�̓����蔻��
			if (mBossShip->IsAlive())
			{

				if (AsoUtility::IsHitSpheres(
					mPlayerShip->GetTranceform()->pos,
					mPlayerShip->COLLISION_RADIUS,
					shot->GetPos(),
					shot->GetCollisionRadius()))
				{
					//�Փ˂��Ă���̂Œe�ƃv���C���[��j��
					shot->CreateExplosion();
					mPlayerShip->Destroy();
				}
			}
		}
	}


	//���@�̒e�̍X�V����
	auto pShots = mPlayerShip->GetShots();
	for (const auto shot : pShots)
	{
		shot->Update();

		if (!shot->IsAlive())
		{
			continue;
			//���[�v�𔲂����ɂ���ȉ��̏����͎��s���Ȃ�
		}

		//�{�X�ƒe�̓����蔻��
		auto info = MV1CollCheck_Sphere(
			mBossShip->GetTranceform()->modelId, -1,
			shot->GetPos(), shot->GetCollisionRadius());

		if (info.HitNum > 0)
		{
			//�Փ˂��Ă���̂Œe��j��
			shot->CreateExplosion();
		}

		//�������蔻�茋�ʂ̃|���S���z��̌�n��������
		MV1CollResultPolyDimTerminate(info);

		//�^���b�g�ƒe�̓����蔻��(���� �� ����)
		auto turrets = mBossShip->GetTurrets();
		for (auto turret : turrets)
		{
			if (!turret->IsAlive())
			{
				continue;
				//���[�v�𔲂����ɂ���ȉ��̏����͎��s���Ȃ�
			}

			if (AsoUtility::IsHitSpheres(
				turret->GetPos(),
				Turret::COLLISION_RADIUS,
				shot->GetPos(),
				shot->GetCollisionRadius()))
			{
				//�^���b�g�Ƀ_���[�W
				turret->Damage();
				//���@�̒e��j��
				shot->CreateExplosion();
				break;
			}
		}
	}

}

void BattleScene::Draw(void)
{
	//�s�����Ȕw�i����`��
	mSpaceDome->Draw();

	//�w�i
	mRockManager->Draw();

	//�L�����N�^�[
	mBossShip->Draw();
	mPlayerShip->Draw();

	//���@�̒e��`��
	auto pShots = mPlayerShip->GetShots();
	for (const auto shot : pShots)
	{
		shot->Draw();
	}

	if (!mBossShip->IsAlive())
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2,
			1.0, 0.0, mEndImg, true);
	}

}

void BattleScene::Release(void)
{
	mBossShip->Release();
	delete mBossShip;
	mBossShip = nullptr;

	mRockManager->Release();
	delete mRockManager;
	mRockManager = nullptr;

	mSpaceDome->Release();
	delete mSpaceDome;
	mSpaceDome = nullptr;

	mPlayerShip->Release();
	delete mPlayerShip;
	mPlayerShip = nullptr;

	DeleteGraph(mEndImg);
}
