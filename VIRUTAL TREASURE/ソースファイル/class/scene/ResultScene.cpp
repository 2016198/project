#include <DxLib.h>
#include "../manager/MaterialManager.h"
#include "ResultScene.h"

ResultScene::ResultScene(INPUT_TYPE type, const int num, const SCENE_ID beforeScene):
	BaseScene(type)
{
	winPlayer_ = num;
	beforeScene_ = beforeScene;
	Init();
}

ResultScene::~ResultScene()
{
}

bool ResultScene::Init(void)
{
	//screen_ = MakeScreen(screen_sizeX, screen_sizeY);
	image_ = lpMaterialMng.LoadGraphHandle("image/back/ResultScene.jpg");
	if (image_ == -1)
	{
		return false;
	}
	screen_ = lpMaterialMng.LoadScreenic("result", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	selectNum_ = beforeScene_;
	color_.resize(2U);
	color_[0] = 0x888888;
	color_[1] = 0xffffff;
	return true;
}

SCENE_ID ResultScene::Update(double delta)
{
	//入力情報の取得
	for (int t = 0; t < 2; t++)
	{
		ptr_[t]->SetKeyList(inputType_);
		input_[t] = ptr_[t]->GetCntData();
	}

	for (auto& c : color_)
	{
		c = 0xffffff;
	}

	if ((input_[0][INPUT_LIST::DOWN][KEY::TRG_DOWN] || input_[1][INPUT_LIST::DOWN][KEY::TRG_DOWN])
		&& selectNum_ == beforeScene_)
	{
		select_ = 1;
		selectNum_ = SCENE_ID::TITLE;
	}
	if ((input_[0][INPUT_LIST::UP][KEY::TRG_DOWN] || input_[1][INPUT_LIST::UP][KEY::TRG_DOWN])
		&& selectNum_ == SCENE_ID::TITLE)
	{
		select_ = 0;
		selectNum_ = beforeScene_;
	}

	color_[select_] = 0x888888;

	if (input_[0][INPUT_LIST::A][KEY::TRG_DOWN] || input_[1][INPUT_LIST::A][KEY::TRG_DOWN])
	{
		return selectNum_;		//選択したシーンへ移動
	}
	return SCENE_ID::CONTINUE;
}

int ResultScene::Draw(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	DrawGraph(0, 0, image_, true);

	DrawBox(100, 50, 540, 200, 0xffff00, true);

	for (int a = 0; a < 2; a++)
	{
		offsetFont_ = GetDrawStringWidthToHandle(str_[a], static_cast<int>(strlen(str_[a])), font_) / 2;
		DrawBox(150, 230 + 150 * a, 490, 265 + 150 * a, color_[a], true);
		DrawStringToHandle(SCREEN_SIZE_X / 2 - offsetFont_, 230 + a * 150, str_[a], 0, font_);
	}

	DrawBox(150, 230 + 150 * select_, 490, 265 + 150 * select_, 0, false);

	DrawStringToHandle(200, 60, "ResultScene", 0, font_);
	DrawFormatStringToHandle(180, 100, 0, font_, "プレイヤー%dの勝利!", winPlayer_);
	
	return screen_;
}

void ResultScene::Release(void)
{
	lpMaterialMng.DeleteGraphHandle("result");
	lpMaterialMng.DeleteGraphHandle("image/back/ResultScene.jpg");
	DeleteFontToHandle(font_);
}

const int ResultScene::GetNum(void)
{
	return 0;
}

const SCENE_ID ResultScene::GetScene(void)
{
	return SCENE_ID::RESULT;
}
