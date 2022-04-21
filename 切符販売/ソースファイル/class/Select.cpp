#include <DxLib.h>
#include "Select.h"

Select::Select()//コンストラクタ
{
	scene_ = SCENE_ID::SELECT;
	color_.resize(2U);
	Init();
	UpDate();
}

Select::~Select()//デストラクタ
{
}

bool Select::Init(void)//初期化処理
{
	for (auto& c : color_)
	{
		c = WHITE;
	}
	return true;
}

void Select::UpDate(void)//更新処理
{
	GetMousePoint(&x_, &y_);

	//戻るボタン
	if (HitBack())
	{
		colorB_ = RED;
	}
	else
	{
		colorB_ = GRAY;
	}
	
	if (x_ > 99 && y_ > 100 &&
		x_ < 299 && y_ < 400)
	{
		color_[0] = YELLOW;
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			scene_ = SCENE_ID::CASH;
		}
	}
	else
	{
		color_[0] = WHITE;
	}

	if (x_ > 341 && y_ > 100 &&
		x_ < 541 && y_ < 400)
	{
		color_[1] = YELLOW;
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			scene_ = SCENE_ID::ELEMONEY;
		}
	}
	else
	{
		color_[1] = WHITE;
	}
}

void Select::Draw(void)//描画処理
{
	width_ = GetDrawExtendStringWidth(2.0, MSG_SELECT, static_cast<int>(strlen(MSG_SELECT))) / 2;
	DrawExtendString(SCREEN_SIZE_X / 2 - width_, 50, 2.0, 2.0, MSG_SELECT, WHITE.GetColorCode());

	DrawBox(99, 100, 299, 400, color_[0].GetColorCode(), false);
	DrawBox(341, 100, 541, 400, color_[1].GetColorCode(), false);

	DrawExtendString(158, 160, 5.0, 5.0, "現\n金", color_[0].GetColorCode());
	DrawExtendString(378, 128, 3.5, 3.5, "電\n子マ\n　ネ\n　｜", color_[1].GetColorCode());
}
