#pragma once
#include <vector>
#include "SceneBase.h"

class SceneManager;
class BossShip;
class SpaceDome;
class RockManager;
class PlayerShip;

class BattleScene :
	public SceneBase
{

public:

	//自機破棄時からのリスタート
	static constexpr float TIME_RESTART = 2.0f;

	BattleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	int mEndImg;

	RockManager* mRockManager;

	PlayerShip* mPlayerShip;

	BossShip* mBossShip;
	SpaceDome* mSpaceDome;

	float mStepShipDestroy;
};

