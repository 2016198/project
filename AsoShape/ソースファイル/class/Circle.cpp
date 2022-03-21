#include <DxLib.h>
#include <math.h>
#include "Circle.h"

Circle::Circle(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	alive_ = true;
	vec_ = { 1.0f, 1.0f };
	def_color_ = color;
}

bool Circle::UpDate(float delta, Shape& ShapeVec)
{
	if (vec_.x_ > add_speed_.x_)//ç≈çÇë¨ìxÇí¥Ç¶Ç»Ç¢ÇÊÇ§Ç…Ç∑ÇÈ
	{
		vec_.x_ = add_speed_.x_;
	}
	else if (vec_.x_ < -add_speed_.x_)
	{
		vec_.x_ = -add_speed_.x_;
	}
	if (vec_.y_ > add_speed_.y_)
	{
		vec_.y_ = add_speed_.y_;
	}
	else if (vec_.y_ < -add_speed_.y_)
	{
		vec_.y_ = -add_speed_.y_;
	}
	if (stop_t_ <= 0.0f)
	{
		pos_.x_ += speed_.x_ * delta * 60 * vec_.x_;//à⁄ìÆ
		pos_.y_ += speed_.y_ * delta * 60 * vec_.y_;
	}

	if (pos_.x_ + size_.x_ > SCREEN_SIZE_X)//âÊñ äOÇ…èoÇ»Ç¢
	{
		pos_.x_ = SCREEN_SIZE_X - size_.x_;
		vec_.x_ *= -1;
		color_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
		def_color_ = color_;
	}
	else if (pos_.x_ - size_.x_ < 0)
	{
		pos_.x_ = size_.x_;
		vec_.x_ *= -1;
		color_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
		def_color_ = color_;
	}

	if (pos_.y_ + size_.y_ > SCREEN_SIZE_Y)
	{
		pos_.y_ = SCREEN_SIZE_Y - size_.y_;
		vec_.y_ *= -1;
		color_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
		def_color_ = color_;
	}
	else if (pos_.y_ - size_.y_ < 0)
	{
		pos_.y_ = size_.y_;
		vec_.y_ *= -1;
		color_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
		def_color_ = color_;
	}
	if (vec_.x_ > 1.0f)//ç≈í·ë¨ìxÇÃê›íË
	{
		vec_.x_ -= 0.05f;
	}
	else if (vec_.x_ < -1.0f)
	{
		vec_.x_ += 0.05f;
	}
	if (vec_.y_ > 1.0f)
	{
		vec_.y_ -= 0.05f;
	}
	else if (vec_.y_ < -1.0f)
	{
		vec_.y_ += 0.05f;
	}
	stop_t_ -= delta;
	return false;
}

void Circle::Draw(void)
{
	//DrawOval((int)(pos_.x_), (int)(pos_.y_), (int)(pos_.x_ + size_.x_), (int)(pos_.y_ + size_.y_), GetColor(255, 255, 0), false);
	DrawCircle((int)(pos_.x_),
				(int)(pos_.y_), 
				(int)(size_.x_),
				color_,
				true);
	color_ = def_color_;
}

void Circle::Draw(float exp)
{
	//DrawOval((int)(pos_.x_), (int)(pos_.y_), (int)(pos_.x_) + (int)(size_.x_ * exp), (int)(pos_.y_) + (int)(size_.y_ * exp), GetColor(255, 255, 0), false);
	DrawCircle((int)(pos_.x_),
				(int)(pos_.y_),
				(int)(size_.x_ * exp),
				color_,
				true);
}

void Circle::Draw(float exp, Vector2Flt offset)
{
	Vector2Flt pos{ pos_ + offset - size_ * exp * offset / size_ };

	/*DrawOval(
		(int)(pos.x_),
		(int)(pos.y_),
		(int)(pos.x_ + (size_.x_ * exp)),
		(int)(pos.y_ + (size_.y_ * exp)),
		GetColor(255, 0, 0),
		false);*/
	DrawCircle(
		(int)(pos.x_),
		(int)(pos.y_),
		(int)(size_.x_ * exp),
		color_,
		true);
}

bool Circle::IsAlive(void)
{
	return alive_;
}

ShapeType Circle::GetType(void)
{
	return ShapeType::CIRCLE;
}

Vector2Flt Circle::GetPos(void)
{
	return pos_;
}

Vector2Flt Circle::GetSize(void)
{
	return size_;
}

ShapeType Circle::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)//Ç†ÇΩÇËÇÕÇÒÇƒÇ¢
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
		//â~ÇÃç∂Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos_.x_ - size_.x_ > pos.x_ &&
			pos_.x_ - size_.x_< pos.x_ + size.x_ &&
			pos_.y_ > pos.y_ &&
			pos_.y_ < pos.y_ + size.y_)
		{
			stop_t_ = 2.0f;
		}
		//â~ÇÃâEÇ™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos_.x_ + size_.x_ > pos.x_ &&
			pos_.x_ + size_.x_< pos.x_ + size.x_ &&
			pos_.y_ > pos.y_ &&
			pos_.y_ < pos.y_ + size.y_)
		{
			stop_t_ = 2.0f;
		}
		//â~ÇÃè„Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos_.x_ > pos.x_ &&
			pos_.x_ < pos.x_ + size.x_ &&
			pos_.y_ - size_.x_> pos.y_ &&
			pos_.y_ - size_.x_ < pos.y_ + size.y_)
		{
			stop_t_ = 2.0f;
		}
		//â~ÇÃâ∫Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos_.x_ > pos.x_ &&
			pos_.x_< pos.x_ + size.x_ &&
			pos_.y_ + size_.x_ > pos.y_ &&
			pos_.y_ + size_.x_ < pos.y_ + size.y_)
		{
			stop_t_ = 2.0f;
		}
		break;
	case ShapeType::CIRCLE:
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
		hypot = hypotf(diffTL.x_, diffTL.y_);
		if (hypot <= size_.x_ + size.x_)
		{
			vec_ *= add_speed_;
		}
		break;
	case ShapeType::MAX:
		break;
	default:
		break;
	}
	return  ShapeType::MAX;
}

