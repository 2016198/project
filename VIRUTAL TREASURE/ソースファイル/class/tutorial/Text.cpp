#include <DxLib.h>
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include "Text.h"

Text::Text()
{
	Init();
}

Text::~Text()
{

}

bool Text::Init(void)
{
	SetText("solo");
	font_ = LoadFontDataToHandle("font/font.dft");
	if (font_ == -1)
	{
		return false;
	}
	sound_ = LoadSoundMem("sound/DB.wav");
	if (sound_ == -1)
	{
		return false;
	}
	pos_ = 100;
	return true;
}

void Text::SetText(std::string key)
{
	type_ = key;
	lpTextMng.LoadTMX("tmx/text.tmx", type_);
	text_ = lpTextMng.GetData();
	parentItr_ = text_[type_].begin();
	childItr_ = (*parentItr_).begin();
}

TEXT_MODE Text::Update(const InputList input1, const InputList input2, bool progress)
{
	//ëÄçÏÉLÅ[ÇéÊìæ
	input_[0] = input1;
	input_[1] = input2;

	if (childItr_ != (*parentItr_).end())
	{
		if (input_[0][INPUT_LIST::A][KEY::TRG_DOWN] || input_[1][INPUT_LIST::A][KEY::TRG_DOWN])
		{
			++childItr_;
			pos_ = 100;
			PlaySoundMem(sound_, DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		if (progress == true)
		{
			if (text_[type_].end() != parentItr_ + 1)
			{
				++parentItr_;
				childItr_ = (*parentItr_).begin();
			}
			else
			{
				return TEXT_MODE::CHANGE;
			}
		}
		return TEXT_MODE::OPERATION;
	}
	return TEXT_MODE::MANUAL;
}

void Text::Draw(double delta)
{
	if (childItr_ != (*parentItr_).end())
	{
		DrawBox(100, 300, 540, 400, 0xffffff, true);
		DrawFormatStringToHandle(100, 300, 0, font_, "%s", (*childItr_).c_str());
		if (pos_ < 540)
		{
			DrawBox(pos_, 300, 540, 400, 0xffffff, true);
			pos_ += static_cast<int>(delta * 2.0);
		}
		else
		{
			pos_ = 540;
		}
	}
}

void Text::Release(void)
{
	text_.clear();
	DeleteFontToHandle(font_);
	DeleteSoundMem(sound_);
}

std::vector<std::string>::iterator Text::GetChildItr(void)
{
	return childItr_;
}

std::vector<std::vector<std::string>>::iterator Text::GetParentItr(void)
{
	return parentItr_;
}
