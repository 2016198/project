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

	//1�}�b�v������̃T�C�Y
	static constexpr int MAP_SIZE = 2000;

	//1�}�b�v������ɐ��������̐�
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

	//�}�b�v�Ǘ�
	std::map<IntVector3, std::vector<Rock*>> mMapRocks;

	//�����_������
	Rock* CreateRandom(IntVector3 mapPos);

};

