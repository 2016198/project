#pragma once
#include <memory>
#include <vector>
#include "../Vector2.h"
#include "../manager/MaterialManager.h"
#include "BaseScene.h"
#include "../game/Player.h"
#include "../game/item/Item.h"
#include "../game/Map.h"

class GameTwoScene:
	public BaseScene
{			
public:
	GameTwoScene(INPUT_TYPE type);		//コンストラクタ
	~GameTwoScene() override;			//デストラクタ

	bool Init(void) override;					//初期化処理
	SCENE_ID Update(double delta) override;		//更新処理
	int Draw(void) override;					//描画処理
	void Release(void) override;				//解放処理
	const int GetNum(void) override;			//値わたし
	const SCENE_ID GetScene(void) override;		//自分のシーンを渡す
		
private:
	std::vector<std::unique_ptr<Player>> playerPtr_;	//プレイヤーのインスタンス	
	std::vector<std::unique_ptr<Item>> itemPtr_;		//アイテムのインスタンス
	std::unique_ptr<Map> mapPtr_;						//マップのインスタンス

	int screenP_;										//プレイヤーのスクリーン
	int winPlayer_;										//勝ったプレイヤー
	bool rock[2];										//同じ処理を連続でしないようにロックする
	double delta_;										//デルタタイム

};

