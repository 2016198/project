#include <DxLib.h>
#include "BaseScene.h"

BaseScene::BaseScene()
{
	SetDrawScreen(DX_SCREEN_BACK);
	GetDrawScreenSize(&ScreenSize_.x_, &ScreenSize_.y_);
	ScreenID_ = MakeScreen(ScreenSize_.x_, ScreenSize_.y_, true);
	GetDrawScreenSize(&x_, &y_);
}

BaseScene::~BaseScene()
{

}

void BaseScene::Draw(double delta)
{
	//DrawBox(0, 0, x_, y_, 0xffffff, true);
	DrawGraph(0, 0, ScreenID_, true);
}

