#pragma once
#include "Transform.h"

class SceneManager;
class ParticleGenerator;
class SpriteAnimator;
class SpeechBalloon;
class PlayerShot;

class PlayerShip
{
public:

	//移動スピード
	static constexpr float SPEED_MOVE = 10.0f;

	//自機の回転量
	static constexpr float SPEED_ROT_DEG_Y = 10.0f;
	static constexpr float SPEED_ROT_DEG_X = 10.0f;

	//衝突判定：半径
	static constexpr float COLLISION_RADIUS = 20.0f;

	//弾の発射間隔
	static constexpr float TIME_DELAY_SHOT = 0.2f;

	//3ウェイショットの角度
	static constexpr float WAY_ANGLE = 5.0f;

	//状態
	enum class STATE
	{
		NONE,
		RUN,
		DESTROY
	};

	PlayerShip(SceneManager* manager);
	void Init(void);
	void Update(void);
	void UpdateRun(void);
	void UpdateDestroy(void);
	void Draw(void);
	void Release(void);

	//操作
	void ProcessTurn(void);
	void Turn(double deg, VECTOR axis);
	void ProcessShot(void);

	//自機の破壊
	void Destroy(void);

	//自機の状態が破壊か確認
	bool IsDestroy(void);

	Transform* GetTranceform(void);

	std::vector<PlayerShot*> GetShots(void);

	SpeechBalloon* GetSpeechBalloon(void);

private:

	SceneManager* mSceneManager;
	ParticleGenerator* mParticleGenerator;

	//モデル制御の基本情報
	Transform mTransform;

	//爆発エフェクト
	SpriteAnimator* mExplosion;

	//状態
	STATE mState;

	//吹き出し
	SpeechBalloon* mSpeechBalloon;

	//弾
	std::vector<PlayerShot*> mShots;

	//弾の発射間隔
	float mDelayShot;

	//加速スピード
	float mAddMove;
	float mPow;

	//状態遷移
	void ChangeState(STATE state);

	//弾を発射
	void CreateShot(double dir);
};

