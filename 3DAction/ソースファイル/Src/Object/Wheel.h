#pragma once
#include "Common/Transform.h"

class SceneManager;

class Wheel
{
public:

	//大きさ
	static constexpr float SCALE = 2.0f;

	// タイヤローカル稼働量(deg)
	static constexpr float ANGLE_POW_WHEEL = 0.1f;

	Wheel(SceneManager* manager,
		Transform* transformParent,
		VECTOR localPos,
		VECTOR localAddAxis,
		bool isLeft);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SyncParent(Transform* transform, VECTOR addAxis);

private:

	SceneManager* mSceneManager;

	// モデル制御の基本情報(親)
	Transform* mTransformParent;

	// モデル制御の基本情報(タイヤ)
	Transform mTransformWheel;

	// 台からの相対座標
	VECTOR mLocalPos;

	// 追加のローカル回転
	VECTOR mLocalAddAxis;

	// 更に追加のタイヤローカル回転
	VECTOR mLocalAddAxisWheel;

	// タイヤローカル稼働量(deg)
	float mAnglePowWheel;

	//タイヤの位置
	int mWheel[2];
};

