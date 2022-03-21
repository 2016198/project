#include <cmath>
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"
#include "Enemy.h"
#include "Unit.h"

Enemy::Enemy(SceneManager* manager, Unit* unit)
{
	mSceneManager = manager;
	mUnit = unit;
}

void Enemy::Init(void)
{
	mModelId = MV1LoadModel("Model/Human.mv1");
	mModelid = MV1LoadModel("Model/car.mv1");
	mIsNotice = false;
	mPos = { 200.0f,0.0f,400.0f };
	mAngles = { 0.0f,AsoUtility::Deg2RadF(42.0f),0.0f };
	mAnglesLocal = { 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f };

	MV1SetPosition(mModelId, mPos);

	//モデルの角度を設定
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModelId, angles);
	MV1SetRotationXYZ(mModelid, angles);

	//モデルの座標を設定
	MV1SetPosition(mModelId, mPos);
	MV1SetPosition(mModelid, mPos);

	MV1SetMaterialDifColor(mModelid, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
}

void Enemy::UpDate(void)
{
	mIsNotice = false;

	VECTOR uPos = mUnit->GetPos();
	VECTOR diff = VSub(uPos, mPos);

	//2つの座標をピタゴラスの定理を使って、指定範囲内かチェック
	float distance = std::pow(diff.x, 2.0f) + std::pow(diff.z, 2.0f);

	if (distance < std::pow(VIEW_RANGE, 2.0f))
	{
		//演習③の角度の取り方を参考に、ユニットが指定角度内かチェック
		float viewRad = atan2f(diff.x, diff.z);
		/*float viewDeg = AsoUtility::Rad2DegF(viewRad);
		float angle = AsoUtility::Rad2DegF(mAngles.y);
		viewDeg -= angle;*/
		float viewDeg = viewRad - mAngles.y;
		viewDeg = AsoUtility::Rad2DegF(viewDeg);
		if (VIEW_ANGLE > viewDeg && viewDeg > -VIEW_ANGLE)
		{
			mIsNotice = true;
		}
	}

}

void Enemy::Draw(void)
{
	if (mIsNotice == true)
	{
		MV1SetMaterialDifColor(mModelId, 0, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		MV1SetMaterialDifColor(mModelId, 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
	}
	//モデルの描画
	MV1DrawModel(mModelId);
	MV1DrawModel(mModelid);

	float viewRad = AsoUtility::Deg2RadF(VIEW_ANGLE);

	//向き角度から方向を取得する
	float x1 = sinf(mAngles.y);
	float z1 = cosf(mAngles.y);

	float x2 = sinf(mAngles.y - viewRad);
	float z2 = cosf(mAngles.y - viewRad);

	float x3 = sinf(mAngles.y + viewRad);
	float z3 = cosf(mAngles.y + viewRad);

	//自分の位置
	VECTOR pos0 = mPos;

	//正面の位置
	VECTOR pos1 = mPos;
	pos1.x += (x1 * VIEW_RANGE);
	pos1.z += (z1 * VIEW_RANGE);

	//正面から反時計周りに30度ずれたの位置
	VECTOR pos2 = mPos;
	pos2.x += (x2 * VIEW_RANGE);
	pos2.z += (z2 * VIEW_RANGE);

	//正面から時計周りに30度ずれたの位置
	VECTOR pos3 = mPos;
	pos3.x += (x3 * VIEW_RANGE);
	pos3.z += (z3 * VIEW_RANGE);

	//視野の描画
	DrawLine3D(pos0, pos1, 0x000000);
	DrawLine3D(pos0, pos2, 0x000000);
	DrawLine3D(pos0, pos3, 0x000000);

	//注意！DrawTriangle3Dの引数の座標は、
	//		時計回りに指定してください。
	pos0.y = pos1.y = pos2.y = pos3.y = 1.0f;
	DrawTriangle3D(pos0, pos2, pos1, 0xff00ff, true);
	DrawTriangle3D(pos0, pos1, pos3, 0xff00ff, true);
}

void Enemy::Release(void)
{
	MV1DeleteModel(mModelId);
	MV1DeleteModel(mModelid);
}

VECTOR Enemy::GetPos(void)
{
	return mPos;
}

VECTOR Enemy::GetAnglePos(void)
{
	return mAngles;
}
