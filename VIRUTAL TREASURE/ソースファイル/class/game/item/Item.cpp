#include <DxLib.h>
#include <cmath>
#include "Item.h"
#include "../../scene/GameTwoScene.h"

bool Item::Init(void)
{
	for (int i = 0; i < static_cast<int>(ITEM::MAX) - 1; i++)
	{
		if (image_[i] == -1)
		{
			return false;
		}
	}
	font_ = lpMaterialMng.LoadFontHandle("font/font2.dft");
	info_.useItem = ITEM::NONE;
	info_.selectItem = ITEM::NONE;
	info_.angle = 0.0;
	info_.life = 6.0;
	delta_ = 1.0;
	distance_[0] = 0.0;
	distance_[1] = 0.0;
	info_.search = false;
	candle = CANDLE::NO_USE;
	setMode_ = false;
	drawPos_ = { 0, 0 };

	return true;
}

bool Item::Update(double delta, double angle, Vector2 dis)
{
	distance_[1] = distance_[0];																																
	info_.search = false;
	delta_ = delta / 100.0;
	setMode_ = false;
	int disX;
	int disY;
	if (info_.life > 0.0)
	{
		switch (info_.useItem)	//使ったアイテム
		{
		case ITEM::COMPASS:
			//徐々に回転していく
			if (angle > info_.angle)
			{
				if (info_.angle + delta_ > angle)
				{
					info_.angle = angle;
				}
				else
				{
					info_.angle += delta_;
				}
			}
			else
			{
				if (info_.angle - delta_ < angle)
				{
					info_.angle = angle;
				}
				else
				{
					info_.angle -= delta_;
				}
			}
			break;
		case ITEM::DETECTOR:
			disX = dis.x * dis.x;
			disY = dis.y * dis.y;
			distance_[0] = sqrt(disX + disY) - 50.0;
			if (distance_[0] < 10.0)
			{
				info_.angle += delta_ * 3.0;
				info_.search = true;
			}
			break;
		case ITEM::MAGNET:
			setMode_ = true;
			break;
		case ITEM::CANDLE:
			if (candle == CANDLE::NO_USE)
			{
				//candle = rand() % static_cast<int>(CANDLE::NO_USE);
				candle = CANDLE::ITEM_GET;
			}
			break;
		}
	}

	if (info_.useItem != ITEM::COMPASS && info_.useItem == ITEM::NONE)
	{
		info_.angle = 0.0;
	}
	if (info_.selectItem == ITEM::COMPASS && info_.useItem != ITEM::COMPASS)
	{
		info_.angle = 3.141519 * -0.5;
	}
	if (info_.useItem != ITEM::NONE)
	{
		if (drawPos_ != movePos_)
		{
			Vector2 dis = drawPos_ - movePos_;
			auto diff = sqrt(dis.x * dis.x + dis.y * dis.y);
			double x = static_cast<double>(dis.x) / diff * MOVE;
			double y = static_cast<double>(dis.y) / diff * MOVE;
			movePow_ = { static_cast<int>(x), static_cast<int>(y) };
		}
		else
		{
			movePow_ = { 0, 0 };
		}

		if (info_.life > 0.0)
		{
			info_.life -= delta_ * 30.0;
		}
	}

	if (info_.selectItem == ITEM::NONE)
	{
		info_.life = 255.0;
		candle = CANDLE::NO_USE;
	}
	else
	{
		if (info_.useItem == ITEM::NONE)
		{
			drawPos_ = info_.pos;
		}
	}

	if (abs(drawPos_.x - movePos_.x) > abs(movePow_.x))
	{
		drawPos_.x -= movePow_.x;
	}
	else
	{
		drawPos_.x -= drawPos_.x - movePos_.x;
	}

	if (abs(drawPos_.y - movePos_.y) > abs(movePow_.y))
	{
		drawPos_.y -= movePow_.y;
	}
	else
	{
		drawPos_.y -= drawPos_.y - movePos_.y;
	}

	return true;
}

void Item::Draw(int num)
{
	if (info_.selectItem != ITEM::NONE && info_.life > 0.0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(info_.life));
		DrawRotaGraph(drawPos_.x, drawPos_.y, 0.1, info_.angle, image_[static_cast<int>(info_.selectItem)], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 34);
	}

	if (info_.useItem == ITEM::DETECTOR && info_.life > 0)
	{
		if (info_.search == true)
		{
			DrawExtendStringToHandle(info_.pos.x + 2, info_.pos.y - 18, 2.0, 2.0,"!!!", 0, font_);
			DrawExtendStringToHandle(info_.pos.x, info_.pos.y - 20, 2.0, 2.0,"!!!", 0xffffff, font_);
			if (CheckSoundMem(sound_[num]) == 0)
			{
				PlaySoundMem(sound_[num], DX_PLAYTYPE_BACK);
			}
		}
		else
		{
			DrawExtendStringToHandle(info_.pos.x + 2, info_.pos.y - 18, 2.0, 2.0, "???", 0, font_);
			DrawExtendStringToHandle(info_.pos.x, info_.pos.y - 20, 2.0, 2.0, "???", 0xffffff, font_);
			if (CheckSoundMem(sound_[num]) == 1)
			{
				StopSoundMem(sound_[num]);
			}
		}
	}
	else
	{
		if (CheckSoundMem(sound_[num]) == 1)
		{
			StopSoundMem(sound_[num]);
		}
	}
}

void Item::Release(void)
{
	for (const auto& name : fileName_["image"])
	{
		lpMaterialMng.DeleteGraphHandle(name);
	}

	for (const auto& name : fileName_["sound"])
	{
		lpMaterialMng.DeleteGraphHandle(name);
	}
}

Item::Item()
{
	//メモリの確保
	image_.resize(static_cast<size_t>(ITEM::MAX) - 1U);
	fileName_["image"].resize(static_cast<size_t>(ITEM::MAX) - 1U);
	sound_.resize(3U);
	fileName_["sound"].resize(3U);

	//画像のロード
	std::string file = "image/item/";
	std::string key[static_cast<int>(ITEM::MAX) - 1] =
	{
		"compass.png",
		"detector.png",
		"magnet.png",
		"candle.png"
	};

	for (int q = 0; q < static_cast<int>(ITEM::MAX) - 1; q++)
	{
		image_[q] = lpMaterialMng.LoadGraphHandle((file + key[q]).c_str());
		fileName_["image"][q] = file + key[q];
	}

	//サウンドのロード
	file = "sound/";
	key[0] = "ppppp.wav";
	key[1] = "pppp.wav";
	key[2] = "bee.wav";

	for (int q = 0; q < 3; q++)
	{
		sound_[q] = lpMaterialMng.LoadSoundHandle((file + key[q]).c_str());
		fileName_["sound"][q] = file + key[q];
	}

	Init();
}

Item::~Item()
{

}

void Item::SetInfo(Vector2 pos1, ITEM itemS, ITEM itemU, Vector2 pos2)
{
	info_.pos = pos1;
	info_.selectItem = itemS;
	info_.useItem = itemU;
	movePos_ = pos2;
}

double Item::GetLife(void)
{
	return info_.life;
}
