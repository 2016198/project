#include <DxLib.h>
#include "TextPool.h"
#include "TextData.h"

void TextData::Generate(std::string text, Vector2 pos, double life, unsigned int color)
{
	text_ = text;
	pos_ = pos;
	int half_height = GetFontSize() / 2;
	int width = GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(text.size()), lpTextPool.font_);
	int half_width = width / 2;
	pos_.y -= half_height;
	pos_.x -= half_width;
	int diff = 0, x, y;
	GetDrawScreenSize(&x, &y);
	//‰æ–ÊŠO‚É‚Í‚Ýo‚³‚È‚¢‚æ‚¤‚É‚·‚é
	if (pos_.x + width > x)
	{
		diff = pos_.x + width - x;
	}
	else if (pos_.x < 0)
	{
		pos_.x = 0;
	}
	pos_.x -= diff;
	life_ = life;
	color_ = color;
}

void TextData::Draw(double delta, int fontID)
{
	if (life_ > 0.0)
	{
		DrawStringToHandle(pos_.x, pos_.y, text_.c_str(), color_, fontID);
		life_ -= delta;
		pos_.y--;
	}
}

TextData::TextData()
{
	color_ = 0;
}

TextData::~TextData()
{

}

bool TextData::IsAlive()
{
	return life_ > 0.0;
}
