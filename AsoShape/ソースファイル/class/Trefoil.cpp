#include <DxLib.h>
#include <math.h>
#include "Trefoil.h"

Trefoil::Trefoil(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	alive_ = true;
	vec_ = { 1.0f, 1.0f };
	def_color_ = color;
}

void Trefoil::Draw(void)
{
	DrawCircle((int)(pos_.x_ + size_.x_ * sin(PAI * 0 / 3)), (int)(pos_.y_ - size_.y_ * cos(PAI * 0 / 3)), (int)size_.x_, color_);
	DrawCircle((int)(pos_.x_ + size_.x_ * sin(PAI * 2 / 3)), (int)(pos_.y_ - size_.y_ * cos(PAI * 2 / 3)), (int)size_.x_, color_);
	DrawCircle((int)(pos_.x_ + size_.x_ * sin(PAI * 4 / 3)), (int)(pos_.y_ - size_.y_ * cos(PAI * 4 / 3)), (int)size_.x_, color_);
	DrawCircle((int)pos_.x_, (int)pos_.y_, (int)(size_.x_ / 3), 0xff5555);
	color_ = def_color_;
}

void Trefoil::Draw(float exp)
{
	/*DrawCircle((int)(pos_.x_ + size_.x_ * exp * sin(PAI * 0 / 3)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 0 / 3)), (int)(size_.x_ * exp), color_);
	DrawCircle((int)(pos_.x_ + size_.x_ * exp * sin(PAI * 2 / 3)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 2 / 3)), (int)(size_.x_ * exp), color_);
	DrawCircle((int)(pos_.x_ + size_.x_ * exp * sin(PAI * 4 / 3)), (int)(pos_.y_ - size_.y_ * exp * cos(PAI * 4 / 3)), (int)(size_.x_ * exp), color_);*/
}

void Trefoil::Draw(float exp, Vector2Flt offset)
{
	//Vector2Flt pos{ pos_ + offset - size_ * exp * offset / size_ };
	//DrawCircle((int)(pos.x_ + size_.x_ * exp * sin(PAI * 0 / 3)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 0 / 3)), (int)(size_.x_ * exp), color_);
	//DrawCircle((int)(pos.x_ + size_.x_ * exp * sin(PAI * 2 / 3)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 2 / 3)), (int)(size_.x_ * exp), color_);
	//DrawCircle((int)(pos.x_ + size_.x_ * exp * sin(PAI * 4 / 3)), (int)(pos.y_ - size_.y_ * exp * cos(PAI * 4 / 3)), (int)(size_.x_ * exp), color_);
}

bool Trefoil::UpDate(float delta, Shape& ShapeVec)
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
		pos_.x_ += speed_.x_ * delta * 60 * vec_.x_;
		pos_.y_ += speed_.y_ * delta * 60 * vec_.y_;
	}
	Vector2Flt posT = { (float)(pos_.x_ + size_.x_ * sin(PAI * 0 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 0 / 3)) };
	Vector2Flt posBR = { (float)(pos_.x_ + size_.x_ * sin(PAI * 2 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 2 / 3)) };
	Vector2Flt posBL = { (float)(pos_.x_ + size_.x_ * sin(PAI * 4 / 3)), (float)(pos_.y_ - size_.y_ * cos(PAI * 4 / 3)) };
	if (posT.y_ < size_.x_)//ìñÇΩÇËîªíË(è„)
	{
		vec_.y_ *= -1;
		pos_.y_ = -size_.y_ * (float)(cos(PAI * 2 / 2)) + size_.y_;
		return true;
	}
	if (posBL.y_ > SCREEN_SIZE_Y - size_.x_)//ìñÇΩÇËîªíË(â∫)
	{
		vec_.y_ *= -1;
		pos_.y_ = SCREEN_SIZE_Y + size_.y_ * (float)(cos(PAI * 2 / 3)) - size_.y_;
		return true;
	}
	if (posBL.x_ < size_.x_)//ìñÇΩÇËîªíË(ç∂)
	{
		vec_.x_ *= -1;
		pos_.x_ = -size_.x_ * (float)(sin(PAI * 4 / 3)) + size_.x_;
		return true;
	}
	if (posBR.x_ > SCREEN_SIZE_X - size_.x_)//ìñÇΩÇËîªíË(âE)
	{
		vec_.x_ *= -1;
		pos_.x_ = SCREEN_SIZE_X - (-size_.x_ * (float)(sin(PAI * 4 / 3)) + size_.x_);
		return true;
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

bool Trefoil::IsAlive(void)
{
	return alive_;
}

ShapeType  Trefoil::GetType(void)
{
	return ShapeType::TREFOIL;
}

Vector2Flt Trefoil::GetPos(void)
{
	return pos_;
}

Vector2Flt Trefoil::GetSize(void)
{
	return size_;
}

ShapeType Trefoil::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)
{
	Vector2Flt sq_pos[4] = {
		pos,
		{pos.x_ + size.x_,pos.y_},
		{pos.x_ ,pos.y_ + size.y_},
		{pos.x_ + size.x_,pos.y_ + size.y_},
	};

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

	Vector2Flt st_pos[5] = {
		 { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 5)) },
		 { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 5)) },
		 { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 5)) },
		 { (float)(pos.x_ + size.x_ * sin(PAI * 6 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 6 / 5)) },
		 { (float)(pos.x_ + size.x_ * sin(PAI * 8 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 8 / 5)) },
	};

	Vector2Flt diff_sq[12] = {
		tre_pos[0] - sq_pos[0],
		tre_pos[0] - sq_pos[1],
		tre_pos[0] - sq_pos[2],
		tre_pos[0] - sq_pos[3],
		tre_pos[1] - sq_pos[0],
		tre_pos[1] - sq_pos[1],
		tre_pos[1] - sq_pos[2],
		tre_pos[1] - sq_pos[3],
		tre_pos[2] - sq_pos[0],
		tre_pos[2] - sq_pos[1],
		tre_pos[2] - sq_pos[2],
		tre_pos[2] - sq_pos[3],
	};

	Vector2Flt diff_tri[9] = {
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

	Vector2Flt diff_st[15] = {
		tre_pos[0] - st_pos[0],
		tre_pos[0] - st_pos[1],
		tre_pos[0] - st_pos[2],
		tre_pos[0] - st_pos[3],
		tre_pos[0] - st_pos[4],
		tre_pos[1] - st_pos[0],
		tre_pos[1] - st_pos[1],
		tre_pos[1] - st_pos[2],
		tre_pos[1] - st_pos[3],
		tre_pos[1] - st_pos[4],
		tre_pos[2] - st_pos[0],
		tre_pos[2] - st_pos[1],
		tre_pos[2] - st_pos[2],
		tre_pos[2] - st_pos[3],
		tre_pos[2] - st_pos[4],
	};

	Vector2Flt diff_cr[3]{
		tre_pos[0] - pos,
		tre_pos[1] - pos,
		tre_pos[2] - pos
	};


	//ÉxÉNÉgÉãç∑ï™ïœêî
	Vector2Flt AB = { 0.0f,0.0f };
	Vector2Flt BP = { 0.0f,0.0f };

	Vector2Flt BC = { 0.0f,0.0f };
	Vector2Flt CP = { 0.0f,0.0f };

	Vector2Flt CA = { 0.0f,0.0f };
	Vector2Flt AP = { 0.0f,0.0f };

	//äOêœÇÃåvéZZÇæÇØÇåvéZÇ∑ÇÈ
	float gai[3] = { 0.0f,0.0f, 0.0f };
	float hypot = 0.0f;

	switch (type)
	{
	case ShapeType::SQUARE:
		for (int e = 0; e < 3; e++)
		{
			//â~ÇÃç∂Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
			if (tre_pos[e].x_ - size_.x_ > pos.x_ &&
				tre_pos[e].x_ - size_.x_< pos.x_ + size.x_ &&
				tre_pos[e].y_ > pos.y_ &&
				tre_pos[e].y_ < pos.y_ + size.y_)
			{
				stop_t_ = 2.0f;
			}
			//â~ÇÃâEÇ™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
			if (tre_pos[e].x_ + size_.x_ > pos.x_ &&
				tre_pos[e].x_ + size_.x_< pos.x_ + size.x_ &&
				tre_pos[e].y_ > pos.y_ &&
				tre_pos[e].y_ < pos.y_ + size.y_)
			{
				stop_t_ = 2.0f;
			}
			//â~ÇÃè„Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
			if (tre_pos[e].x_ > pos.x_ &&
				tre_pos[e].x_ < pos.x_ + size.x_ &&
				tre_pos[e].y_ - size_.x_> pos.y_ &&
				tre_pos[e].y_ - size_.x_ < pos.y_ + size.y_)
			{
				stop_t_ = 2.0f;
			}
			//â~ÇÃâ∫Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
			if (tre_pos[e].x_ > pos.x_ &&
				tre_pos[e].x_< pos.x_ + size.x_ &&
				tre_pos[e].y_ + size_.x_ > pos.y_ &&
				tre_pos[e].y_ + size_.x_ < pos.y_ + size.y_)
			{
				stop_t_ = 2.0f;
			}
		}
		for (int q = 0; q < 12; q++)
		{
			hypot = hypotf(diff_sq[q].x_, diff_sq[q].y_);
			if ((int)hypot <= size_.x_)
			{
				stop_t_ = 2.0f;
			}
		}
		break;
	case ShapeType::CIRCLE:
		for (int e = 0; e < 3; e++)
		{
			hypot = hypotf(diff_cr[e].x_, diff_cr[e].y_);
			if (hypot <= size_.x_ + size.x_)
			{
				color_ = 0x111111;
			}
		}
		break;
	case ShapeType::TRIANGLE:
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
				color_ = 0xff0000;
				return ShapeType::TRIANGLE;
			}
		}
		for (int r = 0; r < 9; r++)
		{
			hypot = hypotf(diff_tri[r].x_, diff_tri[r].y_);
			if (hypot <= size_.x_)
			{
				color_ = 0xff0000;
				return ShapeType::TRIANGLE;
			}
		}
		break;
	case ShapeType::STAR:
		for (int r = 0; r < 15; r++)
		{
			hypot = hypotf(diff_st[r].x_, diff_st[r].y_);
			if (hypot <= size_.x_)
			{
				color_ = 0xffffff;
			}
		}
		AB = tre_pos[1] - tre_pos[0];
		BP = pos - tre_pos[1];

		BC = tre_pos[2] - tre_pos[1];
		CP = pos - tre_pos[2];

		CA = tre_pos[0] - tre_pos[2];
		AP = pos - tre_pos[0];

		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0xffffff;
		}
		break;
	case ShapeType::TREFOIL:
		break;
	case ShapeType::CROSS:
		for (int e = 0; e < 3; e++)
		{
			hypot = hypotf(diff_cr[e].x_, diff_cr[e].y_);
			if (hypot <= size_.x_ + size.x_)
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
