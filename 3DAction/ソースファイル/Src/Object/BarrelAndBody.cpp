#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Common/KeyCheck.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "TankShot.h"
#include "BarrelAndBody.h"

BarrelAndBody::BarrelAndBody(
	SceneManager* manager,
	Transform* transformParent
	, VECTOR localPos,
	VECTOR localAddAxis)
{
	mSceneManager = manager;

	mTransformParent = transformParent;
	mLocalPos = localPos;
	mLocalAddAxis = localAddAxis;

	mTransformBody.SetModel(MV1LoadModel("Data/Model/Tank/Body.mv1"));
	mTransformBarrel.SetModel(MV1LoadModel("Data/Model/Tank/Barrel.mv1"));

	// �C�g���[�J����]
	mLocalAddAxisBody = { 0.0f, 0.0f, 0.0f };
	mLocalAddAxisBarrel = { 0.0f, 0.0f, 0.0f };
}

void BarrelAndBody::Init(void)
{
	Quaternion localRot;
	Quaternion axis;

	// ���f������̊�{���(��)
	mTransformBody.scl = { 0.5f, 0.5f, 0.5f };
	mTransformBody.quaRot = Quaternion();

	// ���[�J����]
	mTransformBody.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// �e���f���Ɠ���
	SyncParent(&mTransformBody, { 0, 0, 0 });



	// ���f������̊�{���(�C��)
	mTransformBarrel.scl = { 0.5f, 0.5f, 0.5f };
	mTransformBarrel.quaRot = Quaternion();

	// ���[�J����]
	mTransformBarrel.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// �e���f���Ɠ���
	SyncParent(&mTransformBarrel, { 0.0f, 0.0f, 0.0f });

	// �䃍�[�J���ғ���(deg)
	mAnglePowBody = ANGLE_POW_BODY;

	// �C�䃍�[�J���ғ���(deg)
	mAnglePowBarrel = ANGLE_POW_BARREL;
}

void BarrelAndBody::Update(void)
{
	//��X����](mLocalAddAxisBody)
	float dir = 0.0f;

	if (CheckHitKey(KEY_INPUT_UP))
	{
		dir = mAnglePowBody;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		dir = -mAnglePowBody;
	}

	if (keyTrgDown[KEY_P1_A])
	{
		CreateShot();
	}

	mLocalAddAxisBody.x += dir;
	SyncParent(&mTransformBody, mLocalAddAxisBody);

	//�C���Z����]
	mLocalAddAxisBarrel.z += mAnglePowBarrel;
	SyncParent(&mTransformBarrel, mLocalAddAxisBarrel);

	//��]�̍���
	Quaternion body = Quaternion::Euler(mLocalAddAxisBody);
	Quaternion barrel = Quaternion::Euler(mLocalAddAxisBarrel);
	Quaternion mix = body.Mult(barrel);
	SyncParent(&mTransformBarrel, mix.ToEuler());

	//�e�̍X�V
	for (auto& shot : mTankShots)
	{
		if (shot->IsAlive())
		{
			shot->Update();
		}
	}
}

void BarrelAndBody::Draw(void)
{
	MV1DrawModel(mTransformBody.modelId);
	MV1DrawModel(mTransformBarrel.modelId);

	//�e�̕`��
	for (auto& shot : mTankShots)
	{
		if (shot->IsAlive())
		{
			shot->Draw();
		}
	}
}

void BarrelAndBody::Release(void)
{
	MV1DeleteModel(mTransformBarrel.modelId);
	MV1DeleteModel(mTransformBody.modelId);
	mTankShots.clear();
}

void BarrelAndBody::SyncParent(Transform* transform, VECTOR addAxis)
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

void BarrelAndBody::CreateShot(void)
{
	//�g�p����Ă��Ȃ����̂��ė��p����
	for (auto& shot : mTankShots)
	{
		if (!shot->IsAlive())
		{
			shot->Generate(mTransformBarrel.pos,
				mTransformBarrel.GetForward(),
				GetColor(GetRand(255), GetRand(255), GetRand(255)));
			return;
		}
	}

	//���ꂪ�Ȃ�������V��������
	TankShot* tankShot = new TankShot(mSceneManager);

	tankShot->Generate(mTransformBarrel.pos,
		mTransformBarrel.GetForward(),
		GetColor(GetRand(255), GetRand(255), GetRand(255)));

	mTankShots.push_back(tankShot);
}
