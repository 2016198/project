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

	// –Cgƒ[ƒJƒ‹‰ñ“]
	mLocalAddAxisBody = { 0.0f, 0.0f, 0.0f };
	mLocalAddAxisBarrel = { 0.0f, 0.0f, 0.0f };
}

void BarrelAndBody::Init(void)
{
	Quaternion localRot;
	Quaternion axis;

	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ(‘ä)
	mTransformBody.scl = { 0.5f, 0.5f, 0.5f };
	mTransformBody.quaRot = Quaternion();

	// ƒ[ƒJƒ‹‰ñ“]
	mTransformBody.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// eƒ‚ƒfƒ‹‚Æ“¯Šú
	SyncParent(&mTransformBody, { 0, 0, 0 });



	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ(–C‘ä)
	mTransformBarrel.scl = { 0.5f, 0.5f, 0.5f };
	mTransformBarrel.quaRot = Quaternion();

	// ƒ[ƒJƒ‹‰ñ“]
	mTransformBarrel.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// eƒ‚ƒfƒ‹‚Æ“¯Šú
	SyncParent(&mTransformBarrel, { 0.0f, 0.0f, 0.0f });

	// ‘äƒ[ƒJƒ‹‰Ò“­—Ê(deg)
	mAnglePowBody = ANGLE_POW_BODY;

	// –C‘äƒ[ƒJƒ‹‰Ò“­—Ê(deg)
	mAnglePowBarrel = ANGLE_POW_BARREL;
}

void BarrelAndBody::Update(void)
{
	//‘äXŽ²‰ñ“](mLocalAddAxisBody)
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

	//–C‘ä‚ÌZŽ²‰ñ“]
	mLocalAddAxisBarrel.z += mAnglePowBarrel;
	SyncParent(&mTransformBarrel, mLocalAddAxisBarrel);

	//‰ñ“]‚Ì‡¬
	Quaternion body = Quaternion::Euler(mLocalAddAxisBody);
	Quaternion barrel = Quaternion::Euler(mLocalAddAxisBarrel);
	Quaternion mix = body.Mult(barrel);
	SyncParent(&mTransformBarrel, mix.ToEuler());

	//’e‚ÌXV
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

	//’e‚Ì•`‰æ
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
	//‰ñ“]î•ñ‚ðe‚©‚çˆø‚«Œp‚®
	transform->quaRot = mTransformParent->quaRot;

	//e‚Ì‰ñ“]‚É‡‚í‚¹‚ÄAŽq‹Ÿ‚Ì‘Š‘ÎÀ•W‚ðŒvŽZ‚·‚é
	//SCALE’l‚ª‘å‚«‚­‚È‚é‚ÆAˆÊ’uŠÖŒW‚à‘å‚«‚­‚È‚é‚Ì‚ÅA
	//SCALE’l‚ª1ˆÈŠO‚Ìê‡‚ÍA‘å‚«‚³‚ÌŒvŽZ‚à•K—v
	localPos = Quaternion::PosAxis(transform->quaRot, mLocalPos);
	transform->pos = VAdd(mTransformParent->pos, VScale(localPos, SCALE));

	//šŽq‹ŸŽ©g‚Ì‰ñ“]
	//Quaternion localRot = Quaternion::Euler(mLocalAddAxis);
	//transform->quaRot = transform->quaRot.Mult(localRot);

	Quaternion localRot;
	Quaternion axis;

	// Unity Z¨X¨Y = Y * X * Z

	axis = Quaternion::AngleAxis(mLocalAddAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	//‚³‚ç‚É‰ñ“](–C‘ä‚ÍYŽ²‰ñ“]A–C‘ä‚ÍXŽ²‰ñ“])
	//Žg—p‚·‚é‰ñ“]î•ñaddAxis
	axis = Quaternion::AngleAxis(addAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	transform->quaRot = transform->quaRot.Mult(localRot);

	//ƒ‚ƒfƒ‹§Œä‚ÌXV
	transform->Update();
}

void BarrelAndBody::CreateShot(void)
{
	//Žg—p‚³‚ê‚Ä‚¢‚È‚¢‚à‚Ì‚ðÄ—˜—p‚·‚é
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

	//‚»‚ê‚ª‚È‚©‚Á‚½‚çV‚µ‚­¶¬
	TankShot* tankShot = new TankShot(mSceneManager);

	tankShot->Generate(mTransformBarrel.pos,
		mTransformBarrel.GetForward(),
		GetColor(GetRand(255), GetRand(255), GetRand(255)));

	mTankShots.push_back(tankShot);
}
