#include "SceneManager.h"
#include "Camera.h"
#include "KeyCheck.h"
#include "BossShip.h"
#include "SpaceDome.h"
#include "EventScene.h"

EventScene::EventScene(SceneManager* manager) : SceneBase(manager)
{
}

void EventScene::Init(void)
{

	//カメラモード変更
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	//ボス
	mBossShip = new BossShip(mSceneManager, nullptr);
	mBossShip->Init();

	//背景
	mSpaceDome = new SpaceDome(mSceneManager, nullptr);
	mSpaceDome->Init();
}

void EventScene::Update(void)
{

	//シーン遷移
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	mBossShip->Update();
	mSpaceDome->Update();
}

void EventScene::Draw(void)
{
	//不透明な背景から描画する
	mSpaceDome->Draw();

	mBossShip->Draw();
}

void EventScene::Release(void)
{
	mBossShip->Release();
	delete mBossShip;
	mBossShip = nullptr;

	mSpaceDome->Release();
	delete mSpaceDome;
	mSpaceDome = nullptr;
}
