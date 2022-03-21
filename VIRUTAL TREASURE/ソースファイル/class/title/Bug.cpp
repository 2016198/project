#include <Dxlib.h>
#include "Bug.h"

Bug::Bug(int image) : image_(image)
{
	life_ = 100.0;
}

void Bug::Generate(Vector2 pos, double angle, double life)
{
	pos_ = pos;
	angle_ = angle;
	life_ = life;
}

void Bug::Update(double delta)
{
	life_ -= delta;
}

void Bug::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y, 0.7, angle_, image_, true);
}

bool Bug::IsAlive(void)
{
	return life_ > 0.0;
}
