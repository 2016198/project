#include <DxLib.h>
#include "GameCommon.h"
#include "SceneManager.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Transform.h"
#include "SpriteAnimator.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Turret.h"
#include "TurretShot.h"

Turret::Turret(SceneManager* manager,
	Transform* transformPlayer,
	Transform* transformParent,
	VECTOR localPos,
	VECTOR localAddAxis)
{

	mSceneManager = manager;
	mTransformPlayer = transformPlayer;

	mTransformParent = transformParent;
	mLocalPos = localPos;
	mLocalAddAxis = localAddAxis;

	ResourceManager* rem = mSceneManager->GetResource();

	mTransformStand.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_STAND));
	mTransformGun.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_GUN));

	mExplosion = new SpriteAnimator(
		mSceneManager, ResourceManager::SRC::SHIP_EXPLOSION, 120, 8.0f);

	mStepDamaged = -1;

	mDelayShot = 1.0f;

	// �C�g���[�J����]
	mLocalAddAxisGun = { 0.0f, 0.0f, 0.0f };

	ChangeState(STATE::ATTACK);

}

void Turret::Init(void)
{

	Quaternion localRot;
	Quaternion axis;

	// ���f������̊�{���(�C��)
	mTransformStand.scl = { SCALE, SCALE, SCALE };
	mTransformStand.quaRot = Quaternion();

	// ���[�J����]
	mTransformStand.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// �e���f���Ɠ���
	SyncParent(&mTransformStand, { 0, 0, 0 });



	// ���f������̊�{���(�C�g)
	mTransformGun.scl = { SCALE, SCALE, SCALE };
	mTransformGun.quaRot = Quaternion();

	// ���[�J����]
	mTransformGun.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(-5.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// �e���f���Ɠ���
	SyncParent(&mTransformGun, { 0.0f, 0.0f, 0.0f });

	// �ϋv��
	mHp = 2;

	// �C�䃍�[�J���ғ���(deg)
	mAnglePowStand = ANGLE_POW_STAND;

	// �C�g���[�J���ғ���(deg)
	mAnglePowGun = ANGLE_POW_GUN;

}

void Turret::Update(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
	{

		float deg;

		// �C�䃍�[�J����]

		// �C��
		//������Y����](mLocalAddAxisStand)
		mLocalAddAxisStand.y += (mAnglePowStand * mSceneManager->GetDeltaTime());
		deg = AsoUtility::Rad2DegF(mLocalAddAxisStand.y);
		if (deg < ANGLE_Y_MIN_STAND || deg > ANGLE_Y_MAX_STAND)
		{
			mAnglePowStand *= -1.0f;
		}
		SyncParent(&mTransformStand, mLocalAddAxisStand);

		// �C�g���[�J����]
		
		// �C�g
		mLocalAddAxisGun.x += (mAnglePowGun * mSceneManager->GetDeltaTime());
		deg = AsoUtility::Rad2DegF(mLocalAddAxisGun.x);
		if (deg < ANGLE_X_MIN_GUN || deg > ANGLE_X_MAX_GUN)
		{
			mAnglePowGun *= -1.0f;
		}
		SyncParent(&mTransformGun, mLocalAddAxisGun);

		Quaternion stand = Quaternion::Euler(mLocalAddAxisStand);
		Quaternion gun = Quaternion::Euler(mLocalAddAxisGun);
		Quaternion mix;
		mix = stand.Mult(gun);
		SyncParent(&mTransformGun, mix.ToEuler());

		// ��_������
		if (mStepDamaged > 0.0f)
		{
			mStepDamaged -= mSceneManager->GetDeltaTime();
		}

	}
		break;
	case Turret::STATE::DESTROY:

		// �e�̍X�V
		mExplosion->Update();
		break;
	}

	if (IsAlive() == true)
	{
		ProcessShot();
	}
}

void Turret::Draw(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:

		if (mStepDamaged > 0.0f)
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
		}
		else
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.48f, 0.52f, 0.4f, 1.0f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.2f, 0.4f, 0.3f, 1.0f));
		}

		MV1DrawModel(mTransformStand.modelId);
		MV1DrawModel(mTransformGun.modelId);

		if (IS_DEBUG)
		{
			DrawSphere3D(mTransformStand.pos, COLLISION_RADIUS, 10, 0xff0000, 0xffffff, false);
		}

		break;
	case Turret::STATE::DESTROY:
		mExplosion->Draw();
		break;
	}

}

void Turret::Release(void)
{

	mExplosion->Release();
	delete mExplosion;
	mExplosion = nullptr;

}

void Turret::SyncParent(Transform* transform, VECTOR addAxis)
{
	VECTOR localPos;
	//��]����e��������p��
	transform->quaRot = mTransformParent->quaRot;

	//�e�̉�]�ɍ��킹�āA�q���̑��΍��W���v�Z����
	//SCALE�l���傫���Ȃ�ƁA�ʒu�֌W���傫���Ȃ�̂ŁA
	//SCALE�l��1�ȊO�̏ꍇ�́A�傫���̌v�Z���K�v
	localPos = Quaternion::PosAxis(transform->quaRot, mLocalPos);
	transform->pos = VAdd(mTransformParent->pos, VScale(localPos, SCALE));

	//���q�����g�̉�]
	//Quaternion localRot = Quaternion::Euler(mLocalAddAxis);
	//transform->quaRot = transform->quaRot.Mult(localRot);

	Quaternion localRot;
	Quaternion axis;

	// Unity Z��X��Y = Y * X * Z

	axis = Quaternion::AngleAxis(mLocalAddAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	//����ɉ�](�C���Y����]�A�C���X����])
	//�g�p�����]���addAxis
	axis = Quaternion::AngleAxis(addAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	transform->quaRot = transform->quaRot.Mult(localRot);

	//���f������̍X�V
	transform->Update();
}

void Turret::ProcessShot(void)
{
	//�e�̐����f�B���C
	mDelayShot -= mSceneManager->GetDeltaTime();
	if (mDelayShot <= 0.0f)
	{
		mDelayShot = 0.0f;
	}

	if (mDelayShot <= 0.0f)
	{
		mDelayShot = TIME_DELAY_SHOT;

		//���@�̒e�𐶐�
		CreateShot();
	}
}

bool Turret::IsAlive(void)
{
	return mState == STATE::ATTACK;
}

VECTOR Turret::GetPos(void)
{
	return mTransformStand.pos;
}

void Turret::Damage(void)
{

	mStepDamaged = TIME_DAMAGED_EFFECT;

	mHp -= 1;
	if (mHp <= 0)
	{
		ChangeState(STATE::DESTROY);
	}

}

std::vector<TurretShot*> Turret::GetShots(void)
{
	return mShots;
}

void Turret::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
		break;
	case Turret::STATE::DESTROY:
	{
		auto mat = mTransformGun.quaRot.ToMatrix();
		auto localPos = VTransform({ 0.0f, 1.2f, 0.0f }, mat);
		auto birthPos = VAdd(mTransformStand.pos, VScale(localPos, SCALE));
		mExplosion->Create(birthPos);
	}
	break;
	}

}

void Turret::CreateShot(void)
{
	//�e�̔��ˈʒu����
	//�e�̉�]���ɍ��킹���ʒu���v�Z
	//MATRIX mat = mTransformGun.qutRot.ToMatrix();
	//VECTOR localPos = VTransform({ 0.0f, 2.0f, 3.0f }, mat);

	VECTOR localPos = Quaternion::PosAxis(
		mTransformGun.quaRot, { 0.0f, 2.0f, 3.0f });
	VECTOR pos = VAdd(mTransformGun.pos, VScale(localPos, SCALE));

	VECTOR dir = mTransformGun.GetForward();

	bool isCreate = false;
	for (auto& shot : mShots)
	{
		if (!shot->IsAlive())
		{
			//�C���X�^���X�̎g���܂킵
			shot->Create(pos, dir);
			isCreate = true;
		}
	}

	if (!isCreate)
	{
		//�g���܂킵�ł��Ȃ�������
		TurretShot* newShot =
			new TurretShot(mSceneManager, &mTransformGun);
		newShot->Create(pos, mTransformGun.GetForward());
		mShots.push_back(newShot);
	}
}
