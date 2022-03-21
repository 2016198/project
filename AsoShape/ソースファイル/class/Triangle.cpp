#include <DxLib.h>
#include <math.h>
#include "Triangle.h"

Triangle::Triangle(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	alive_ = true;
	vec_ = { 1.0f, 1.0f };
	def_color_ = color;
}

bool Triangle::UpDate(float delta, Shape& ShapeVec)
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
	Vector2Flt posT = { (float)(pos_.x_ + size_.x_ * sin(PAI * 0 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 0 / 3)) };
	Vector2Flt posBR = { (float)(pos_.x_ + size_.x_ * sin(PAI * 2 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 2 / 3)) };
	Vector2Flt posBL = { (float)(pos_.x_ + size_.x_ * sin(PAI * 4 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 4 / 3)) };
	if (posT.y_ < 0)//当たり判定(上)
	{
		vec_.y_ *= -1;
		pos_.y_ = size_.y_ * (float)(cos(PAI * 0 / 3));
	}
	if (posBL.y_ > SCREEN_SIZE_Y)//当たり判定(下)
	{
		vec_.y_ *= -1;
		pos_.y_ = SCREEN_SIZE_Y + size_.y_ * (float)(cos(PAI * 2 / 3));
	}
	if (posBL.x_ < 0)//当たり判定(左)
	{
		vec_.x_ *= -1;
		pos_.x_ = size_.x_ * (float)(sin(PAI * 2 / 3));
	}
	if (posBR.x_ > SCREEN_SIZE_X)//当たり判定(右)
	{
		vec_.x_ *= -1;
		pos_.x_ = SCREEN_SIZE_X - size_.x_ * (float)(sin(PAI * 2 / 3));
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

void Triangle::Draw(void)
{
	DrawTriangle(
		(int)(pos_.x_ + size_.x_ * sin(PAI * 0 / 3)), (int)(pos_.y_ - size_.y_ * cos(PAI * 0 / 3)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 2 / 3)), (int)(pos_.y_ - size_.y_ * cos(PAI * 2 / 3)),
		(int)(pos_.x_ + size_.x_ * sin(PAI * 4 / 3)), (int)(pos_.y_ - size_.y_ * cos(PAI * 4 / 3)),
		color_, true);
	//DrawCircle((int)pos_.x_, (int)pos_.y_, 5, 0xffffff);
	color_ = def_color_;
}

void Triangle::Draw(float exp)
{
	/*DrawTriangle(
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 0 / 3)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 0 / 3)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 2 / 3)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 2 / 3)),
		(int)(pos_.x_ + size_.x_ * exp * sin(PAI * 4 / 3)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 4 / 3)),
		color_, true);*/
}

void Triangle::Draw(float exp, Vector2Flt offset)
{
	/*Vector2Flt pos{ pos_ + offset - size_ * exp * offset / size_ };
	DrawTriangle(
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 0 / 3)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 0 / 3)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 2 / 3)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 2 / 3)),
		(int)(pos.x_ + size_.x_ * exp * sin(PAI * 4 / 3)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 4 / 3)),
		color_, true);*/
}

bool Triangle::IsAlive(void)
{
	return alive_;
}

ShapeType Triangle::GetType(void)
{
	return ShapeType::TRIANGLE;
}

Vector2Flt Triangle::GetPos(void)
{
	return pos_;
}

Vector2Flt Triangle::GetSize(void)
{
	return size_;
}

ShapeType Triangle::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)
{
	float hypot = 0.0f;

	Vector2Flt posT[3] = {
		{ (float)(pos_.x_ + size_.x_ * sin(PAI * 0 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 0 / 3)) },
		{ (float)(pos_.x_ + size_.x_ * sin(PAI * 2 / 3)),(float)(pos_.y_ - size_.y_ * cos(PAI * 2 / 3)) },
		{ (float)(pos_.x_ + size_.x_ * sin(PAI * 4 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 4 / 3)) } };

	Vector2Flt sq_pos[4] = {
		pos,{pos.x_ + size.x_,pos.y_},{pos.x_,pos.y_ + size.y_},{pos.x_ + size.x_,pos.y_ + size.y_}
	};

	Vector2Flt tr_pos[3] = {
		{ (float)(pos.x_ + size.x_ * sin(PAI * 0 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 3)) },
		{ (float)(pos.x_ + size.x_ * sin(PAI * 2 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 3)) },
		{ (float)(pos.x_ + size.x_ * sin(PAI * 4 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 3)) } };

	Vector2Flt diffT = pos - posT[0];
	Vector2Flt diffBL = pos - posT[1];
	Vector2Flt diffBR = pos - posT[2];

	Vector2Flt st_pos[6] = { { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 5)) },
	 { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 5)) },
	 { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 5)) },
	 { (float)(pos.x_ + size.x_ * sin(PAI * 6 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 6 / 5)) },
	 { (float)(pos.x_ + size.x_ * sin(PAI * 8 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 8 / 5)) },
	 { pos.x_, pos.y_ } };

	Vector2Flt tre_pos[3] = {
		 { (float)(pos_.x_ + size_.x_ * sin(PAI * 0 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 0 / 3)) },
		 { (float)(pos_.x_ + size_.x_ * sin(PAI * 2 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 2 / 3)) },
		 { (float)(pos_.x_ + size_.x_ * sin(PAI * 4 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 4 / 3)) }
	};

	Vector2Flt tri_pos[3] = {
		 { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 3)) },
		 { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 3)) },
		 { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 3)) }
	};

	Vector2Flt diff_tre[9] = {
		tri_pos[0] - tre_pos[0],
		tri_pos[0] - tre_pos[1],
		tri_pos[0] - tre_pos[2],
		tri_pos[1] - tre_pos[0],
		tri_pos[1] - tre_pos[1],
		tri_pos[1] - tre_pos[2],
		tri_pos[2] - tre_pos[0],
		tri_pos[2] - tre_pos[1],
		tri_pos[2] - tre_pos[2],
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
		for (int st = 0; st < 4; st++)
		{
			AB = posT[1] - posT[0];
			BP = sq_pos[st] - posT[1];

			BC = posT[2] - posT[1];
			CP = sq_pos[st] - posT[2];

			CA = posT[0] - posT[2];
			AP = sq_pos[st] - posT[0];

			gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
			gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
			gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
			if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
			{
				stop_t_ = 2.0f;
			}
		}
		for (int st = 0; st < 3; st++)
		{
			if (posT[st].x_ > pos.x_ &&
				posT[st].x_ < pos.x_ + size.x_ &&
				posT[st].y_ > pos.y_ &&
				posT[st].y_ < pos.y_ + size.y_)
			{
				stop_t_ = 2.0f;
			}
		}
		break;
	case ShapeType::CIRCLE:
		hypot = hypotf(diffBR.x_, diffBR.y_);
		if (hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		hypot = hypotf(diffT.x_, diffT.y_);
		if (hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		hypot = hypotf(diffBL.x_, diffBL.y_);
		if (hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		break;
	case ShapeType::TRIANGLE:
		for (int st = 0; st < 3; st++)
		{
			AB = posT[1] - posT[0];
			BP = tr_pos[st] - posT[1];

			BC = posT[2] - posT[1];
			CP = tr_pos[st] - posT[2];

			CA = posT[0] - posT[2];
			AP = tr_pos[st] - posT[0];

			gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
			gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
			gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
			if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
			{
				if (size >= size_)
				{
					alive_ = false;
				}
			}
		}
		for (int st = 0; st < 3; st++)
		{
			AB = tr_pos[1] - tr_pos[0];
			BP = posT[st] - tr_pos[1];

			BC = tr_pos[2] - tr_pos[1];
			CP = posT[st] - tr_pos[2];

			CA = tr_pos[0] - tr_pos[2];
			AP = posT[st] - tr_pos[0];

			gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
			gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
			gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
			if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
			{
				if (size >= size_)
				{
					alive_ = false;
				}
			}
		}
		break;
	case ShapeType::STAR:
		for (int st = 0; st < 6; st++)
		{
			AB = posT[1] - posT[0];
			BP = st_pos[st] - posT[1];

			BC = posT[2] - posT[1];
			CP = st_pos[st] - posT[2];

			CA = posT[0] - posT[2];
			AP = st_pos[st] - posT[0];

			gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
			gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
			gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
			if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
			{
				color_ = 0xffffff;
			}
		}
		break;
	case ShapeType::TREFOIL:
		for (int st = 0; st < 3; st++)
		{
			AB = tri_pos[1] - tri_pos[0];
			BP = tre_pos[st] - tri_pos[1];

			BC = tri_pos[2] - tri_pos[1];
			CP = tre_pos[st] - tri_pos[2];

			CA = tri_pos[0] - tri_pos[2];
			AP = tre_pos[st] - tri_pos[0];

			gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
			gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
			gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
			if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
			{
				return ShapeType::TRIANGLE;
			}
		}
		for (int r = 0; r < 9; r++)
		{
			hypot = hypotf(diff_tre[r].x_, diff_tre[r].y_);
			if (hypot <= size.x_)
			{
				color_ = 0x0000ff;
			}
		}
		break;
	case ShapeType::CROSS:
		hypot = hypotf(diffBR.x_, diffBR.y_);
		if (hypot <= size.x_)
		{
			vec_ *= add_speed_;
		}
		hypot = hypotf(diffT.x_, diffT.y_);
		if (hypot <= size.x_)
		{
			vec_ *= add_speed_;
		}
		hypot = hypotf(diffBL.x_, diffBL.y_);
		if (hypot <= size.x_)
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
