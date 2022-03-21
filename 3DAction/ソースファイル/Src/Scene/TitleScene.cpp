#include <string>
#include <DxLib.h>
#include "../Common/KeyCheck.h"
#include "../Common/GameCommon.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/Camera.h"
#include "../Object/Common/AnimationController.h"
#include "../Object/SkyDome.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
	mImgPush = -1;
	mImgTitle = -1;
	mSkyDome = nullptr;
	mAnimationController = nullptr;
}

void TitleScene::Init(void)
{

	ResourceManager* rm = mSceneManager->GetResourceManager();

	// 画像読み込み
	mImgTitle = rm->Load(ResourceManager::SRC::TITLE).mHandleId;
	mImgPush = rm->Load(ResourceManager::SRC::PUSH_SPACE).mHandleId;

	// 背景
	mSkyDome = new SkyDome(mSceneManager, nullptr);
	mSkyDome->Init();

	float size;

	// メイン惑星
	mPlanet.SetModel(rm->LoadModelDuplicate(ResourceManager::SRC::FALL_PLANET));
	mPlanet.pos = AsoUtility::VECTOR_ZERO;
	mPlanet.scl = AsoUtility::VECTOR_ONE;
	mPlanet.Update();

	// 回転する惑星
	mMovePlanet.SetModel(rm->LoadModelDuplicate(ResourceManager::SRC::LAST_PLANET));
	mMovePlanet.pos = { -250.0f, -100.0f, -100.0f };
	size = 0.7f;
	mMovePlanet.scl = { size, size, size };
	mMovePlanet.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(90.0f), 0.0f, 0.0f);
	mMovePlanet.Update();

	// キャラ
	mChara.SetModel(rm->LoadModelDuplicate(ResourceManager::SRC::PLAYER));
	mChara.pos = { -250.0f, -32.0f, -105.0f };
	size = 0.4f;
	mChara.scl = { size, size, size };
	mChara.quaRot = Quaternion::Euler(
		0.0f, AsoUtility::Deg2RadF(90.0f), 0.0f);
	mChara.Update();

	// アニメーションの設定
	std::string path = "Data/Model/Player/";
	mAnimationController = new AnimationController(mSceneManager, mChara.modelId);
	mAnimationController->Add(0, path + "Run.mv1", 20.0f);
	mAnimationController->Play(0);

	// 定点カメラ
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::GAME, true);
	}

	if (keyTrgDown[KEY_P1_A])
	{
		mSceneManager->ChangeScene(SCENE_ID::TANK, true);
	}

	// 惑星の回転
	mMovePlanet.quaRot = mMovePlanet.quaRot.Mult(
		Quaternion::Euler(0.0f, 0.0f, AsoUtility::Deg2RadF(1.0f)));
	mMovePlanet.Update();

	// キャラアニメーション
	mAnimationController->Update();

	mSkyDome->Update();

}

void TitleScene::Draw(void)
{

	mSkyDome->Draw();

	MV1DrawModel(mPlanet.modelId);
	MV1DrawModel(mMovePlanet.modelId);
	MV1DrawModel(mChara.modelId);

	DrawRotaGraph(SCREEN_SIZE_X / 2, 250, 1.0, 0.0, mImgTitle, true);
	DrawRotaGraph(SCREEN_SIZE_X / 2, 500, 1.0, 0.0, mImgPush, true);

	DrawString(700, 500, "Nキーでタンクモード", 0xff00ff);

}

void TitleScene::Release(void)
{

	mSkyDome->Release();
	delete mSkyDome;

	mAnimationController->Release();
	delete mAnimationController;

}
