#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "Wheel.h"

Wheel::Wheel(SceneManager* manager,
	Transform* transformParent,
	VECTOR localPos, 
	VECTOR localAddAxis,
	bool isLeft)
{
	mSceneManager = manager;

	mTransformParent = transformParent;
	mLocalPos = localPos;
	mLocalAddAxis = localAddAxis;
	if (isLeft == true)
	{
		mWheel[0] = KEY_INPUT_LEFT;
		mWheel[1] = KEY_INPUT_RIGHT;
	}
	else
	{
		mWheel[0] = KEY_INPUT_RIGHT;
		mWheel[1] = KEY_INPUT_LEFT;
	}

	mTransformWheel.SetModel(MV1LoadModel("Data/Model/Tank/Wheel.mv1"));

	// 砲身ローカル回転
	mLocalAddAxisWheel = { 0.0f, 0.0f, 0.0f };
}

void Wheel::Init(void)
{
	Quaternion localRot;
	Quaternion axis;

	// モデル制御の基本情報(砲台)
	mTransformWheel.scl = { 0.5f, 0.5f, 0.5f };
	mTransformWheel.quaRot = Quaternion();

	// ローカル回転
	mTransformWheel.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// 親モデルと同期
	SyncParent(&mTransformWheel, { 0, 0, 0 });

	// タイヤローカル稼働量(deg)
	mAnglePowWheel = ANGLE_POW_WHEEL;
}

void Wheel::Update(void)
{
	//往復のY軸回転(mLocalAddAxisStand)
	float move = 0.0f;
	float dir = 0.0f;
	if (CheckHitKey(KEY_INPUT_W))
	{
		move = -mAnglePowWheel;
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		move = mAnglePowWheel;
	}

	if (CheckHitKey(mWheel[0]))
	{
		dir = mAnglePowWheel / 3.0f;
	}

	if (CheckHitKey(mWheel[1]))
	{
		dir = -mAnglePowWheel / 3.0f;
	}
	mLocalAddAxisWheel.x += (move + dir);
	SyncParent(&mTransformWheel, mLocalAddAxisWheel);
}

void Wheel::Draw(void)
{
	MV1DrawModel(mTransformWheel.modelId);	
}

void Wheel::Release(void)
{
	MV1DrawModel(mTransformWheel.modelId);
}

void Wheel::SyncParent(Transform* transform, VECTOR addAxis)
{
	VECTOR localPos;
	//回転情報を親から引き継ぐ
	transform->quaRot = mTransformParent->quaRot;

	//親の回転に合わせて、子供の相対座標を計算する
	//SCALE値が大きくなると、位置関係も大きくなるので、
	//SCALE値が1以外の場合は、大きさの計算も必要
	localPos = Quaternion::PosAxis(transform->quaRot, mLocalPos);
	transform->pos = VAdd(mTransformParent->pos, VScale(localPos, SCALE));

	//★子供自身の回転
	//Quaternion localRot = Quaternion::Euler(mLocalAddAxis);
	//transform->quaRot = transform->quaRot.Mult(localRot);

	Quaternion localRot;
	Quaternion axis;

	// Unity Z→X→Y = Y * X * Z

	axis = Quaternion::AngleAxis(mLocalAddAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	//さらに回転(砲台はY軸回転、砲台はX軸回転)
	//使用する回転情報addAxis
	axis = Quaternion::AngleAxis(addAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	transform->quaRot = transform->quaRot.Mult(localRot);

	//モデル制御の更新
	transform->Update();
}
