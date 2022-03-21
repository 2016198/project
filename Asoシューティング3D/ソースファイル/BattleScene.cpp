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

	//カメラモードの設定
	auto camera = mSceneManager->GetCamera();
	camera->SetShip(mPlayerShip->GetTranceform());
	camera->ChangeMode(Camera::MODE::FOLLOW_SPRING);

	mStepShipDestroy = 0.0f;
}

void BattleScene::Update(void)
{
	//シーン遷移
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	//自機とステージとの衝突判定
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
		//ボス
		if (mBossShip->IsAlive())
		{
			auto info = MV1CollCheck_Sphere(
				mBossShip->GetTranceform()->modelId, -1,
				mPlayerShip->GetTranceform()->pos,
				PlayerShip::COLLISION_RADIUS);

			if (info.HitNum > 0)
			{
				//衝突している
				mPlayerShip->Destroy();
			}

			//★当たり判定結果のポリゴン配列の後始末をする
			MV1CollResultPolyDimTerminate(info);
		}
	}

	mPlayerShip->Update();
	mBossShip->Update();

	mRockManager->Update();
	mSpaceDome->Update();

	//砲台の弾の更新処理
	auto turrets = mBossShip->GetTurrets();
	for (const auto turret : turrets)
	{
		auto tShots = turret->GetShots();
		for (const auto shot : tShots)
		{
			if (!shot->IsAlive())
			{
				continue;
				//ループを抜けずにこれ以下の処理は実行しない
			}

			//プレイヤーと弾の当たり判定
			if (mBossShip->IsAlive())
			{

				if (AsoUtility::IsHitSpheres(
					mPlayerShip->GetTranceform()->pos,
					mPlayerShip->COLLISION_RADIUS,
					shot->GetPos(),
					shot->GetCollisionRadius()))
				{
					//衝突しているので弾とプレイヤーを破棄
					shot->CreateExplosion();
					mPlayerShip->Destroy();
				}
			}
		}
	}


	//自機の弾の更新処理
	auto pShots = mPlayerShip->GetShots();
	for (const auto shot : pShots)
	{
		shot->Update();

		if (!shot->IsAlive())
		{
			continue;
			//ループを抜けずにこれ以下の処理は実行しない
		}

		//ボスと弾の当たり判定
		auto info = MV1CollCheck_Sphere(
			mBossShip->GetTranceform()->modelId, -1,
			shot->GetPos(), shot->GetCollisionRadius());

		if (info.HitNum > 0)
		{
			//衝突しているので弾を破棄
			shot->CreateExplosion();
		}

		//★当たり判定結果のポリゴン配列の後始末をする
		MV1CollResultPolyDimTerminate(info);

		//タレットと弾の当たり判定(球体 体 球体)
		auto turrets = mBossShip->GetTurrets();
		for (auto turret : turrets)
		{
			if (!turret->IsAlive())
			{
				continue;
				//ループを抜けずにこれ以下の処理は実行しない
			}

			if (AsoUtility::IsHitSpheres(
				turret->GetPos(),
				Turret::COLLISION_RADIUS,
				shot->GetPos(),
				shot->GetCollisionRadius()))
			{
				//タレットにダメージ
				turret->Damage();
				//自機の弾を破壊
				shot->CreateExplosion();
				break;
			}
		}
	}

}

void BattleScene::Draw(void)
{
	//不透明な背景から描画
	mSpaceDome->Draw();

	//背景
	mRockManager->Draw();

	//キャラクター
	mBossShip->Draw();
	mPlayerShip->Draw();

	//自機の弾を描画
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
