#include <DxLib.h>
#include "Bullet.h"

Bullet::Bullet(Vector2 pos, bool isLeft)
{
	Init(pos, isLeft);
}

Bullet::~Bullet()
{

}

bool Bullet::Init(Vector2 pos, bool isLeft)
{
	moveLeft_ = isLeft;
	pos_ = { static_cast<double>(pos.x_), static_cast<double>(pos.y_)};
	arive_ = 81.0;
	speed_ = 6.5;
	return true;
}

void Bullet::UpDate()
{
	if (arive_ > 0.0)
	{
		if (moveLeft_)
		{
			pos_.x_ -= speed_;
		}
		else
		{
			pos_.x_ += speed_;
		}
		arive_ -= 0.6;
	}
}

void Bullet::Draw()
{
	if (arive_ > 0.0)
	{
		DrawCircle(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), 20, 0x770000);
		if (moveLeft_)
		{
			DrawCircle(static_cast<int>(pos_.x_) + 4, static_cast<int>(pos_.y_), 18, 0x000000);
		}
		else
		{
			DrawCircle(static_cast<int>(pos_.x_) - 4, static_cast<int>(pos_.y_), 18, 0x000000);
		}
	}
}
