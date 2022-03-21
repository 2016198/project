#include <cmath>
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"
#include "ShotBall.h"

ShotBall::ShotBall(SceneManager* manager)
{
	mSceneManager = manager;
}

void ShotBall::Init(void)
{
	mPos = {0.0f,0.0f,0.0f};
	mAlive = false;
	mLife = 0.0f;
	mx = mz = 0.0f;
	mColor = 0x000000;
}

void ShotBall::UpDate(void)
{
	if (mLife > 0.0f)
	{
		mPos.x += (mx * MOVE_SPEED);
		mPos.z += (mz * MOVE_SPEED);
	}
	else
	{
		Destroy();
	}
	mLife -= 1.0f;
}

void ShotBall::Draw(void)
{
	if (mAlive)
	{
		DrawSphere3D(mPos, 30.0f, 20, mColor, 0xffffff, true);
	}
}

void ShotBall::Create(VECTOR pos, float angleY, unsigned int color)
{
	mx = sinf(angleY);
	mz = cosf(angleY);
	mPos = pos;
	mPos.y += 100.0f;
	mAlive = true;
	mLife = LIFE;
	mColor = color;
}

void ShotBall::Destroy(void)
{
	mAlive = false;
	mx = mz = 0.0f;
}

bool ShotBall::IsAlive(void)
{
	return mAlive;
}
