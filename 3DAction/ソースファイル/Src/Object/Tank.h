#pragma once

#include <DxLib.h>
#include <vector>
#include "Common/Transform.h"
#include "Stage.h"

class SceneManager;
class GravityManager;
class Collider;
class Wheel;
class BarrelAndBody;

class Tank
{

public:

	//�X�s�[�h
	static constexpr float SPEED_MOVE = 5.0f;

	//��]��
	static constexpr double ROT_DEG = 1.0f;

	Tank(SceneManager* manager);
	void Init(void);
	void Update(void);
	void UpdatePlay(void);
	void Draw(void);
	void DrawDebug(void);
	void Release(void);

	//����
	void ProcessMove(void);

	//�d��
	void CalcGravityPow(void);

	Transform* GetTransform(void);

	//�Փ˔���ɗp������R���C�_����
	void AddCollider(Collider* collider);
	void ClearCollider(void);

private:

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	//�ړ��X�s�[�h
	float mSpeed;

	//�ړ���
	VECTOR mMovePow;

	//�ړ���̍��W
	VECTOR mMovedPos;

	//�d�͕����x�N�g��
	VECTOR mGravityPow;

	//�Փ˔���ɗp������R���C�_
	std::vector<Collider*> mColliders;

	//�Փ˃`�F�b�N
	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	//�^�C���̏��
	std::vector<Wheel*> mWheels;

	//��ƖC��̏��
	BarrelAndBody* mBarrelAndBody;

	//�Փ˔���
	void Collision(void);
	void CollisionGravity(void);

	//�^�C���̐���
	void MakeWhlle(VECTOR localPos, VECTOR localAddAxis, bool isLeft);

	//�^�C���̍X�V
	void UpdateWhlle(void);

	//�^�C���̕`��
	void DrawWhlle(void);

	//��ƖC��̐���
	void MakeBarrelAndBody(VECTOR localPos, VECTOR localAddAxis);

	//��ƖC��̍X�V
	void UpdateBarrelAndBody(void);

	//��ƖC��̕`��
	void DrawBarrelAndBody(void);
};


