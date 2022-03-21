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

	//�J�������[�h�ύX
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	//�{�X
	mBossShip = new BossShip(mSceneManager, nullptr);
	mBossShip->Init();

	//�w�i
	mSpaceDome = new SpaceDome(mSceneManager, nullptr);
	mSpaceDome->Init();
}

void EventScene::Update(void)
{

	//�V�[���J��
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	mBossShip->Update();
	mSpaceDome->Update();
}

void EventScene::Draw(void)
{
	//�s�����Ȕw�i����`�悷��
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
