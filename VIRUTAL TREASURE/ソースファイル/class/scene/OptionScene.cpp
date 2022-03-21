#include <DxLib.h>
#include "../Color3.h"
#include "../manager/MaterialManager.h"
#include "../game/text/TextPool.h"
#include "OptionScene.h"

OptionScene::OptionScene(INPUT_TYPE type, bool clear) :
	BaseScene(type)
{
	clear_ = clear;
	Init();
}

OptionScene::~OptionScene()
{
}

bool OptionScene::Init(void)
{
	sound_[0] = lpMaterialMng.LoadSoundHandle("sound/DB.wav");
	sound_[1] = lpMaterialMng.LoadSoundHandle("sound/frog.wav");
	image_ = lpMaterialMng.LoadGraphHandle("image/back/OptionScene.jpg");
	imageOpt_ = lpMaterialMng.LoadGraphHandle("image/title/backTitle.png");
	helpImage_ = lpMaterialMng.LoadGraphHandle("image/help.png");
	font_ = lpMaterialMng.LoadFontHandle("font/font1.dft");

	img_.at(0) = lpMaterialMng.LoadGraphHandle("image/option/manual.png");
	img_.at(1) = lpMaterialMng.LoadGraphHandle("image/option/option.png");
	if (clear_ == false)
	{
		img_.at(2) = lpMaterialMng.LoadGraphHandle("image/option/unlock.png");
	}
	else
	{
		img_.at(2) = lpMaterialMng.LoadGraphHandle("image/option/tutorial.png");
	}

	if (font_ == -1)
	{
		return false;
	}
	if (image_ == -1)
	{
		return false;
	}
	if (imageOpt_ == -1)
	{
		return false;
	}
	if (helpImage_ == -1)
	{
		return false;
	}
	for (const auto i : img_)
	{
		if (i == -1)
		{
			return false;
		}
	}

	for (auto& t : offset_)
	{
		t.x = 0;
		t.y = 0;
	}

	offset_[0].x = 700;
	offset_[1].x = 600;
	offset_[2].x = 500;
	offset_[3].y = 1000;

	screen_ = lpMaterialMng.LoadScreenic("option", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	optionScreen_ = lpMaterialMng.LoadScreenic("type", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	select_ = 3;
	selectOption_ = 0;
	soundNum_ = 255;
	selectNum_ = SCENE_ID::TITLE;
	color_.resize(4U);
	color_[0] = 0xffffff;
	color_[1] = 0xffffff;
	color_[2] = 0xffffff;
	color_[3] = 0xffffff;
	size[0] = 0.0;
	size[1] = 0.0;
	zoom_[0] = false;
	zoom_[1] = false;
	lineColor_.Color3Code(0x777777);
	isSelect_ = 0;

	return true;
}

SCENE_ID OptionScene::Update(double delta)
{
	delta_ = delta;

	if (CheckMoveEnd())
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

		//上下選択
		if (zoom_[0] == false && zoom_[1] == false)
		{
			if ((input_[0][INPUT_LIST::UP][KEY::TRG_DOWN] || input_[1][INPUT_LIST::UP][KEY::TRG_DOWN])
				&& select_ > 0)
			{
				select_--;
				PlaySoundMem(sound_[0], DX_PLAYTYPE_BACK);
			}
			if ((input_[0][INPUT_LIST::DOWN][KEY::TRG_DOWN] || input_[1][INPUT_LIST::DOWN][KEY::TRG_DOWN])
				&& select_ < 3)
			{
				select_++;
				PlaySoundMem(sound_[0], DX_PLAYTYPE_BACK);
			}
		}

		color_[select_] = 0x888888;
		lineColor_.Color3Code(0x777777);

		//Bボタンでタイトルにカーソルが行く　
		//戻るボタンにカーソルがあるときに押すとタイトルへ…
		//ビデオに映し出されたココロの陰部 これは夢なのか現実なのか…。熱い真夏の夜 過熱した欲望はついに危険な領域へと突入する

		if ((input_[0][INPUT_LIST::B][KEY::TRG_DOWN] || input_[1][INPUT_LIST::B][KEY::TRG_DOWN]))
		{
			if (select_ == 3)
			{
				isSelect_ = true;
				return selectNum_;
			}
			if (zoom_[0] == false && zoom_[1] == false)
			{
				select_ = 3;
				PlaySoundMem(sound_[0], DX_PLAYTYPE_BACK);
			}
			else
			{
				zoom_[1] = zoom_[0] = false;
				isSelect_ = false;
				PlaySoundMem(sound_[1], DX_PLAYTYPE_BACK);
			}
		}

		//Aボタン(決定キー)を押したら
		if (input_[0][INPUT_LIST::A][KEY::TRG_DOWN] || input_[1][INPUT_LIST::A][KEY::TRG_DOWN])
		{
			if (select_ == 3)
			{
				isSelect_ = true;
				return selectNum_;
			}

			else if (select_ == 2)
			{
				zoom_[0] = !zoom_[0];
				isSelect_ = !isSelect_;
			}

			else if (select_ == 1)
			{
				isSelect_ = zoom_[1] = true;
			}

			PlaySoundMem(sound_[1], DX_PLAYTYPE_BACK);
		}

		if (size[1] > 0.0)
		{
			UpdateOption();
		}

		ZoomCommand(delta);
	}
	else
	{
		//画像の移動処理
		ImgMove();
	}

	return SCENE_ID::CONTINUE;//キーを押したら次のシーンへ移動
}

int OptionScene::Draw(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	DrawGraph(0, 0, image_, true);

	//タイトルへ戻る
	DrawBox(50, 380 + offset_[3].y, 155, 430 + offset_[3].y, color_[3], true);
	DrawBox(50, 380 + offset_[3].y, 155, 430 + offset_[3].y, 0x777777, false);
	DrawRotaGraph(100, 405 + offset_[3].y, 0.15, -0.3, imageOpt_, true, true);

	//オプション工項目
	for (int a = 0, b = 2; a < 3; a++, b--)
	{
		DrawBox(150 + offset_[a].x, 260 - (a * OFFSET), 500 + offset_[a].x, 330 - (a * OFFSET), color_[b], true);
		DrawExtendGraph(150 + offset_[a].x, 260 - (a * OFFSET), 500 + offset_[a].x, 330 - (a * OFFSET), img_[a], true);
	}
	for (int a = 0; a < 3; a++)
	{
		DrawBox(150 + offset_[a].x, 260 - (a * OFFSET), 500 + offset_[a].x, 330 - (a * OFFSET), 0x777777, false);
	}

	if (CheckMoveEnd())
	{
		for (int l = 0; l < 5; l++)
		{
			if (isSelect_)
			{
				lineColor_ = YELLOW;
			}
			switch (select_)
			{
			case 0:
			case 1:
			case 2:
				DrawBox(149 - l, 259 - l - ((2 - select_) * OFFSET), 501 + l, 331 + l - ((2 - select_) * OFFSET),
					lineColor_.GetColorCode(), false);
				break;
			case 3:
				DrawBox(49 - l, 379 - l, 156 + l, 430 + l,
					lineColor_.GetColorCode(), false);
			default:
				//なし
				break;
			}

			lineColor_ -= 20;
		}
	}

	if (size[0] > 0.0)
	{
		DrawRotaGraph(
			HALF_SCREEN_X,
			HALF_SCREEN_Y,
			size[0], 0.0,
			helpImage_, true);
	}

	if (size[1] > 0.0)
	{
		DrawOption();
	}

	//デバッグ用
	//if (input_[0][INPUT_LIST::MOUSE_LEFT][KEY::TRG_DOWN])
	//{
	//	int x, y;
	//	GetMousePoint(&x, &y);
	//	const char* theIMP[4] = {
	//		"1章　極道脅迫！体育部員たちの逆襲",
	//		"2章　モデル反撃！犯されるスカウトマン",
	//		//"3章　盗撮！そしてSM妄想へ…",
	//		"3章　空手部　性の裏技"
	//		"4章　昏睡レイプ！野獣と化した先輩"
	//	};
	//	lpTextPool.Generate(theIMP[rand() % 3], { x,y }, 400.0, GetColor(rand() % 256, rand() % 256, rand() % 256));
	//}

	return screen_;
}

void OptionScene::Release(void)
{
	lpMaterialMng.DeleteGraphHandle("option");
	lpMaterialMng.DeleteGraphHandle("type");
	lpMaterialMng.DeleteGraphHandle("image/back/OptionScene.jpg");
	lpMaterialMng.DeleteGraphHandle("image/title/backTitle.png");
	lpMaterialMng.DeleteGraphHandle("image/help.png");
	lpMaterialMng.DeleteSoundHandle("sound/DB.wav");
	lpMaterialMng.DeleteSoundHandle("sound/frog.wav");
	lpMaterialMng.DeleteGraphHandle("image/option/manual.png");
	lpMaterialMng.DeleteGraphHandle("image/option/option.png");
	if (clear_ == false)
	{
		lpMaterialMng.DeleteGraphHandle("image/option/unlock.png");
	}
	else
	{
		lpMaterialMng.DeleteGraphHandle("image/option/tutorial.png");
	}
}

const int OptionScene::GetNum(void)
{
	return 0;
}

const SCENE_ID OptionScene::GetScene(void)
{
	return SCENE_ID::OPTION;
}

void OptionScene::ImgMove(void)
{
	for (auto& t : offset_)
	{
		t.x -= 10;
		if (t.x <= 0)
		{
			t.x = 0;
		}
	}
	offset_[3].y -= 20;
	if (offset_[3].y <= 0)
	{
		offset_[3].y = 0;
	}
}

bool OptionScene::CheckMoveEnd(void)
{
	if (offset_[0].x <= 0 &&
		offset_[1].x <= 0 &&
		offset_[2].x <= 0 &&
		offset_[3].y <= 0)
	{
		return true;
	}
	return false;
}

void OptionScene::ZoomCommand(double delta)
{
	for (int cmd = 0; cmd < 2; cmd++)
	{
		if (zoom_[cmd] == true)//zoom処理
		{
			size[cmd] += delta / 150.0;
			if (size[cmd] > 1.0)
			{
				size[cmd] = 1.0;
			}
		}
		else
		{
			size[cmd] -= delta / 150.0;
			if (size[cmd] < 0.0)
			{
				size[cmd] = 0.0;
			}
		}
	}
}

void OptionScene::UpdateOption(void)
{
	if (input_[0][INPUT_LIST::DOWN][KEY::TRG_DOWN] || input_[1][INPUT_LIST::DOWN][KEY::TRG_DOWN])
	{
		if (selectOption_ < 1)
		{
			selectOption_++;
		}
	}

	if (input_[0][INPUT_LIST::UP][KEY::TRG_DOWN] || input_[1][INPUT_LIST::UP][KEY::TRG_DOWN])
	{
		if (selectOption_  > 0)
		{
			selectOption_--;
		}
	}

	if (input_[0][INPUT_LIST::A][KEY::TRG_DOWN] || input_[1][INPUT_LIST::A][KEY::TRG_DOWN])
	{
		if (selectOption_ == 0)
		{
			if (inputType_ == INPUT_TYPE::KEY)
			{
				inputType_ = INPUT_TYPE::PAD;
			}
			else
			{
				inputType_ = INPUT_TYPE::KEY;
			}
		}
	}

	if (selectOption_ == 1)
	{
		if (input_[0][INPUT_LIST::RIGHT][KEY::NOW] || input_[1][INPUT_LIST::RIGHT][KEY::NOW])
		{
			if (soundNum_ < 255)
			{
				soundNum_++;
			}
		}

		if (input_[0][INPUT_LIST::LEFT][KEY::NOW] || input_[1][INPUT_LIST::LEFT][KEY::NOW])
		{
			if (soundNum_ > 0)
			{
				soundNum_--;
			}
		}
	}
}

void OptionScene::DrawOption(void)
{
	SetDrawScreen(optionScreen_);
	ClsDrawScreen();

	//操作タイプと音量調整をする場所
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, WHITE.GetColorCode(), true);
	DrawExtendStringToHandle(20, 100, 1.5, 2.0, "操作タイプ" , BROWN.GetColorCode(), font_);
	DrawExtendStringToHandle(20, 280, 2.0, 2.0, "サウンド" , BROWN.GetColorCode(), font_);
	DrawBox(20, 100 + 180 * selectOption_ , 620, 165 + 180 * selectOption_, BLACK.GetColorCode(), false);
	DrawBox(300, 290, 303 + soundNum_, 330, BLUE.GetColorCode(), true);
	if (inputType_ == INPUT_TYPE::KEY)
	{
		DrawExtendStringToHandle(360, 100, 1.5, 2.0, message_[1], BLACK.GetColorCode(), font_);
	}
	else
	{
		DrawExtendStringToHandle(330, 100, 1.5, 2.0, message_[0], GREEN.GetColorCode(), font_);
	}

	SetDrawScreen(screen_);
	DrawRotaGraph(
		HALF_SCREEN_X,
		HALF_SCREEN_Y,
		size[1], 0.0,
		optionScreen_, true);
}
