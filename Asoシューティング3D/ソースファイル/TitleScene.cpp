#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TitleScene.h"
#include "SpaceDome.h"
#include "ParticleGenerator.h"
#include "TextScroll.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{

	mImgStartLogo = LoadGraph("Image/StartLogo.png");
	mSpaceDome = new SpaceDome(mSceneManager, nullptr);

	mSpaceDome->Init();

	mParticleGenerator = new ParticleGenerator(
		mSceneManager, { 0.0f, 0.0f, 0.0f }, 20
	);

	mParticleGenerator->Init();

	mTextScroll = new TextScroll(mSceneManager);
	mTextScroll->Init();

	//カメラモードの設定
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FREE);
}

void TitleScene::Update(void)
{

	// シーン遷移
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}
	mSpaceDome->Update();

	mParticleGenerator->Update();

	mTextScroll->Update();
}

void TitleScene::Draw(void)
{
	mSpaceDome->Draw();
	
	mParticleGenerator->Draw();

	mTextScroll->Draw();
	// ロゴ描画
	DrawLogo();

}

void TitleScene::DrawLogo(void)
{

	int cx = SCREEN_SIZE_X / 2;
	int cy = SCREEN_SIZE_Y / 2;
	DrawRotaGraph(
		cx, cy - 200,
		1.0f, 0.0f, mImgStartLogo, true);

	char* msg = (char*)"Push Space";
	SetFontSize(28);
	int len = (int)strlen(msg);
	int width = GetDrawStringWidth(msg, len);
	DrawFormatString((SCREEN_SIZE_X / 2) - (width / 2), 200, 0x87cefa, msg);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetFontSize(16);
	
}

void TitleScene::Release(void)
{

	DeleteGraph(mImgStartLogo);

	mSpaceDome->Release();
	delete mSpaceDome;
	mSpaceDome = nullptr;

	mParticleGenerator->Release();
	delete mParticleGenerator;
	mParticleGenerator = nullptr;

	mTextScroll->Release();
	delete mTextScroll;
	mTextScroll = nullptr;
}
