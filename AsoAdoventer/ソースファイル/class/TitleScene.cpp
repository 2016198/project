#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "common/ImageMng.h"
#include "Transition/CrossOver.h"

TitleScene::TitleScene()
{
	Init();
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{

}

bool TitleScene::Init(void)
{
	lpImageMng.GetID("image/bg1.png","bg1.png");
	GetDrawScreenSize(&x_, &y_);
	return true;
}

uniqueScene TitleScene::UpDate(double delta, uniqueScene ownScene)
{
	if (CheckHitKey(KEY_INPUT_SPACE))//クロスオーバーシーンに切り替え
	{
		return std::make_unique<CrossOver>(
			3.0,
			std::move(ownScene),
			std::make_unique<GameScene>()
			);
	}
	DrawOwnScreen(delta);
	return ownScene;
}

void TitleScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(ScreenID_);
	ClsDrawScreen();
	DrawExtendGraph(100, 50, x_ - 100, y_ - 50, lpImageMng.GetID("bg1.png")[0], true);
	DrawString(401, 401, "スペースキーを押してください", 0);
	DrawString(400, 400, "スペースキーを押してください", 0xff00ff);
	
}

//bool TitleScene::Release(void)
//{
//	return true;
//}
