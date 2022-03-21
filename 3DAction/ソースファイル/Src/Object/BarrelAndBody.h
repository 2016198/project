#pragma once
#include "Common/Transform.h"

class SceneManager;
class TankShot;

class BarrelAndBody
{
public:

	//大きさ
	static constexpr float SCALE = 2.0f;

	// 砲台ローカル稼働量(deg)
	static constexpr float ANGLE_POW_BARREL = 0.05f;

	// 台ローカル稼働量(deg)
	static constexpr float ANGLE_POW_BODY = 0.05f;


	BarrelAndBody(SceneManager* manager,
		Transform* transformParent,
		VECTOR localPos,
		VECTOR localAddAxis);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SyncParent(Transform* transform, VECTOR addAxis);

private:

	SceneManager* mSceneManager;

	//弾の基本情報
	std::vector<TankShot*> mTankShots;

	// モデル制御の基本情報(親)
	Transform* mTransformParent;

	// モデル制御の基本情報(台)
	Transform mTransformBody;

	// モデル制御の基本情報(砲台)
	Transform mTransformBarrel;

	// 台からの相対座標
	VECTOR mLocalPos;

	// 追加のローカル回転
	VECTOR mLocalAddAxis;

	// 更に追加の台ローカル回転
	VECTOR mLocalAddAxisBody;

	// 更に追加の砲台ローカル回転
	VECTOR mLocalAddAxisBarrel;

	// 台ローカル稼働量(deg)
	float mAnglePowBody;

	// 砲台ローカル稼働量(deg)
	float mAnglePowBarrel;

	void CreateShot(void);
};

