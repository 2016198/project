#include <DxLib.h>
#include "../Color3.h"
#include "../manager/MaterialManager.h"
#include "Map.h"

bool Map::Init(int point1, int point2)
{
	map_.resize(2U);
	map_[0] = point1;
	map_[1] = point2;
	color_ = BROWN.GetColorCode();

	/*for (const auto& i : image_)
	{
		if (i == -1)
		{
			return false;
		}
	}*/

	return true;
}

void Map::Draw(int point1, int point2)
{
	map_[0] = point1;
	map_[1] = point2;
	for (int z = 0; z < POINT_SIZE; z++)
	{
		/*if (map_[0] == z)
		{
			color_ = 0x0000ff;
		}
		else
		{
			if (map_[1] == z)
			{
				color_ = 0xff0000;
			}
			else
			{
				color_ = 0xffffff;
			}
		}*/

		drawPos_.x = OFFSET_X + ((z % POINT_COUNT) * OFFSET_SIZE);
		drawPos_.y = OFFSET_Y + ((z / POINT_COUNT) * OFFSET_SIZE);

		DrawBox(
			drawPos_.x,
			drawPos_.y,
			drawPos_.x + POINT_SIZE,
			drawPos_.y + POINT_SIZE,
			color_, true);

		drawPos_.x = (OFFSET_X - POINT_SIZE) + ((z % POINT_COUNT) * OFFSET_SIZE);
		drawPos_.y = (OFFSET_Y - POINT_SIZE) + ((z / POINT_COUNT) * OFFSET_SIZE);

		DrawBox(
			drawPos_.x,
			drawPos_.y,
			drawPos_.x + OFFSET_SIZE,
			drawPos_.y + OFFSET_SIZE,
			color_, false);

		/*DrawExtendGraph(
			DrawPos_.x,
			DrawPos_.y,
			DrawPos_.x + offset_size,
			DrawPos_.y + offset_size,
			image_[z], true);*/
	}
}

bool Map::Init(int point)
{
	map_.resize(1U);
	map_[0] = point;
	color_ = BROWN.GetColorCode();

	/*for (const auto& i : image_)
	{
		if (i == -1)
		{
			return false;
		}
	}*/

	return true;
}

void Map::Draw(int point)
{
	map_[0] = point;
	for (int z = 0; z < POINT_SIZE; z++)
	{
		/*if (map_[0] == z)
		{
			color_ = 0xff00ff;
		}
		else
		{
			color_ = 0xffffff;
		}*/

		drawPos_.x = OFFSET_X + ((z % POINT_COUNT) * OFFSET_SIZE);
		drawPos_.y = OFFSET_Y + ((z / POINT_COUNT) * OFFSET_SIZE);

		DrawBox(
			drawPos_.x,
			drawPos_.y,
			drawPos_.x + POINT_SIZE,
			drawPos_.y + POINT_SIZE,
			color_, true);

		drawPos_.x = (OFFSET_X - POINT_SIZE) + ((z % POINT_COUNT) * OFFSET_SIZE);
		drawPos_.y = (OFFSET_Y - POINT_SIZE) + ((z / POINT_COUNT) * OFFSET_SIZE);

		DrawBox(
			drawPos_.x,
			drawPos_.y,
			drawPos_.x + OFFSET_SIZE,
			drawPos_.y + OFFSET_SIZE,
			color_, false);

		/*DrawExtendGraph(
			DrawPos_.x,
			DrawPos_.y,
			DrawPos_.x + offset_size,
			DrawPos_.y + offset_size,
			image_[z], true);*/
	}
}

void Map::Release(void)
{
	/*for (const auto& name: fileNameG_)
	{
		lpMaterialMng.DeleteGraphic(name);
	}*/
}

void Map::SetMap(int map, int num)
{
	map_[num] = map;
}

Map::Map()
{
	std::string folderName = "image/free/";
	std::string fileName[POINT_SIZE] = {
		"airport.png",
		"warehouse.png",
		"bench.png",
		"car.png",
		"chest.png",
		"park.png",
		"toilet.png",
		"water.png",
		"woodhouse.png",
		"door.png",
		"cave.png",
		"desert.png",
		"forest.png",
		"green.png",
		"house1.png",
		"house2.png",
		"orange.png",
		"statue.png",
		"yellow.png",
		"ship.png",
		"ocean.png",
		"purple.png",
		"blue.png",
		"red.png",
		"planet.png",
	};
	for (int n = 0; n < POINT_SIZE; n++)
	{
		fileNameG_[n] = folderName + fileName[n];
		//image_[n] = lpMaterialMng.LoadGraphic(fileNameG_[n].c_str());
	}
}

Map::~Map()
{

}
