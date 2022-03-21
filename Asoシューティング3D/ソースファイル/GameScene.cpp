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

	//カメラモードの設定
	auto camera = mSceneManager->GetCamera();
	camera->SetShip(mPlayerShip->GetTranceform());
	camera->ChangeMode(Camera::MODE::FOLLOW_SPRING);

	mStepShipDestroy = 0.0f;
}

void GameScene::Update(void)
{
	// シーン遷移
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}
	//プレイヤーの更新を先にする
	//プレイヤー機の移動に合わせて処理するため
	mPlayerShip->Update();

	//自機とステージとの衝突判定
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
			//衝突している
			mPlayerShip->Destroy();
		}

		//★当たり判定結果のポリゴン配列の後始末をする
		MV1CollResultPolyDimTerminate(info);
	}

	mSpaceDome->Update();
	mStage->Update();

	mRockManager->Update();
}

void GameScene::Draw(void)
{
	//背景の描画
	mSpaceDome->Draw();

	//ステージの描画
	mStage->Draw();

	//プレイヤーシップの描画
	mPlayerShip->Draw();

	//岩の描画
	mRockManager->Draw();

	//2D系、UI系
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
