#pragma once
#include <vector>
#include "Transform.h"
#include "SpriteAnimator.h"

class SceneManager;
class PlayerShip;
class EventShot;
class Turret;

class BossShip
{
public:

	//移動スピード
	static constexpr float SPEED_MOVE = 4.0f;

	//着弾後のイベントの終了時間
	static constexpr float TIME_EVENT = 4.0f;

	//破壊演出時間
	static constexpr float TIME_DESTROY = 4.0f;

	//爆破エフェクト間隔
	static constexpr float TIME_BLAST = 1.0f;

	enum class STATE
	{
		NONE,
		EVENT,
		BATTLE,
		DESTROY,
		END
	};

	BossShip(SceneManager* sceneManager, PlayerShip* playerShip);
	void Init(void);
	void Update(void);
	void UpdateTurret(void);
	void Draw(void);
	void DrawTurret(void);
	void Release(void);

	Transform* GetTranceform(void);

	std::vector<Turret*> GetTurrets(void);

	//ボスの破壊
	void Destroy(void);

	//ボスの状態が破壊か確認
	bool IsAlive(void);	

private:

	SceneManager* mSceneManager;
	PlayerShip* mPlayerShip;
	// 自身の爆発
	std::vector<SpriteAnimator*> mExplosion;

	//イベント用の弾
	EventShot* mEventShot;

	//モデル制御の基本情報
	Transform mTransform;

	//状態
	STATE mState;

	//タレット
	std::vector<Turret*> mTurrets;

	//イベント時間の管理
	float mStepEvent;

	//破壊演出時間の管理
	float mStepDestroy;

	//爆破エフェクトの管理
	float mStepBlast;

	//状態遷移
	void ChangeState(STATE state);

	//タレットの作成
	void MakeTurret(VECTOR localPos, VECTOR localAddAxis);
};

