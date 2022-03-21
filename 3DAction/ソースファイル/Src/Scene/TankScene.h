#pragma once
#include "SceneBase.h"

class SceneManager;
class Stage;
class SkyDome;
class Tank;

class TankScene : public SceneBase
{

public:

	TankScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawDebug(void);
	void Release(void) override;

private:

	Stage* mStage;
	SkyDome* mSkyDome;
	Tank* mTank;
};
