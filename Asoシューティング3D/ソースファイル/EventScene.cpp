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

	//ƒJƒƒ‰ƒ‚[ƒh•ÏX
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	//ƒ{ƒX
	mBossShip = new BossShip(mSceneManager, nullptr);
	mBossShip->Init();

	//”wŒi
	mSpaceDome = new SpaceDome(mSceneManager, nullptr);
	mSpaceDome->Init();
}

void EventScene::Update(void)
{

	//ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	mBossShip->Update();
	mSpaceDome->Update();
}

void EventScene::Draw(void)
{
	//•s“§–¾‚È”wŒi‚©‚ç•`‰æ‚·‚é
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
