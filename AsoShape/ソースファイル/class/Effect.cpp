#include <DxLib.h>
#include "Effect.h"

Effect::Effect(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	alive_ = true;
	ness_ = GetRand(4) + 1;
	time_ = GetRand(150) / 100.0f + 0.5f;
	delta_t_ = 0.0f;
}

void Effect::Draw(void)
{
	DrawLine(pos_.x_, pos_.y_, pos_.x_ + size_.x_, pos_.y_ + size_.y_, color_, ness_);
}

void Effect::Draw(float exp)
{

}

void Effect::Draw(float exp, Vector2Flt offset)
{

}

bool Effect::UpDate(float delta, Shape& ShapeVec)
{
	delta_t_ += delta;
	size_ += speed_;
	if (delta_t_ > time_)
	{
		alive_ = false;
	}
	return false;
}

bool Effect::IsAlive(void)
{
	return alive_;
}

ShapeType Effect::GetType(void)
{
	return ShapeType::MAX;
}

Vector2Flt Effect::GetPos(void)
{
	return pos_;
}

Vector2Flt Effect::GetSize(void)
{
	return size_;
}

ShapeType Effect::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)
{
	return ShapeType::MAX;
}
