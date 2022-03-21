#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Camera.h"
#include "Unit.h"
#include "Enemy.h"
#include "AsoUtility.h"
#include "RollBall.h"
#include "ShotBall.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mStage = new Stage(mSceneManager);
	mStage->Init();

	mUnit = new Unit(mSceneManager);
	mUnit->Init();

	mEnemy = new Enemy(mSceneManager, mUnit);
	mEnemy->Init();

	mRollBall = new RollBall(mSceneManager, mUnit);
	mRollBall->Init();

	for (int s = 0; s < 50; s++)
	{
		mShotBall[s] = new ShotBall(mSceneManager);
		mShotBall[s]->Init();
	}

	Camera* camera = mSceneManager->GetCamera();
	camera->GetUnit(mUnit);
}

void TitleScene::Update(void)
{
	mIsShot[0] = CheckHitKey(KEY_INPUT_Q);

	if (mIsShot[0] && !mIsShot[1])
	{
		for (const auto s:mShotBall)
		{
			if (!s->IsAlive())
			{
				s->Create(mUnit->GetPos(), mUnit->GetAnglePos().y, GetColor(rand() % 255, rand() % 255, rand() % 255));
				break;
			}
		}
	}

	mStage->UpDate();
	mUnit->UpDate();
	mEnemy->UpDate();
	mRollBall->UpDate();
	for (const auto s : mShotBall)
	{
		s->UpDate();
	}
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}
	mIsShot[1] = mIsShot[0];
}

void TitleScene::Draw(void)
{
	mStage->Draw();
	mUnit->Draw();
	mEnemy->Draw();
	mRollBall->Draw();
	for (const auto s : mShotBall)
	{
		s->Draw();
	}
	DrawDebug();
}

void TitleScene::DrawDebug(void)
{
	Camera* camera = mSceneManager->GetCamera();

	VECTOR pos = camera->GetPos();
	VECTOR angles = camera->GetAnglePos();

	//--------------------------------------------------------------
	DrawString(0, 3, "●カメラ", 0xffffff);

	DrawFormatString(
		0, 20, 0xffffff,
		"カメラ座標 : (%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);

	DrawFormatString(
		0, 40, 0xffffff,
		"カメラ角度 : (%.1f, %.1f, %.1f)",
		AsoUtility::Rad2DegD(angles.x),
		AsoUtility::Rad2DegD(angles.y), 
		AsoUtility::Rad2DegD(angles.z)
	);
	pos = camera->GetTargetPos();
	DrawFormatString(
		0, 60, 0xffffff,
		"注視点座標 : (%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);

	DrawSphere3D(pos, 10.0f, 10, 0xffffff, 0xffffff, 1);	//注視点に球体を描画
	//--------------------------------------------------------------------------------
	DrawString(0, 90, "●ユニット", 0xffffff);
	pos = mUnit->GetPos();
	angles = mUnit->GetAnglePos();

	DrawFormatString(
		0, 110, 0xffffff,
		"ユニット座標 : (%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);

	DrawFormatString(
		0, 130, 0xffffff,
		"ユニット角度 : (%.1f, %.1f, %.1f)",
		AsoUtility::Rad2DegD(angles.x),
		AsoUtility::Rad2DegD(angles.y),
		AsoUtility::Rad2DegD(angles.z)
	);

	//------------------------------------------------
	DrawString(0, 160, "●ロールボール", 0xffffff);
	//2つの座標から角度を求める
	VECTOR uPos = pos;
	VECTOR bPos = mRollBall->GetPos();

	float diffX = bPos.x - uPos.x;	//衛星ー太陽
	float diffZ = bPos.z - uPos.z;

	//Zの方向から見た角度
	float rad = atan2f(diffX,diffZ);
	float deg = AsoUtility::Rad2DegF(rad);
	deg = AsoUtility::DegIn360(deg);
	DrawFormatString(
		0, 180, 0xffffff,
		"対Z角　　　　: %.1f",
		deg
	);

	float uAngle = AsoUtility::Rad2DegD(angles.y);
	deg -= uAngle;
	deg = AsoUtility::DegIn360(deg);
	//プレイヤーから見た角度
	DrawFormatString(
		0, 200, 0xffffff,
		"対ユニット角 : %.1f",
		deg
	);

	pos = mRollBall->GetPos();
	DrawFormatString(
		0, 220, 0xffffff,
		"ロールボール座標 : (%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);

	//-----------------------------------------------------------------
	DrawString(0, 250, "●エネミー", 0xffffff);
	pos = VSub(uPos, mEnemy->GetPos());
	float distance = pos.x * pos.x + pos.z * pos.z;
	distance = sqrtf(distance);
	rad = atan2f(pos.x, pos.z);
	deg = AsoUtility::Rad2DegF(rad);
	deg = AsoUtility::DegIn360(deg);

	angles = mEnemy->GetAnglePos();
	float eAngle = AsoUtility::Rad2DegF(angles.y);
	deg -= eAngle;
	deg = AsoUtility::DegIn360(deg);

	DrawFormatString(
		0, 270, 0xffffff,
		"対ユニット角度 : %.1f",
		deg
	);
	DrawFormatString(
		0, 290, 0xffffff,
		"対ユニット距離 : %.1f",
		distance
	);
}

void TitleScene::Release(void)
{
	mStage->Release();
	delete mStage;
	mStage = nullptr;
	mUnit->Release();
	delete mUnit;
	mUnit = nullptr;
	delete mRollBall;
	mRollBall = nullptr;
	for (int s = 0; s < 50; s++)
	{
		delete mShotBall[s];
		mShotBall[s] = nullptr;
	}
}
