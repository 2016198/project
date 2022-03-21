#include "SpriteAnimator.h"
#include "SceneManager.h"
#include "Camera.h"
#include "EventShot.h"

EventShot::EventShot(SceneManager* manager, Transform* parent) : ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
	//���e���̃G�t�F�N�g
	mExplosion->Update();

	//�e���j�󂳂ꂽ�Ȃ�΁A�ړ���Փ˔���͍s��Ȃ�
	if (!mIsAlive)
	{
		return;
	}

	//�ړ�����
	Move();

	//3D���W����2D���W�֕ϊ�
	VECTOR pos2D = ConvWorldPosToScreenPos(mTransform.pos);
	if (pos2D.z <= 0.0f || pos2D.z >= 1.0f)
	{
		//�ʒu�𒲐�(�J�����ɉf��悤�ɁA���ɉ������Ă݂����ȍ��W)
		VECTOR velocity = VScale(VScale(mDir, -1.0f), 100.0f);
		mTransform.pos = VAdd(mTransform.pos, velocity);
		mTransform.Update();

		//�����G�t�F�N�g
		CreateExplosion();

		//�J������h�炷
		mSceneManager->GetCamera()->ChangeMode(Camera::MODE::SHAKE);
	}

	//���f������̊�{���X�V
	mTransform.Update();
}

float EventShot::GetSpeed(void)
{
	return 20.0f;
}

float EventShot::GetTimeAlive(void)
{
	return 10.0f;
}
