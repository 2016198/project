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
	//タンク
	mTank = new Tank(mSceneManager);
	mTank->Init();

	// スカイドーム
	mSkyDome = new SkyDome(mSceneManager, nullptr);
	mSkyDome->Init();

	mStage = new Stage(mSceneManager, mTank);
	mStage->Init();

	// ステージの設定
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

	// デバッグ表示
	DrawDebug();

}

void TankScene::DrawDebug(void)
{
	// ヘルプ
	DrawFormatString(840, 20, 0x000000, "前方移動　　：Wキー");
	DrawFormatString(840, 40, 0x000000, "後方移動　　：Sキー");
	DrawFormatString(840, 60, 0x000000, "左右回転　　：←→キー");
	DrawFormatString(840, 80, 0x000000, "上下回転　  ：↑↓キー");
	DrawFormatString(840, 100, 0x000000, "発射！      ：Nキー");
	DrawFormatString(840, 120, 0x000000, "タイトルへ  ：スペース");
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
