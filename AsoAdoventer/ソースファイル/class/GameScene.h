#pragma once
#include <list>
#include <memory>
#include "BaseScene.h"
#include "../tmx/TmxObj.h"
#include "Obj/Obj.h"

class GameScene :
    public BaseScene
{
public:
	GameScene();
	~GameScene() override;
private:
	bool Init(void) override;
	uniqueScene UpDate(double delta, uniqueScene ownScene) override;
	void DrawOwnScreen(double delta) override;
	//bool Release(void) override;
	Scene GetSceneID(void)override { return Scene::Game; };

	std::list<std::unique_ptr<Obj>> objList_;
	TmxObj TmxObj_;
};

