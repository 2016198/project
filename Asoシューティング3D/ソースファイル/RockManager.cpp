#include "SceneManager.h"
#include "AsoUtility.h"
#include "ResourceManager.h"
#include "Rock.h"
#include "RockManager.h"

RockManager::RockManager(SceneManager* manager, Transform* playerTransform)
{
	mSceneManager = manager;
	mPlayerTransform = playerTransform;
	mResourceManager = mSceneManager->GetResource();
}

void RockManager::Init(void)
{

	//暗転中
	Update();
}

void RockManager::Update(void)
{
	//●プレイヤーの位置を見て、周囲27マスのマップ生成を
	//行うかどうか判断する

	//プレイヤーの座標をマップ座標に変換
	VECTOR playerGrobalPos = mPlayerTransform->pos;
	
	//KEY(first)
	IntVector3 playerMapPos = playerGrobalPos;
	playerMapPos.x /= MAP_SIZE;
	playerMapPos.y /= MAP_SIZE;
	playerMapPos.z /= MAP_SIZE;

	//テストコード
	IntVector3 mapPos = playerMapPos;

	//loopを正方向に統一するためあらかじめ-1
	mapPos.x -= 1;
	mapPos.y -= 1;
	mapPos.z -= 1;

	IntVector3 mapCalcPos = mapPos;

	int loop = 3;

	for (int x = 0; x < loop; x++)
	{
		for (int y = 0; y < loop; y++)
		{
			for (int z = 0; z < loop; z++)
			{
				//27個のマップ座標
				mapCalcPos.x = mapPos.x + x;
				mapCalcPos.y = mapPos.y + y;
				mapCalcPos.z = mapPos.z + z;

				//すでに生成されているマップ座標か確認
				if (mMapRocks.count(mapCalcPos) == 0)
				{

					//VALUE(second)
					std::vector<Rock*> rocks;

					for (int i = 0; i < NUM_CREATE; i++)
					{
						//ランダムに岩を生成する
						Rock* rock = CreateRandom(mapCalcPos);
						//岩リストにぶち込んでやるぜ
						rocks.push_back(rock);

					}
					//マップ管理に加える
					mMapRocks.emplace(mapCalcPos, rocks);
				}
			}
		}

	}
}

void RockManager::Draw(void)
{
	//for (const std::pair<IntVector3, std::vector<Rock*>> p : mMapRocks)
	for (const auto p : mMapRocks)
	{
		//KEY = IntVector3
		//p.first;
		//VALUE = std::vector<Rock*>
		//p.second;

		for(const auto rock: p.second)
		{
			rock->Draw();
		}
	}
}

void RockManager::Release(void)
{
	//for (const std::pair<IntVector3, std::vector<Rock*>> p : mMapRocks)
	for (auto& p : mMapRocks)
	{
		//KEY = IntVector3
		//p.first;
		//VALUE = std::vector<Rock*>
		//p.second;

		for (auto& rock : p.second)
		{
			rock->Release();
			delete rock;
			rock = nullptr;
		}
		p.second.clear();
	}
	mMapRocks.clear();
}

Rock* RockManager::CreateRandom(IntVector3 mapPos)
{
	//岩のモデルをランダムに決める
	int r = GetRand(1);
	int id = -1;
	switch (r)
	{
	case 0:
		id = mResourceManager->LoadModelDuplicate(
			ResourceManager::SRC::ROCK01);
		break;

	case 1:
		id = mResourceManager->LoadModelDuplicate(
			ResourceManager::SRC::ROCK02);
		break;

	}

	//ランダムな角度
	VECTOR angles;
	angles.x = AsoUtility::Deg2RadF(float(GetRand(360)));
	angles.y = AsoUtility::Deg2RadF(float(GetRand(360)));
	angles.z = AsoUtility::Deg2RadF(0.0f);

	//ランダムな大きさ
	VECTOR scale;
	int s = GetRand(8) + 4;

	scale.x = float(s);
	scale.y = float(s);
	scale.z = float(s);

	//位置
	VECTOR pos;
	pos.x = mapPos.x * MAP_SIZE;
	pos.y = mapPos.y * MAP_SIZE;
	pos.z = mapPos.z * MAP_SIZE;

	pos.x += float(GetRand(MAP_SIZE) - MAP_SIZE / 2);
	pos.y += float(GetRand(MAP_SIZE) - MAP_SIZE / 2);
	pos.z += float(GetRand(MAP_SIZE) - MAP_SIZE / 2);

	//岩を生成
	Rock* ret = new Rock();
	ret->Init(id, pos, angles, scale);

	return ret;
}
