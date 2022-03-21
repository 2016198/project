#pragma once
#include <map>
#include <vector>
#include "IntVector3.h"
#include "Transform.h"

class SceneManager;
class ResourceManager;
class Rock;

class RockManager
{
public:

	//1マップ当たりのサイズ
	static constexpr int MAP_SIZE = 2000;

	//1マップ当たりに生成する岩の数
	static constexpr int NUM_CREATE = 30;

	RockManager(SceneManager* manager, Transform* playerTransform);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;

	Transform* mPlayerTransform;

	//マップ管理
	std::map<IntVector3, std::vector<Rock*>> mMapRocks;

	//ランダム生成
	Rock* CreateRandom(IntVector3 mapPos);

};

