#include <string>
#include <EffekseerForDXLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "Common/Collider.h"
#include "Common/SpeechBalloon.h"
#include "Planet.h"
#include "Wheel.h"
#include "BarrelAndBody.h"
#include "Tank.h"

Tank::Tank(SceneManager* manager)
{
	mSceneManager = manager;
	mResourceManager = manager->GetResourceManager();
	mGravityManager = manager->GetGravityManager();
}

void Tank::Init(void)
{

	// モデルの基本設定
	mTransform.SetModel(-1);

	mTransform.pos = { 0.0f, 30.0f, 0.0f };
	mTransform.scl = { 0.5f, 0.5f, 0.5f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = Quaternion();
	mTransform.Update();

	//タイヤの作成

	//左
	MakeWhlle(
		{ -30.5f, 25.5f, 0.0f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f },
		true
	);
	//右
	MakeWhlle(
		{ 30.5f, 25.5f, 0.0f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f },
		false
	);

	//台と砲台
	MakeBarrelAndBody(
		{ 0.0f, 50.0f, 0.0f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f }
	);

}

void Tank::Update(void)
{
	//更新処理
	mTransform.Update();

	//タイヤの更新
	UpdateWhlle();

	//台と砲台の更新
	UpdateBarrelAndBody();
	
	UpdatePlay();
}

void Tank::UpdatePlay(void)
{
	//移動処理(mMovePowを作る処理)
	ProcessMove();

	//重力による移動量計算
	CalcGravityPow();

	//衝突判定
	Collision();
}

void Tank::Draw(void)
{

	//タイヤの描画
	DrawWhlle();

	//台と砲台の描画
	DrawBarrelAndBody();

	// デバッグ用描画
	DrawDebug();

}

void Tank::DrawDebug(void)
{
	unsigned int white = 0xffffff;
	unsigned int black = 0x000000;
	unsigned int red = 0xff0000;
	unsigned int green = 0x00ff00;
	unsigned int blue = 0x0000ff;
	unsigned int yellow = 0xffff00;
 	unsigned int purpl = 0x800080;

	VECTOR vector;

	// キャラ基本情報
	//-------------------------------------------------------
	// キャラ座標
	vector = mTransform.pos;
	DrawFormatString(20, 60, black, "タンク座標 ： (%0.2f, %0.2f, %0.2f)",
		vector.x, vector.y, vector.z
	);

	//-------------------------------------------------------

	//衝突判定用の線

	//DrawLine3D(mGravHitDown, mGravHitUp, 0);

}

void Tank::AddCollider(Collider* collider)
{
	mColliders.push_back(collider);
}

void Tank::ClearCollider(void)
{
	mColliders.clear();
}

void Tank::Release(void)
{
	mTransform.Release();
	for (const auto& wheel : mWheels)
	{
		wheel->Release();
	}
	mBarrelAndBody->Release();
}

void Tank::ProcessMove(void)
{
	//移動量をゼロ
	mMovePow = AsoUtility::VECTOR_ZERO;

	//移動方向
	VECTOR dir, dirL, dirR;
	dir = dirL = dirR = AsoUtility::VECTOR_ZERO;

	Quaternion axisY;

	if (CheckHitKey(KEY_INPUT_W))
	{
		dir = mTransform.GetForward();
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		dir = mTransform.GetBack();
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		axisY = Quaternion::AngleAxis(AsoUtility::Deg2RadD(-ROT_DEG),
			AsoUtility::AXIS_Y);
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		axisY = Quaternion::AngleAxis(AsoUtility::Deg2RadD(ROT_DEG),
			AsoUtility::AXIS_Y);
	}

	mTransform.quaRot = Quaternion::Mult(axisY, mTransform.quaRot);


	if (!AsoUtility::EqualsVZero(dir))
	{
		//移動
		mSpeed = SPEED_MOVE;

		//移動方向・移動量
		mMovePow = VScale(dir, mSpeed);
	}

}

void Tank::CalcGravityPow(void)
{
	//重力方向
	VECTOR dirGravity = mGravityManager->GetDirGravity();

	//重力の強さ
	float gravityPow = mGravityManager->GetPower();

	//重力
	VECTOR gravity = VScale(dirGravity, gravityPow);
	mGravityPow = VAdd(mGravityPow, gravity);

	float dot = VDot(dirGravity, mGravityPow);
	if (dot >= 0.0f)
	{
		//落下中
		mGravityPow = gravity;
	}
}

Transform* Tank::GetTransform(void)
{
	return &mTransform;
}

void Tank::Collision(void)
{
	//現在座標を起点に移動後座標を決める
	mMovedPos = VAdd(mTransform.pos, mMovePow);

	//衝突(重力)
	CollisionGravity();

	//移動
	mTransform.pos = mMovedPos;

}

void Tank::CollisionGravity(void)
{
	//ジャンプパワーを移動座標に加算
	mMovedPos = VAdd(mMovedPos, mGravityPow);

	//重力
	float checkPow = 10.0f;
	VECTOR dirUpGravity = mGravityManager->GetDirUpGravity();
	VECTOR dirGravity = mGravityManager->GetDirGravity();
	float gravityPow = mGravityManager->GetPower();

	mGravHitUp = VAdd(mMovedPos, VScale(dirUpGravity, gravityPow));
	mGravHitUp = VAdd(mGravHitUp, VScale(dirUpGravity, checkPow * 2.0f));
	mGravHitDown = VAdd(mMovedPos, VScale(dirGravity, checkPow));

	for (auto c : mColliders)
	{
		//地面との衝突
		auto hit = MV1CollCheck_Line(c->mModelId, -1, mGravHitUp, mGravHitDown);
		if (hit.HitFlag > 0)
		{

			//衝突地点から、少し上に移動
			mMovedPos = VAdd(hit.HitPosition, VScale(dirUpGravity, 2.0f));

		}
	}
}

void Tank::MakeWhlle(VECTOR localPos, VECTOR localAddAxis, bool isLeft)
{
	Wheel* wheel = new Wheel(
		mSceneManager,
		&mTransform,
		localPos, localAddAxis,
		isLeft);

	wheel->Init();

	mWheels.push_back(wheel);
}

void Tank::UpdateWhlle(void)
{
	for (const auto& whlle : mWheels)
	{
		whlle->Update();
	}
}

void Tank::DrawWhlle(void)
{
	for (const auto& whlle : mWheels)
	{
		whlle->Draw();
	}
}

void Tank::MakeBarrelAndBody(VECTOR localPos, VECTOR localAddAxis)
{
	mBarrelAndBody = new BarrelAndBody(
		mSceneManager,
		&mTransform,
		localPos, localAddAxis);

	mBarrelAndBody->Init();
}

void Tank::UpdateBarrelAndBody(void)
{
	mBarrelAndBody->Update();
}

void Tank::DrawBarrelAndBody(void)
{
	mBarrelAndBody->Draw();
}

