#include <DxLib.h>
#include <math.h>
#include "Cross.h"

Cross::Cross(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	alive_ = true;
	vec_ = { 1.0f, 1.0f };
	def_color_ = color;
}

void Cross::Draw(void)
{
	static int c = 0;
	DrawLine(
		(int)(pos_.x_ + size_.x_ * cos(PAI * (c  % 360) / 180)), (int)(pos_.y_ - size_.x_ * sin(PAI * ((c + 0) % 360) / 180)),
		(int)(pos_.x_ + size_.x_ * cos(PAI * ((c + 180) % 360) / 180)), (int)(pos_.y_ - size_.x_ * sin(PAI * ((c + 180) % 360) / 180)),
		color_, (int)size_.y_);
	DrawLine(
		(int)(pos_.x_ + size_.x_ * cos(PAI * ((c + 90) % 360) / 180)), (int)(pos_.y_ - size_.x_ * sin(PAI * ((c + 90) % 360) / 180)),
		(int)(pos_.x_ + size_.x_ * cos(PAI * ((c + 270) % 360) / 180)), (int)(pos_.y_ - size_.x_ * sin(PAI * ((c + 270) % 360) / 180)),
		color_, (int)size_.y_);
	c -= 10;
	color_ = def_color_;
}

void Cross::Draw(float exp)
{
}

void Cross::Draw(float exp, Vector2Flt offset)
{
}

bool Cross::UpDate(float delta, Shape& ShapeVec)
{
	if (stop_t_ <= 0.0f)
	{
		pos_.x_ += speed_.x_ * delta * 60 * vec_.x_;//à⁄ìÆ
		pos_.y_ += speed_.y_ * delta * 60 * vec_.y_;
	}

	if (pos_.x_ + size_.x_ > SCREEN_SIZE_X)//âÊñ äOÇ…èoÇ»Ç¢
	{
		pos_.x_ = SCREEN_SIZE_X - size_.x_;
		vec_.x_ *= -1;
	}
	else if (pos_.x_ - size_.x_ < 0)
	{
		pos_.x_ = size_.x_;
		vec_.x_ *= -1;
	}

	if (pos_.y_ + size_.x_ > SCREEN_SIZE_Y)
	{
		pos_.y_ = SCREEN_SIZE_Y - size_.x_;
		vec_.y_ *= -1;
	}
	else if (pos_.y_ - size_.x_ < 0)
	{
		pos_.y_ = size_.x_;
		vec_.y_ *= -1;
	}
	stop_t_ -= delta;
	return false;
}

bool Cross::IsAlive(void)
{
	return alive_;
}

ShapeType Cross::GetType(void)
{
	return ShapeType::CROSS;
}

Vector2Flt Cross::GetPos(void)
{
	return pos_;
}

Vector2Flt Cross::GetSize(void)
{
	return size_;
}

ShapeType Cross::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)
{
	float hypot = 0.0f;
	Vector2Flt diffTL = pos_ - pos;
	Vector2Flt diffBR = pos_ - (pos + size);

	Vector2Flt st_diffT = { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 5)) };
	Vector2Flt st_diffR = { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 5)) };
	Vector2Flt st_diffBR = { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 5)) };
	Vector2Flt st_diffBL = { (float)(pos.x_ + size.x_ * sin(PAI * 6 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 6 / 5)) };
	Vector2Flt st_diffL = { (float)(pos.x_ + size.x_ * sin(PAI * 8 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 8 / 5)) };

	Vector2Flt tri_diffT = { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 3)) };
	Vector2Flt tri_diffBR = { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 3)) };
	Vector2Flt tri_diffBL = { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 3)) };

	st_diffT -= pos_;
	st_diffR -= pos_;
	st_diffL -= pos_;
	st_diffBL -= pos_;
	st_diffBR -= pos_;

	tri_diffT -= pos_;
	tri_diffBR -= pos_;
	tri_diffBL -= pos_;

	Vector2Flt tre_diff[3] = {
		tri_diffT,
		tri_diffBL,
		tri_diffBR
	};
	switch (type)
	{
	case ShapeType::SQUARE:
		hypot = hypotf(diffTL.x_, diffTL.y_);
		if ((int)hypot <= size_.x_)
		{
			stop_t_ = 2.0f;
		}
		hypot = hypotf(diffTL.x_, diffBR.y_);
		if ((int)hypot <= size_.x_)
		{
			stop_t_ = 2.0f;
		}
		hypot = hypotf(diffBR.x_, diffTL.y_);
		if ((int)hypot <= size_.x_)
		{
			stop_t_ = 2.0f;
		}
		hypot = hypotf(diffBR.x_, diffBR.y_);
		if ((int)hypot <= size_.x_)
		{
			stop_t_ = 2.0f;
		}
		break;
	case ShapeType::CIRCLE:
		hypot = hypotf(diffTL.x_, diffTL.y_);
		if (hypot <= size_.x_ + size.x_)
		{
			color_ = 0x111111;
		}
		break;
	case ShapeType::TRIANGLE:
		hypot = hypotf(tri_diffBR.x_, tri_diffBR.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		hypot = hypotf(tri_diffT.x_, tri_diffT.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		hypot = hypotf(tri_diffBL.x_, tri_diffBL.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		break;
	case ShapeType::STAR:
		hypot = hypotf(st_diffBR.x_, st_diffBR.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xffffff;
		}
		hypot = hypotf(st_diffT.x_, st_diffT.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xffffff;
		}
		hypot = hypotf(st_diffBL.x_, st_diffBL.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xffffff;
		}
		hypot = hypotf(st_diffL.x_, st_diffL.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xffffff;
		}
		hypot = hypotf(st_diffR.x_, st_diffR.y_);
		if (hypot <= size_.x_)
		{
			color_ = 0xffffff;
		}
		break;
	case ShapeType::TREFOIL:
		for (int e = 0; e < 3; e++)
		{
			hypot = hypotf(tre_diff[e].x_, tre_diff[e].y_);
			if (hypot <= size_.x_ + size.x_)
			{
				color_ = 0x0000ff;
			}
		}
		break;
	case ShapeType::CROSS:
		break;
	case ShapeType::MAX:
		break;
	default:
		break;
	}	
	return ShapeType::MAX;
}
