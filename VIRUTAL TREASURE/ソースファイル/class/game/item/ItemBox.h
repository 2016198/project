#pragma once
#include "../item/Item.h"
#include "../../Vector2.h"

class ItemBox
{

public:

	static constexpr size_t ANIM_COUNT = 6U;					//画像のアニメーションの数

	void Generate(int point, ITEM type, unsigned int color);	//生成処理
	void Draw(double delta);									//描画処理

	ItemBox(std::vector<int> image);	//コンストラクタ
	~ItemBox();							//デストラクタ

	int IsGetItem(Vector2 pos1, Vector2 pos2);	//プレイヤーとアイテムがぶつかったか(かさなっているか)：ダブル
	int IsGetItem(Vector2 pos);					//プレイヤーとアイテムがぶつかったか(かさなっているか)：シングル
	void Distroy(double delta);					//破棄処理
	Vector2 GetDrawPos(void);					//座標の情報
	ITEM GetItemInfo(void);						//入手アイテムの情報

private:

	bool alive_ = false;		//現在の状態
	unsigned int color_;		//色コード
	double delta_;				//デルタタイル
	Vector2 pos_;				//描画座標
	ITEM type_;					//アイテムの種類
	std::vector<int> image_;	//グラフィックハンドル
	int fream_;					//画像のアニメーション変数
};

