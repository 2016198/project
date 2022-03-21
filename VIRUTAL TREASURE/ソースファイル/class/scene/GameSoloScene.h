#pragma once
#include <memory>
#include "../Vector2.h"
#include <list>
#include "../manager/MaterialManager.h"
#include "BaseScene.h"
#include "../game/Player.h"
#include "../game/item/Item.h"
#include "../game/Map.h"
#include "../game/Fire.h"

class GameSoloScene :
	public BaseScene
{
public:
	GameSoloScene(INPUT_TYPE type);		//コンストラクタ
	~GameSoloScene() override;			//デストラクタ

	bool Init(void) override;					//初期化処理
	SCENE_ID Update(double delta) override;		//更新処理
	int Draw(void) override;					//描画処理
	void Release(void) override;				//解放処理
	const int GetNum(void) override;			//値わたし
	const SCENE_ID GetScene(void) override;		//自分のシーンを渡す

private:
	std::unique_ptr<Player> playerPtr_;				//プレイヤーのインスタンス	
	std::unique_ptr<Item> itemPtr_;					//アイテムのインスタンス
	std::unique_ptr<Map> mapPtr_;					//マップのインスタンス
	std::list<std::unique_ptr<Fire>> firePtrPool_;	//予備の炎のインスタンス
	std::list<std::unique_ptr<Fire>> firePtrList_;	//使用する炎のインスタンス

	int screenP_;									//プレイヤーのスクリーン
	bool rock;										//同じ処理を連続でしないようにロックする
	double delta_;									//デルタタイム
	int makeFire_;									//ファイアの生成確立
};

