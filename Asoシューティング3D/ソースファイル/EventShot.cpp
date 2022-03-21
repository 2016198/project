#include "SpriteAnimator.h"
#include "SceneManager.h"
#include "Camera.h"
#include "EventShot.h"

EventShot::EventShot(SceneManager* manager, Transform* parent) : ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
	//着弾時のエフェクト
	mExplosion->Update();

	//弾が破壊されたならば、移動や衝突判定は行わない
	if (!mIsAlive)
	{
		return;
	}

	//移動処理
	Move();

	//3D座標から2D座標へ変換
	VECTOR pos2D = ConvWorldPosToScreenPos(mTransform.pos);
	if (pos2D.z <= 0.0f || pos2D.z >= 1.0f)
	{
		//位置を調整(カメラに映るように、後ろに下がってみたいな座標)
		VECTOR velocity = VScale(VScale(mDir, -1.0f), 100.0f);
		mTransform.pos = VAdd(mTransform.pos, velocity);
		mTransform.Update();

		//爆発エフェクト
		CreateExplosion();

		//カメラを揺らす
		mSceneManager->GetCamera()->ChangeMode(Camera::MODE::SHAKE);
	}

	//モデル制御の基本情報更新
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
