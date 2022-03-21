#include <DxLib.h>
#include "GameScene.h"
#include "common/ImageMng.h"
#include "Obj/Player.h"
#include "Obj/Enemy.h"
#include "common/Vector2.h"

GameScene::GameScene()
{
	Init();
	DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{

}

bool GameScene::Init(void)
{
	TmxObj_.LoadTMX("./tmx/map.tmx");
	lpImageMng.GetID("image/bg2.png", "bg2");
	objList_.emplace_back(std::make_unique<Player>(CntType::Key, Vector2{ 320,0 }));
	objList_.emplace_back(std::make_unique<Enemy>(CntType::Key, Vector2{ 320,60 }));
	//objList_.emplace_back(std::make_unique<Player>(CntType::Pad));
	return false;
}

uniqueScene GameScene::UpDate(double delta, uniqueScene ownScene)
{
	for (const auto& obj : objList_)
	{
		obj->UpDate(TmxObj_.GetColList());
	}
	DrawOwnScreen(delta);
	return ownScene;
}

void GameScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(ScreenID_);
	ClsDrawScreen();

	auto mapData = TmxObj_.GetMapData();
	auto tileSize = TmxObj_.GetTileSize();
	auto area = TmxObj_.GetWorldArea();
	int graph;
	for (auto& layer : mapData)
	{
		for (int y = 0; y < area.y_; y++)
		{
			for (int x = 0; x < area.x_; x++)
			{
				//x,y‚Ì‚Æ‚±‚ë‚ÉÀ•W‚ð“n‚·B
				if (y * area.x_ + x < (int)(layer.second.size()))
				{
					graph = layer.second[x + y * area.x_] - TmxObj_.GetFirstGID();
					if (graph >= 0)
					{
						DrawGraph(x * tileSize.x_, y * tileSize.y_, lpImageMng.GetID("map")[graph], true);
					}
				}
			}
		}
	}
	for (const auto& obj : objList_)
	{
		obj->Draw();
	}
}