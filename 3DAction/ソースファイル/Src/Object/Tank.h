#pragma once

#include <DxLib.h>
#include <vector>
#include "Common/Transform.h"
#include "Stage.h"

class SceneManager;
class GravityManager;
class Collider;
class Wheel;
class BarrelAndBody;

class Tank
{

public:

	//スピード
	static constexpr float SPEED_MOVE = 5.0f;

	//回転量
	static constexpr double ROT_DEG = 1.0f;

	Tank(SceneManager* manager);
	void Init(void);
	void Update(void);
	void UpdatePlay(void);
	void Draw(void);
	void DrawDebug(void);
	void Release(void);

	//操作
	void ProcessMove(void);

	//重力
	void CalcGravityPow(void);

	Transform* GetTransform(void);

	//衝突判定に用いられるコライダ制御
	void AddCollider(Collider* collider);
	void ClearCollider(void);

private:

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	//移動スピード
	float mSpeed;

	//移動量
	VECTOR mMovePow;

	//移動後の座標
	VECTOR mMovedPos;

	//重力方向ベクトル
	VECTOR mGravityPow;

	//衝突判定に用いられるコライダ
	std::vector<Collider*> mColliders;

	//衝突チェック
	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	//タイヤの情報
	std::vector<Wheel*> mWheels;

	//台と砲台の情報
	BarrelAndBody* mBarrelAndBody;

	//衝突判定
	void Collision(void);
	void CollisionGravity(void);

	//タイヤの生成
	void MakeWhlle(VECTOR localPos, VECTOR localAddAxis, bool isLeft);

	//タイヤの更新
	void UpdateWhlle(void);

	//タイヤの描画
	void DrawWhlle(void);

	//台と砲台の生成
	void MakeBarrelAndBody(VECTOR localPos, VECTOR localAddAxis);

	//台と砲台の更新
	void UpdateBarrelAndBody(void);

	//台と砲台の描画
	void DrawBarrelAndBody(void);
};


