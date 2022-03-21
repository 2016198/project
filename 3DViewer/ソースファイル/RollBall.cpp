#include <cmath>
#include "AsoUtility.h"
#include "RollBall.h"
#include "SceneManager.h"
#include "Unit.h"

RollBall::RollBall(SceneManager* manager, Unit* unit)
{
	mSceneManager = manager;
	mUnit = unit;
}

void RollBall::Init(void)
{
	mStep = 0.0f;
	mPos = {};
}

void RollBall::UpDate(void)
{
	mStep += mSceneManager->GetDeltaTime();

	VECTOR uPos = mUnit->GetPos();

	//çÇÇ≥
	mPos.y = 70.0f;

	//îºåa
	float dis = 100.0f;
	mPos.x = uPos.x + (dis * sin(mStep));
	mPos.z = uPos.z + (dis * cos(mStep));
}

void RollBall::Draw(void)
{
	DrawSphere3D(mPos, 15.0f, 20, 0xff0000, 0x00ff00, true);
	VECTOR pos1 = mPos;
	VECTOR pos2 = mPos;
	pos1.x -= 20.0f;
	pos2.x += 20.0f;
	DrawLine3D(pos1, pos2, 0x888888);
	pos1 = mPos;
	pos2 = mPos;
	pos1.y -= 20.0f;
	pos2.y += 20.0f;
	DrawLine3D(pos1, pos2, 0x888888);
	pos1 = mPos;
	pos2 = mPos;
	pos1.z -= 20.0f;
	pos2.z += 20.0f;
	DrawLine3D(pos1, pos2, 0x888888);
}

VECTOR RollBall::GetPos()
{
	return mPos;
}
