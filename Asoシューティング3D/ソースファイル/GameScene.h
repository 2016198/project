#pragma once
#include <vector>
#include "SceneBase.h"

class SceneManager;
class SpaceDome;
class Stage;
class PlayerShip;
class RockManager;

class GameScene : public SceneBase
{

public:

	//自機破棄時からのリスタート
	static constexpr float TIME_RESTART = 2.0f;

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	SpaceDome* mSpaceDome;
	Stage* mStage;
	PlayerShip* mPlayerShip;
	RockManager* mRockManager;

	float mStepShipDestroy;
};
