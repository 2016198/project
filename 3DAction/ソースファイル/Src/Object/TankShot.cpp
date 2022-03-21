#include <EffekseerForDXLib.h>
#include "../Manager/SceneManager.h"
#include "TankShot.h"

TankShot::TankShot(SceneManager* manager): mSceneManager(manager)
{
	mLife = 0.0f;
}

void TankShot::Generate(VECTOR pos, VECTOR forward, unsigned int color)
{
	mColor = color;
	mLife = LIFE;
	mPos = VSub(pos, VScale(forward, SPEED * 10.0f));
	mMovePow = VScale(forward, SPEED);
}

void TankShot::Update(void)
{
	mPos = VSub(mPos, mMovePow);
	mLife -= mSceneManager->GetDeltaTime();
}

void TankShot::Draw(void)
{
	DrawSphere3D(mPos, 10.0f, 10, mColor, 0xffffff, true);
}

bool TankShot::IsAlive(void)
{
	return mLife > 0.0f;
}
