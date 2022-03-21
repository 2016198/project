#include <DxLib.h>
#include "SceneManager.h"
#include "Particle.h"

Particle::Particle(SceneManager* manager, int image)
{
	mSceneManager = manager;
	mImgLight = image;
}

void Particle::Generate(VECTOR pos, float size, VECTOR dir, float speed, float lifeTime)
{
	mPos = pos;
	mDir = dir;
	mSize = size;
	mSpeed = speed;
	mLifeTime = lifeTime;
	mAngle = static_cast<float>(rand() % 628) / 100.0f;
}

void Particle::Update(void)
{
	//ˆÚ“®ˆ—
	mPos = VAdd(mPos, VScale(mDir, mSpeed * mSceneManager->GetDeltaTime()));

	//¶‘¶Šm”F
	if (mLifeTime > 0.0f)
	{
		mLifeTime -= mSceneManager->GetDeltaTime();
	}

	//‰ñ“]
	mAngle += mSceneManager->GetDeltaTime() * 3.0f;
}

void Particle::Draw(void)
{
	DrawBillboard3D(mPos, 0.5f, 0.5f, mSize, mAngle, mImgLight, true);
}

void Particle::Release(void)
{

}

float Particle::GetZLen(void)
{
	return mZLen;
}

void Particle::SetZLen(float len)
{
	mZLen = len;
}

VECTOR Particle::GetPos(void)
{
	return mPos;
}

bool Particle::IsAlive(void)
{
	return mLifeTime > 0.0f;
}
