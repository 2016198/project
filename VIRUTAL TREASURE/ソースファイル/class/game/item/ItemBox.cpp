#include <DxLib.h>
#include "../../Color3.h"
#include "ItemBox.h"
#include "../Map.h"

void ItemBox::Generate(int pos, ITEM type, unsigned int color)
{
	pos_.x = (OFFSET_X - POINT_SIZE) + ((pos % 6) * OFFSET_SIZE);
	pos_.y = (OFFSET_Y - POINT_SIZE) + ((pos / 6) * OFFSET_SIZE);
	color_ = color;
	type_ = type;
	delta_ = 0.0;
	image_.resize(ANIM_COUNT);
	fream_ = 0;

	alive_ = true;
}

void ItemBox::Draw(double delta)
{
	fream_++;
	DrawRotaGraph(pos_.x, pos_.y, 1.5, 0.0, image_[fream_ / 5 % ANIM_COUNT], false);
}

ItemBox::ItemBox(std::vector<int> image) : image_(image)
{

}

ItemBox::~ItemBox()
{
}

int ItemBox::IsGetItem(Vector2 pos1, Vector2 pos2)
{
	if (pos1 == pos_)
	{
		return 1;
	}

	if (pos2 == pos_)
	{
		return 2;
	}

	return 0;
}

int ItemBox::IsGetItem(Vector2 pos)
{
	if (pos == pos_)
	{
		return 1;
	}

	return 0;
}

void ItemBox::Distroy(double delta)
{
	delta_ += delta;
	if (delta_ > 200.0)
	{
		alive_ = false;
	}
}

Vector2 ItemBox::GetDrawPos(void)
{
	return pos_;
}

ITEM ItemBox::GetItemInfo(void)
{
	return type_;
}
