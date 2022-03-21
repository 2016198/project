#include <DxLib.h>
#include <math.h>
#include <cmath>
#include "Square.h"

Square::Square(Vector2Flt&& pos, Vector2Flt&& size, Vector2Flt&& speed, unsigned int color) :
	Shape(pos, size, speed, color)
{
	alive_ = true;
	vec_ = { 1.0f, 1.0f };	
	def_color_ = color;
}

bool Square::UpDate(float delta, Shape& ShapeVec)
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
	/*if (pos_.x_ <= )
	{

	}*/
	/*static float moveSum = 0.0f;
	static float moveAve = 0.0f;
	static float deltaSum = 0.0f;
	static int sec = 0;
	deltaSum += delta;
	if ((int)deltaSum > sec)
	{
		sec = (int)deltaSum;
		moveAve = moveSum / sec;
	}*/
	pos_.x_ += speed_.x_ * delta * 60 * vec_.x_;//à⁄ìÆ
	pos_.y_ += speed_.y_ * delta * 60 * vec_.y_;
	if (pos_.x_ + size_.x_ > SCREEN_SIZE_X)//âÊñ äOÇ…èoÇ»Ç¢
	{
		pos_.x_ = SCREEN_SIZE_X - size_.x_;
		vec_.x_ *= -1;
		color_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
		def_color_ = color_;
	}
	else if(pos_.x_ < 0)
	{
		pos_.x_ = 0;
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
	else if (pos_.y_ < 0)
	{
		pos_.y_ = 0;
		vec_.y_ *= -1;
		color_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
		def_color_ = color_;
	}


	if (vec_.x_ > 1.0f)//ç≈í·ë¨ìxÇÃê›íË
	{
		vec_.x_ -= 0.05f;
	}
	else if(vec_.x_ < -1.0f)
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
	/*moveSum += speed_.x_ * delta * 60;
	DrawFormatString(0, 0, 0xff1111, "à⁄ìÆó :%f", moveSum);
	DrawFormatString(0, 0, 0xff1111, "\nïΩãœà⁄ìÆó :%f", moveAve);
	DrawFormatString(0, 0, 0xff1111, "\n\nåoâﬂéûä‘:%f", deltaSum);*/
	return false;
}

bool Square::IsAlive(void)
{
	return alive_;
}

void Square::Draw(void)
{
	DrawBox((int)(pos_.x_),
			(int)(pos_.y_),
			(int)(pos_.x_ + size_.x_),
			(int)(pos_.y_ + size_.y_),
			color_,
			true);
	color_ = def_color_;
}

void Square::Draw(float exp)
{
	DrawBox((int)(pos_.x_),
			(int)(pos_.y_),
			(int)(pos_.x_) + (int)(size_.x_ * exp),
			(int)(pos_.y_) + (int)(size_.y_ * exp),
			color_,
			true);
}

void Square::Draw(float exp, Vector2Flt offset)
{
	Vector2Flt pos{ pos_ + offset - size_ * exp * offset / size_ };

	DrawBox(
		(int)(pos.x_),
		(int)(pos.y_),
		(int)(pos.x_ + (size_.x_ * exp)),
		(int)(pos.y_ + (size_.y_ * exp)),
		color_,
		true);
}

ShapeType Square::GetType(void)
{
	return ShapeType::SQUARE;
}

Vector2Flt Square::GetPos(void)
{
	return pos_;
}

Vector2Flt Square::GetSize(void)
{
	return size_;
}

ShapeType Square::Collsion(Vector2Flt pos, Vector2Flt size, ShapeType type)//Ç†ÇΩÇËÇÕÇÒÇƒÇ¢
{
	float hypot = 0.0f;
	Vector2Flt diffTL = pos_ - pos;
	Vector2Flt diffBR = pos_ + size_ - pos;
	Vector2Flt half_size;
	half_size.x_ = size_.x_ / 2;
	half_size.y_ = size_.y_ / 2;

	Vector2Flt st_diffT = { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 5)) };
	Vector2Flt st_diffR = { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 5)) };
	Vector2Flt st_diffBR = { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 5)) };
	Vector2Flt st_diffBL = { (float)(pos.x_ + size.x_ * sin(PAI * 6 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 6 / 5)) };
	Vector2Flt st_diffL = { (float)(pos.x_ + size.x_ * sin(PAI * 8 / 5)), (float)(pos.y_ - size.y_ * cos(PAI * 8 / 5)) };

	Vector2Flt tri_diffT = { (float)(pos.x_ + size.x_ * sin(PAI * 0 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 0 / 3)) };
	Vector2Flt tri_diffBR = { (float)(pos.x_ + size.x_ * sin(PAI * 2 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 2 / 3)) };
	Vector2Flt tri_diffBL = { (float)(pos.x_ + size.x_ * sin(PAI * 4 / 3)), (float)(pos.y_ - size.y_ * cos(PAI * 4 / 3)) };

	Vector2Flt tre_diff[12] = {
		tri_diffT - pos_,
		tri_diffBL - pos_,
		tri_diffBR - pos_,
		{tri_diffT.x_ - (pos_.x_ + size_.x_),tri_diffT.y_ - pos_.y_},
		{tri_diffBL.x_ - (pos_.x_ + size_.x_),tri_diffBL.y_ - pos_.y_},
		{tri_diffBR.x_ - (pos_.x_ + size_.x_),tri_diffBR.y_ - pos_.y_},
		{tri_diffT.x_ - pos_.x_,tri_diffT.y_ - (pos_.y_ + size_.y_)},
		{tri_diffBL.x_ - pos_.x_,tri_diffBL.y_ - (pos_.y_ + size_.y_)},
		{tri_diffBR.x_ - pos_.x_,tri_diffBR.y_ - (pos_.y_ + size_.y_)},
		tri_diffT - (pos_ + size_),
		tri_diffBL - (pos_ + size_),
		tri_diffBR - (pos_ + size_)
	};

	//ÉxÉNÉgÉãåvéZ
	Vector2Flt AB = tri_diffBL - tri_diffT;
	Vector2Flt BP = pos_ - tri_diffBL;

	Vector2Flt BC = tri_diffBR - tri_diffBL;
	Vector2Flt CP = pos_ - tri_diffBR;

	Vector2Flt CA = tri_diffT - tri_diffBR;
	Vector2Flt AP = pos_ - tri_diffT;
	//äOêœÇÃåvéZZÇæÇØÇåvéZÇ∑ÇÈ
	float gai[3] = { 0.0f,0.0f, 0.0f };

	switch (type)
	{
	case ShapeType::SQUARE:
		break;
	case ShapeType::CIRCLE:
		//â~ÇÃí[Ç¡Ç±Ç™éläpÇÃäpÇ…êGÇÍÇΩÇÁ
		hypot = hypotf(diffTL.x_, diffTL.y_);
		if ((int)hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		hypot = hypotf(diffTL.x_, diffBR.y_);
		if ((int)hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		hypot = hypotf(diffBR.x_, diffTL.y_);
		if ((int)hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		hypot = hypotf(diffBR.x_, diffBR.y_);
		if ((int)hypot <= size.x_)
		{
			color_ = 0x111111;
		}
		//â~ÇÃç∂Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos.x_ - size.x_ > pos_.x_ &&
			pos.x_ - size.x_< pos_.x_ + size_.x_ &&
			pos.y_ > pos_.y_ &&
			pos.y_ < pos_.y_ + size_.y_)
		{
			color_ = 0x111111;
		}
		//â~ÇÃâEÇ™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos.x_ + size.x_ > pos_.x_ &&
			pos.x_ + size.x_< pos_.x_ + size_.x_ &&
			pos.y_ > pos_.y_ &&
			pos.y_ < pos_.y_ + size_.y_)
		{
			color_ = 0x111111;
		}
		//â~ÇÃè„Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos.x_ > pos_.x_ &&
			pos.x_ < pos_.x_ + size_.x_ &&
			pos.y_ - size.x_> pos_.y_ &&
			pos.y_ - size.x_ < pos_.y_ + size_.y_)
		{
			color_ = 0x111111;
		}
		//â~ÇÃâ∫Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (pos.x_ > pos_.x_ &&
			pos.x_< pos_.x_ + size_.x_ &&
			pos.y_ + size.x_ > pos_.y_ &&
			pos.y_ + size.x_ < pos_.y_ + size_.y_)
		{
			color_ = 0x111111;
		}
		break;
	case ShapeType::TRIANGLE:
		//éOäpÇÃè„Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (tri_diffT.x_ > pos_.x_ &&
			tri_diffT.x_ < pos_.x_ + size_.x_ &&
			tri_diffT.y_ > pos_.y_ &&
			tri_diffT.y_ < pos_.y_ + size_.y_)
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		//éOäpÇÃâEâ∫Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (tri_diffBR.x_ > pos_.x_ &&
			tri_diffBR.x_ < pos_.x_ + size_.x_ &&
			tri_diffBR.y_ > pos_.y_ &&
			tri_diffBR.y_ < pos_.y_ + size_.y_)
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		//éOäpÇÃç∂â∫Ç™éläpÇÃíÜÇ…ì¸Ç¡ÇΩÇÁ
		if (tri_diffBL.x_ > pos_.x_ &&
			tri_diffBL.x_ < pos_.x_ + size_.x_ &&
			tri_diffBL.y_ > pos_.y_ &&
			tri_diffBL.y_ < pos_.y_ + size_.y_)
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		//äOêœÇÃåvéZ
		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		//ç∂è„
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		//âEè„
		BP.x_ = pos_.x_ + size_.x_ - tri_diffBL.x_;
		BP.y_ = pos_.y_ - tri_diffBL.y_;
		CP.x_ = pos_.x_ + size_.x_ - tri_diffBR.x_;
		CP.y_ = pos_.y_ - tri_diffBR.y_;
		AP.x_ = pos_.x_ + size_.x_ - tri_diffT.x_;
		AP.y_ = pos_.y_ - tri_diffT.y_;
		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}

		//ç∂â∫
		BP.x_ = pos_.x_ - tri_diffBL.x_;
		BP.y_ = pos_.y_ + size_.y_ - tri_diffBL.y_;
		CP.x_ = pos_.x_ - tri_diffBR.x_;
		CP.y_ = pos_.y_ + size_.y_ - tri_diffBR.y_;
		AP.x_ = pos_.x_ - tri_diffT.x_;
		AP.y_ = pos_.y_ + size_.y_ - tri_diffT.y_;
		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}

		//âEâ∫
		BP = pos_ + size_ - tri_diffBL;
		CP = pos_ + size_ - tri_diffBR;
		AP = pos_ + size_ - tri_diffT;
		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		//ê^ÇÒíÜ
		BP = pos_ + half_size - tri_diffBL;
		CP = pos_ + half_size - tri_diffBR;
		AP = pos_ + half_size - tri_diffT;
		gai[0] = AB.x_ * BP.y_ - AB.y_ * BP.x_;
		gai[1] = BC.x_ * CP.y_ - BC.y_ * CP.x_;
		gai[2] = CA.x_ * AP.y_ - CA.y_ * AP.x_;
		if ((gai[0] > 0 && gai[1] > 0 && gai[2] > 0) || (gai[0] < 0 && gai[1] < 0 && gai[2] < 0))
		{
			color_ = 0xff0000;
			return ShapeType::TRIANGLE;
		}
		break;
	case ShapeType::STAR:
		if (pos_.x_ <= st_diffT.x_ &&
			pos_.x_ + size_.x_ >= st_diffT.x_ &&
			pos_.y_ <= st_diffT.y_ &&
			pos_.y_ + size_.y_ >= st_diffT.y_)
		{
			color_ = 0xffffff;
		}
		if (pos_.x_ <= st_diffBL.x_ &&
			pos_.x_ + size_.x_ >= st_diffBL.x_ &&
			pos_.y_ <= st_diffBL.y_ &&
			pos_.y_ + size_.y_ >= st_diffBL.y_)
		{
			color_ = 0xffffff;
		}
		if (pos_.x_ <= st_diffBR.x_ &&
			pos_.x_ + size_.x_ >= st_diffBR.x_ &&
			pos_.y_ <= st_diffBR.y_ &&
			pos_.y_ + size_.y_ >= st_diffBR.y_)
		{
			color_ = 0xffffff;
		}
		if (pos_.x_ <= st_diffL.x_ &&
			pos_.x_ + size_.x_ >= st_diffL.x_ &&
			pos_.y_ <= st_diffL.y_ &&
			pos_.y_ + size_.y_ >= st_diffL.y_)
		{
			color_ = 0xffffff;
		}
		if (pos_.x_ <= st_diffR.x_ &&
			pos_.x_ + size_.x_ >= st_diffR.x_ &&
			pos_.y_ <= st_diffR.y_ &&
			pos_.y_ + size_.y_ >= st_diffR.y_)
		{
			color_ = 0xffffff;
		}
		break;
	case ShapeType::TREFOIL:
		for (int e = 0; e < 12; e++)
		{
			hypot = hypotf(tre_diff[e].x_, tre_diff[e].y_);
			if ((int)hypot <= size.x_)
			{
				color_ = 0x0000ff;
			}
		}
		break;
	case ShapeType::CROSS:
		hypot = hypotf(diffTL.x_, diffTL.y_);
		if ((int)hypot <= size.x_)
		{
			vec_ *= add_speed_;
		}
		hypot = hypotf(diffTL.x_, diffBR.y_);
		if ((int)hypot <= size.x_)
		{
			vec_ *= add_speed_;
		}
		hypot = hypotf(diffBR.x_, diffTL.y_);
		if ((int)hypot <= size.x_)
		{
			vec_ *= add_speed_;
		}
		hypot = hypotf(diffBR.x_, diffBR.y_);
		if ((int)hypot <= size.x_)
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
