#pragma once
#include "BaseScene.h"
class TitleScene:
	public BaseScene
{
public:
	TitleScene();
	~TitleScene() override;
private:
	bool Init(void) override;
	uniqueScene UpDate(double delta, uniqueScene ownScene) override;
	void DrawOwnScreen(double delta) override;
	//bool Release(void) override;
	Scene GetSceneID(void)override { return Scene::Title; };

	int x_, y_;
};

