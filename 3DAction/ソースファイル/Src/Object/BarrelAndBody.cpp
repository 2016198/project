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

	// 砲身ローカル回転
	mLocalAddAxisBody = { 0.0f, 0.0f, 0.0f };
	mLocalAddAxisBarrel = { 0.0f, 0.0f, 0.0f };
}

void BarrelAndBody::Init(void)
{
	Quaternion localRot;
	Quaternion axis;

	// モデル制御の基本情報(台)
	mTransformBody.scl = { 0.5f, 0.5f, 0.5f };
	mTransformBody.quaRot = Quaternion();

	// ローカル回転
	mTransformBody.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// 親モデルと同期
	SyncParent(&mTransformBody, { 0, 0, 0 });



	// モデル制御の基本情報(砲台)
	mTransformBarrel.scl = { 0.5f, 0.5f, 0.5f };
	mTransformBarrel.quaRot = Quaternion();

	// ローカル回転
	mTransformBarrel.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// 親モデルと同期
	SyncParent(&mTransformBarrel, { 0.0f, 0.0f, 0.0f });

	// 台ローカル稼働量(deg)
	mAnglePowBody = ANGLE_POW_BODY;

	// 砲台ローカル稼働量(deg)
	mAnglePowBarrel = ANGLE_POW_BARREL;
}

void BarrelAndBody::Update(void)
{
	//台X軸回転(mLocalAddAxisBody)
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

	//砲台のZ軸回転
	mLocalAddAxisBarrel.z += mAnglePowBarrel;
	SyncParent(&mTransformBarrel, mLocalAddAxisBarrel);

	//回転の合成
	Quaternion body = Quaternion::Euler(mLocalAddAxisBody);
	Quaternion barrel = Quaternion::Euler(mLocalAddAxisBarrel);
	Quaternion mix = body.Mult(barrel);
	SyncParent(&mTransformBarrel, mix.ToEuler());

	//弾の更新
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

	//弾の描画
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

void BarrelAndBody::CreateShot(void)
{
	//使用されていないものを再利用する
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

	//それがなかったら新しく生成
	TankShot* tankShot = new TankShot(mSceneManager);

	tankShot->Generate(mTransformBarrel.pos,
		mTransformBarrel.GetForward(),
		GetColor(GetRand(255), GetRand(255), GetRand(255)));

	mTankShots.push_back(tankShot);
}
