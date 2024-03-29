#include "DxLib.h"
#include <map>
#include <string>
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(void)
{
}

ResourceManager::~ResourceManager(void)
{
	mResourcesMap.clear();
}

void ResourceManager::Init(void)
{

	Resource res;

	// 機体の爆発エフェクト
	res = Resource(Resource::TYPE::IMGS, "Image/ShipExplosion.png", 7, 1, 120, 120);
	mResourcesMap.emplace(SRC::SHIP_EXPLOSION, res);

	// 弾の爆発エフェクト
	res = Resource(Resource::TYPE::IMGS, "Image/ShotExplosion.png", 7, 1, 120, 120);
	mResourcesMap.emplace(SRC::SHOT_EXPLOSION, res);

	// 吹き出し
	res = Resource(Resource::TYPE::IMG, "Image/SpeechBalloon.png");
	mResourcesMap.emplace(SRC::SPEECH_BALLOON, res);


	// 弾
	res = Resource(Resource::TYPE::MODEL, "Model/Shot/Shot.mv1");
	mResourcesMap.emplace(SRC::SHOT_MODEL, res);

	// 砲台
	res = Resource(Resource::TYPE::MODEL, "Model/BossShip/Turret.mv1");
	mResourcesMap.emplace(SRC::TURRET_STAND, res);

	// 砲身
	res = Resource(Resource::TYPE::MODEL, "Model/BossShip/Turret_Gun.mv1");
	mResourcesMap.emplace(SRC::TURRET_GUN, res);

	// 背景岩１
	res = Resource(Resource::TYPE::MODEL, "Model/Rock/Rock21.mv1");
	mResourcesMap.emplace(SRC::ROCK01, res);

	// 背景岩２
	res = Resource(Resource::TYPE::MODEL, "Model/Rock/Rock23.mv1");
	mResourcesMap.emplace(SRC::ROCK02, res);

}

void ResourceManager::Release(void)
{

	for (auto p : mLoadedMap)
	{
		p.second->Release();
		delete p.second;
	}

	mLoadedMap.clear();

}

Resource ResourceManager::Load(SRC src)
{

	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return Resource();
	}
	Resource ret = *res;
	return *res;

}

int ResourceManager::LoadModelDuplicate(SRC src)
{

	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res->mHandleId);
	res->mDuplicateModelIds.push_back(duId);

	return duId;

}

Resource* ResourceManager::_Load(SRC src)
{

	auto lPair = mLoadedMap.find(src);
	if (lPair != mLoadedMap.end())
	{
		return lPair->second;
	}

	auto rPair = mResourcesMap.find(src);
	if (rPair == mResourcesMap.end())
	{
		// 登録されていない
		return nullptr;
	}

	rPair->second.Load();
	
	// 念のためコピーコンストラクタ
	Resource* ret = new Resource(rPair->second);
	mLoadedMap.emplace(src, ret);

	return ret;

}
