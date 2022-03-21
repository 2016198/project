#pragma once
#include <DxLib.h>
class SceneManager;
class Unit;

class RollBall
{
public:
	RollBall(SceneManager* manager, Unit* unit);
	void Init(void);
	void UpDate(void);
	void Draw(void);

	VECTOR GetPos();

private:
	SceneManager* mSceneManager;
	Unit* mUnit;
	VECTOR mPos;
	float mStep;
};

