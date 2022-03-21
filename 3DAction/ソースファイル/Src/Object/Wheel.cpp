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

	// –Cgƒ[ƒJƒ‹‰ñ“]
	mLocalAddAxisWheel = { 0.0f, 0.0f, 0.0f };
}

void Wheel::Init(void)
{
	Quaternion localRot;
	Quaternion axis;

	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ(–C‘ä)
	mTransformWheel.scl = { 0.5f, 0.5f, 0.5f };
	mTransformWheel.quaRot = Quaternion();

	// ƒ[ƒJƒ‹‰ñ“]
	mTransformWheel.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// eƒ‚ƒfƒ‹‚Æ“¯Šú
	SyncParent(&mTransformWheel, { 0, 0, 0 });

	// ƒ^ƒCƒ„ƒ[ƒJƒ‹‰Ò“­—Ê(deg)
	mAnglePowWheel = ANGLE_POW_WHEEL;
}

void Wheel::Update(void)
{
	//‰•œ‚ÌYŽ²‰ñ“](mLocalAddAxisStand)
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
