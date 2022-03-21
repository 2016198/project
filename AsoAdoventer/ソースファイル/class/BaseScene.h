#pragma once
#include <memory>
#include"common/Vector2.h"

class BaseScene;

using uniqueScene = std::unique_ptr<BaseScene>;

enum class Scene
{
	Transition,
	Title,
	Game,
	Max
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	//virtual bool Init(void) = 0;
	virtual bool Init(void) = 0;
	virtual uniqueScene UpDate(double delta, uniqueScene ownScene) = 0;
	virtual void Draw(double delta);
	virtual void DrawOwnScreen(double delta) = 0;
	virtual Scene GetSceneID(void) = 0;
	//virtual bool Release(void) = 0;
private:
	int x_, y_;

protected:
	int ScreenID_;
	Vector2 ScreenSize_;
};

