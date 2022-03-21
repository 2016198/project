#include <DxLib.h>
#include "TransitionScene.h"
#include"../../_debug/_DebugConOut.h"
#include"../../_debug/_DebugDispOut.h"

TransitionScene::TransitionScene(uniqueScene beforScene, uniqueScene afterScene)
{
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
	cnt = 0.0;
	SetDrawScreen(ScreenID_);
	ClsDrawScreen();
	beforScene_->Draw(0.0);
	TRACE("TransitionSceneÇÃê∂ê¨\n");
}

TransitionScene::~TransitionScene()
{

}

bool TransitionScene::Init(void)
{
	return true;
}

uniqueScene TransitionScene::UpDate(double delta, uniqueScene ownScene)
{
	if (UpDateTransition(delta))
	{
		return std::move(afterScene_);
	}
	DrawOwnScreen(delta);
	return ownScene;
}

