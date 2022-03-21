#include <DxLib.h>
#include "MaterialManager.h"

const int& MaterialManager::LoadScreenic(std::string key, int sizeX, int sizeY)
{
	if (map_.count(key) == 0)
	{
		map_[key].resize(1);
		map_[key][0] = MakeScreen(sizeX, sizeY, true);
	}
	return map_[key][0];
}

const int& MaterialManager::LoadGraphHandle(std::string key)
{
	if (map_.count(key) == 0)
	{
		map_[key].resize(1);
		map_[key][0] = LoadGraph(key.c_str());
	}
	return map_[key][0];
}

const int& MaterialManager::LoadSoundHandle(std::string key)
{
	if (map_.count(key) == 0)
	{
		map_[key].resize(1);
		map_[key][0] = LoadSoundMem(key.c_str());
	}
	return map_[key][0];
}

const int& MaterialManager::LoadFontHandle(std::string key)
{
	if (map_.count(key) == 0)
	{
		map_[key].resize(1);
		map_[key][0] = LoadFontDataToHandle(key.c_str());
	}
	return map_[key][0];
}

const VecInt& MaterialManager::LoadDivGraphic(std::string key, Vector2 count)
{
	if (map_.count(key) == 0)
	{
		map_[key].resize(static_cast<size_t>(count.x) * static_cast<size_t>(count.y));
		int x, y, image;
		image = LoadGraph(key.c_str());
		GetGraphSize(image, &x, &y);
		DeleteGraph(image);
		x /= count.x;
		y /= count.y;
		LoadDivGraph(key.c_str(), count.x * count.y, count.x, count.y, x, y, &map_[key][0]);
	}
	return map_[key];
}

void MaterialManager::DeleteGraphHandle(std::string key)
{
	if (map_.count(key) != 0)
	{
		for (const int map : map_[key])
		{
			DeleteGraph(map);
		}
		map_.erase(key);
	}
}

void MaterialManager::DeleteSoundHandle(std::string key)
{
	if (map_.count(key) != 0)
	{
		DeleteSoundMem(map_[key][0]);
		map_.erase(key);
	}
}

void MaterialManager::DeleteFontHandle(std::string key)
{
	if (map_.count(key) != 0)
	{
		DeleteFontToHandle(map_[key][0]);
		map_.erase(key);
	}
}

