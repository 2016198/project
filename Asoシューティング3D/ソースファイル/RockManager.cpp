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

	//�Ó]��
	Update();
}

void RockManager::Update(void)
{
	//���v���C���[�̈ʒu�����āA����27�}�X�̃}�b�v������
	//�s�����ǂ������f����

	//�v���C���[�̍��W���}�b�v���W�ɕϊ�
	VECTOR playerGrobalPos = mPlayerTransform->pos;
	
	//KEY(first)
	IntVector3 playerMapPos = playerGrobalPos;
	playerMapPos.x /= MAP_SIZE;
	playerMapPos.y /= MAP_SIZE;
	playerMapPos.z /= MAP_SIZE;

	//�e�X�g�R�[�h
	IntVector3 mapPos = playerMapPos;

	//loop�𐳕����ɓ��ꂷ�邽�߂��炩����-1
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
				//27�̃}�b�v���W
				mapCalcPos.x = mapPos.x + x;
				mapCalcPos.y = mapPos.y + y;
				mapCalcPos.z = mapPos.z + z;

				//���łɐ�������Ă���}�b�v���W���m�F
				if (mMapRocks.count(mapCalcPos) == 0)
				{

					//VALUE(second)
					std::vector<Rock*> rocks;

					for (int i = 0; i < NUM_CREATE; i++)
					{
						//�����_���Ɋ�𐶐�����
						Rock* rock = CreateRandom(mapCalcPos);
						//�⃊�X�g�ɂԂ�����ł�邺
						rocks.push_back(rock);

					}
					//�}�b�v�Ǘ��ɉ�����
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
	//��̃��f���������_���Ɍ��߂�
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

	//�����_���Ȋp�x
	VECTOR angles;
	angles.x = AsoUtility::Deg2RadF(float(GetRand(360)));
	angles.y = AsoUtility::Deg2RadF(float(GetRand(360)));
	angles.z = AsoUtility::Deg2RadF(0.0f);

	//�����_���ȑ傫��
	VECTOR scale;
	int s = GetRand(8) + 4;

	scale.x = float(s);
	scale.y = float(s);
	scale.z = float(s);

	//�ʒu
	VECTOR pos;
	pos.x = mapPos.x * MAP_SIZE;
	pos.y = mapPos.y * MAP_SIZE;
	pos.z = mapPos.z * MAP_SIZE;

	pos.x += float(GetRand(MAP_SIZE) - MAP_SIZE / 2);
	pos.y += float(GetRand(MAP_SIZE) - MAP_SIZE / 2);
	pos.z += float(GetRand(MAP_SIZE) - MAP_SIZE / 2);

	//��𐶐�
	Rock* ret = new Rock();
	ret->Init(id, pos, angles, scale);

	return ret;
}
