#include <DxLib.h>
#include <math.h>
#include "Star.h"

Star::Star(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	vec_ = { 1.0f, 1.0f };
	alive_ = true;
	def_color_ = color;
}

void Star::Draw(void)
{
	/*for (int t = 0; t < 5;t++)
	{
		DrawCircle((int)(pos_.x_ + size_.x_ * sin(PAI * (t * 2) / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * (t * 2) / 5)), 3, 0xff0000);
	}*/
	DrawTriangle(
		(int)(pos_.x_ + (size_.x_ / 3) * sin(PAI * 5 / 5)), (int)(pos_.y_ - (size_.y_ / 3) * cos(PAI * 5 / 5)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 6 / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * 6 / 5)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 0 / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * 0 / 5)),
		color_, true);
	DrawTriangle(
		(int)(pos_.x_ + (size_.x_ / 3) * sin(PAI * 5 / 5)), (int)(pos_.y_ - (size_.y_ / 3) * cos(PAI * 5 / 5)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 4 / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * 4 / 5)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 0 / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * 0 / 5)),
		color_, true);
	DrawTriangle(
		(int)(pos_.x_ + (size_.x_ / 3) * sin(PAI * 5 / 5)), (int)(pos_.y_ - (size_.y_ / 3) * cos(PAI * 5 / 5)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 2 / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * 2 / 5)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 8 / 5)), (int)(pos_.y_ - size_.y_ * cos(PAI * 8 / 5)),
		color_, true);
	//DrawCircle((int)pos_.x_, (int)pos_.y_, 5, 0x33ff33);
	//DrawCircle((int)pos_.x_, (int)pos_.y_, 3, 0xff0000);
	color_ = def_color_;
}

void Star::Draw(float exp)
{
	/*DrawTriangle(
		(int)(pos_.x_ + (size_.x_ * exp / 3) * sin(PAI * 5 / 5)), (int)(pos_.y_ - (size_.y_ * exp / 3) * cos(PAI * 5 / 5)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 6 / 5)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 6 / 5)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 0 / 5)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 0 / 5)),
		color_, true);
	DrawTriangle(
		(int)(pos_.x_ + (size_.x_ * exp / 3) * sin(PAI * 5 / 5)), (int)(pos_.y_ - (size_.y_ * exp / 3) * cos(PAI * 5 / 5)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 4 / 5)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 4 / 5)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 0 / 5)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 0 / 5)),
		color_, true);
	DrawTriangle(
		(int)(pos_.x_ + (size_.x_ * exp / 3) * sin(PAI * 5 / 5)), (int)(pos_.y_ - (size_.y_ * exp / 3) * cos(PAI * 5 / 5)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 2 / 5)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 2 / 5)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 8 / 5)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 8 / 5)),
		color_, true);*/
}

void Star::Draw(float exp, Vector2Flt offset)
{
	/*Vector2Flt pos{ pos_ + offset - size_ * exp * offset / size_ };
	DrawTriangle(
		(int)(pos.x_ + (size_.x_ * exp / 3) * sin(PAI * 5 / 5)), (int)(pos.y_ - (size_.y_ * exp / 3) * cos(PAI * 5 / 5)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 6 / 5)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 6 / 5)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 0 / 5)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 0 / 5)),
		color_, true);
	DrawTriangle(
		(int)(pos.x_ + (size_.x_ * exp / 3) * sin(PAI * 5 / 5)), (int)(pos.y_ - (size_.y_ * exp / 3) * cos(PAI * 5 / 5)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 4 / 5)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 4 / 5)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 0 / 5)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 0 / 5)),
		color_, true);
	DrawTriangle(
		(int)(pos.x_ + (size_.x_ * exp / 3) * sin(PAI * 5 / 5)), (int)(pos.y_ - (size_.y_ * exp / 3) * cos(PAI * 5 / 5)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 2 / 5)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 2 / 5)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 8 / 5)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 8 / 5)),
		color_, true);*/
}

bool Star::UpDate(float delta, Shape& ShapeVec)
{
	if (vec_.x_ > add_speed_.x_)//最高速度を超えないようにする
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
		pos_.x_ += speed_.x_ * delta * 60 * vec_.x_;
		pos_.y_ += speed_.y_ * delta * 60 * vec_.y_;
	}
	Vector2Flt posT = { (float)(pos_.x_ + size_.x_ * sin(PAI * 0 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 0 / 5)) };
	Vector2Flt posR = { (float)(pos_.x_ + size_.x_ * sin(PAI * 2 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 2 / 5)) };
	Vector2Flt posBR = { (float)(pos_.x_ + size_.x_ * sin(PAI * 4 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 4 / 5)) };
	Vector2Flt posBL = { (float)(pos_.x_ + size_.x_ * sin(PAI * 6 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 6 / 5)) };
	Vector2Flt posL = { (float)(pos_.x_ + size_.x_ * sin(PAI * 8 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 8 / 5)) };
	if (posR.x_ > SCREEN_SIZE_X)
	{
		vec_.x_ *= -1;
		pos_.x_ = SCREEN_SIZE_X - size_.x_ * (float)(sin(PAI * 2 / 5));
		return true;
	}
	if (posL.x_ < 0)
	{
		vec_.x_ *= -1;
		pos_.x_ = 0 - size_.x_ * (float)(sin(PAI * 8 / 5));
		return true;
	}
	if (posBL.y_ > SCREEN_SIZE_Y)
	{
		vec_.y_ *= -1;
		pos_.y_ = SCREEN_SIZE_Y + size_.y_ * (float)(cos(PAI * 6 / 5));
		return true;
	}
	if (posT.y_ < 0)
	{
		vec_.y_ *= -1;
		pos_.y_ = size_.y_ * (float)(cos(PAI * 0 / 2));
		return true;
	}
	if (vec_.x_ > 1.0f)//最低速度の設定
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

bool Star::IsAlive(void)
{
	return alive_;
}

ShapeType Star::GetType(void)
{
	return ShapeType::STAR;
}

Vector2Flt Star::GetPos(void)
{
	return pos_;
}

Vector2Flt Star::GetSize(void)
{
	return size_;
}

ShapeType Star::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)
{
	float hypot = 0.0f;

	Vector2Flt sq_pos[4] = {
		pos,
		{pos.x_ + size.x_,pos.y_},
		{pos.x_ ,pos.y_ + size.y_},
		{pos.x_ + size.x_,pos.y_ + size.y_},
	};

	Vector2Flt posT = { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 3)) };
	Vector2Flt posBL = { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 3)),(float)(pos.y_ - size.y_ * cos(PAI * 2 / 3)) };
	Vector2Flt posBR = { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 3)) };

	Vector2Flt st_pos[6] = {
	 { (float)(pos_.x_ + size_.x_ * sin(PAI * 0 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 0 / 5)) },
	 { (float)(pos_.x_ + size_.x_ * sin(PAI * 2 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 2 / 5)) },
	 { (float)(pos_.x_ + size_.x_ * sin(PAI * 4 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 4 / 5)) },
	 { (float)(pos_.x_ + size_.x_ * sin(PAI * 6 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 6 / 5)) },
	 { (float)(pos_.x_ + size_.x_ * sin(PAI * 8 / 5)), (float)(pos_.y_ - size_.y_ * cos(PAI * 8 / 5)) },
	 { pos_.x_, pos_.y_ } };

	Vector2Flt diff_st[15] = {
		st_pos[0] - posT,
		st_pos[0] - posBL,
		st_pos[0] - posBR,
		st_pos[1] - posT,
		st_pos[1] - posBL,
		st_pos[1] - posBR,
		st_pos[2] - posT,
		st_pos[2] - posBL,
		st_pos[2] - posBR,
		st_pos[3] - posT,
		st_pos[3] - posBL,
		st_pos[3] - posBR,
		st_pos[4] - posT,
		st_pos[4] - posBL,
		st_pos[4] - posBR,
	};

	//ベクトル差分変数
	Vector2Flt AB = { 0.0f,0.0f };
	Vector2Flt BP = { 0.0f,0.0f };

	Vector2Flt BC = { 0.0f,0.0f };
	Vector2Flt CP = { 0.0f,0.0f };

	Vector2Flt CA = { 0.0f,0.0f };
	Vector2Flt AP = { 0.0f,0.0f };

	//外積の計算Zだけを計算する
	float gai[3] = { 0.0f,0.0f, 0.0f };

	switch (type)
	{
	case ShapeType::SQUARE:
		for (int r = 0; r < 6; r++)
		{
			if (pos.x_ <= st_pos[r].x_ &&
				pos.x_ + size.x_ >= st_pos[r].x_ &&
				pos.y_ <= st_pos[r].y_ &&
				pos.y_ + size.y_ >= st_pos[r].y_)
			{
				stop_t_ = 2.0f;
			}
		}
		break;
	case ShapeType::CIRCLE:
		for (int w = 0; w < 5; w++)
		{
			st_pos[w] -= pos;
			hypot = hypotf(st_pos[w].x_, st_pos[w].y_);
			if (hypot <= size.x_)
			{
				color_ = 0x111111;
			}
		}
		break;
	case ShapeType::TRIANGLE:
		for (int t = 0; t < 6; t++)
		{
			AB = posBL - posT;
			BP = st_pos[t] - posBL;

			BC = posBR - posBL;
			CP = st_pos[t] - posBR;

			CA = posT - posBR;
			AP = st_pos[t] - posT;

			gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
			gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
			gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
			if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
			{
				color_ = 0xff0000;
				return ShapeType::TRIANGLE;
			}
		}
		break;
	case ShapeType::STAR:
		break;
	case ShapeType::TREFOIL:
		for (int r = 0; r < 15; r++)
		{
			hypot = hypotf(diff_st[r].x_, diff_st[r].y_);
			if (hypot <= size.x_)
			{
				color_ = 0x0000ff;
			}
		}
		AB = posBL - posT;
		BP = pos_ - posBL;

		BC = posBR - posBL;
		CP = pos_ - posBR;

		CA = posT - posBR;
		AP = pos_ - posT;

		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0x0000ff;
		}
		break;
	case ShapeType::CROSS:
		for (int w = 0; w < 5; w++)
		{
			st_pos[w] -= pos;
			hypot = hypotf(st_pos[w].x_, st_pos[w].y_);
			if (hypot <= size.x_)
			{
				vec_ *= add_speed_;
			}
		}
		break;
	case ShapeType::MAX:
		break;
	default:
		break;
	}
	return  ShapeType::MAX;
}
