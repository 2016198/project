#include <DxLib.h>
#include "../manager/MaterialManager.h"
#include "Map.h"
#include "Fire.h"

Fire::Fire(std::vector<int> imageVec) : image_(imageVec)
{

}

Fire::~Fire()
{

}

void Fire::Create(int num)
{
	switch (num)
	{
	case 0:
		pos_ = 0;
		break;
	case 1:
		pos_ = 24;
		break;
	case 2:
		pos_ = 4;
		break;
	case 3:
		pos_ = 20;
		break;
	}
	offsetSize_.x = 12;
	offsetSize_.y = 12;
	size_ = 0.8;
	move_ = 0;
	alive_ = true;
}

void Fire::Update(void)
{
	drawPos_.x = (OFFSET_X + ((pos_ % POINT_COUNT) * OFFSET_SIZE)) + offsetSize_.x;
	drawPos_.y = (OFFSET_Y + ((pos_ / POINT_COUNT) * OFFSET_SIZE)) + offsetSize_.y;
}

void Fire::Move(MOVE_DIR dir)
{
	move_++;
	int num = move_ / 5 + 1;
	size_ = static_cast<double>(num);
	switch (dir)
	{
	case MOVE_DIR::LEFT:
		if (pos_ % POINT_COUNT != 0)
		{
			pos_--;
		}
		else
		{
			pos_++;
		}
		break;
	case MOVE_DIR::RIGHT:
		if (pos_ % POINT_COUNT != 4)
		{
			pos_++;
		}
		else
		{
			pos_--;
		}
		break;
	case MOVE_DIR::UP:
		if (pos_ - POINT_COUNT >= 0)
		{
			pos_ -= POINT_COUNT;
		}
		else
		{
			pos_ += POINT_COUNT;
		}
		break;
	case MOVE_DIR::DOWN:
		if (pos_ + POINT_COUNT <= POINT_SIZE - 1)
		{
			pos_ += POINT_COUNT;
		}
		else
		{
			pos_ -= POINT_COUNT;
		}
		break;
	}
}

void Fire::Draw(void)
{
	DrawRotaGraph(drawPos_.x, drawPos_.y, size_, 0.0, image_[0], true);
}

bool Fire::Check(int pos)
{
	if (pos == pos_)
	{
		alive_ = false;
		return true;
	}
	return false;
}

bool Fire::IsAlive(void)
{
	return alive_;
}