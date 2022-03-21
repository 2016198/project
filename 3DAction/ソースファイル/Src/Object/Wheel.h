#pragma once
#include "Common/Transform.h"

class SceneManager;

class Wheel
{
public:

	//�傫��
	static constexpr float SCALE = 2.0f;

	// �^�C�����[�J���ғ���(deg)
	static constexpr float ANGLE_POW_WHEEL = 0.1f;

	Wheel(SceneManager* manager,
		Transform* transformParent,
		VECTOR localPos,
		VECTOR localAddAxis,
		bool isLeft);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SyncParent(Transform* transform, VECTOR addAxis);

private:

	SceneManager* mSceneManager;

	// ���f������̊�{���(�e)
	Transform* mTransformParent;

	// ���f������̊�{���(�^�C��)
	Transform mTransformWheel;

	// �䂩��̑��΍��W
	VECTOR mLocalPos;

	// �ǉ��̃��[�J����]
	VECTOR mLocalAddAxis;

	// �X�ɒǉ��̃^�C�����[�J����]
	VECTOR mLocalAddAxisWheel;

	// �^�C�����[�J���ғ���(deg)
	float mAnglePowWheel;

	//�^�C���̈ʒu
	int mWheel[2];
};

