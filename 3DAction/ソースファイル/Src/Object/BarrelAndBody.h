#pragma once
#include "Common/Transform.h"

class SceneManager;
class TankShot;

class BarrelAndBody
{
public:

	//�傫��
	static constexpr float SCALE = 2.0f;

	// �C�䃍�[�J���ғ���(deg)
	static constexpr float ANGLE_POW_BARREL = 0.05f;

	// �䃍�[�J���ғ���(deg)
	static constexpr float ANGLE_POW_BODY = 0.05f;


	BarrelAndBody(SceneManager* manager,
		Transform* transformParent,
		VECTOR localPos,
		VECTOR localAddAxis);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SyncParent(Transform* transform, VECTOR addAxis);

private:

	SceneManager* mSceneManager;

	//�e�̊�{���
	std::vector<TankShot*> mTankShots;

	// ���f������̊�{���(�e)
	Transform* mTransformParent;

	// ���f������̊�{���(��)
	Transform mTransformBody;

	// ���f������̊�{���(�C��)
	Transform mTransformBarrel;

	// �䂩��̑��΍��W
	VECTOR mLocalPos;

	// �ǉ��̃��[�J����]
	VECTOR mLocalAddAxis;

	// �X�ɒǉ��̑䃍�[�J����]
	VECTOR mLocalAddAxisBody;

	// �X�ɒǉ��̖C�䃍�[�J����]
	VECTOR mLocalAddAxisBarrel;

	// �䃍�[�J���ғ���(deg)
	float mAnglePowBody;

	// �C�䃍�[�J���ғ���(deg)
	float mAnglePowBarrel;

	void CreateShot(void);
};

