#pragma once
#include "SceneBase.h"

class SceneManager;
class Stage;
class Unit;
class Enemy;
class RollBall;
class ShotBall;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawDebug(void);
	void Release(void) override;

private:

	Stage* mStage;
	Unit* mUnit;
	Enemy* mEnemy;
	RollBall* mRollBall;
	ShotBall* mShotBall[50];

	bool mIsShot[2];
};
