#pragma once
#include <memory>
#include <list>
#include "ItemBox.h"

#define lpItemBoxPool ItemBoxPool::GetInstance()//シングルトーン

class ItemBoxPool
{

public:
	static ItemBoxPool& GetInstance()	//インスタンスの入手
	{
		static ItemBoxPool s_Instance;
		return s_Instance;
	}

	std::list<ItemBox*> itemBoxList_;	//使う分の要素
	std::list<ItemBox*> itemBoxPool_;	//予備の要素

	void Init(void);					//初期化処理
	void Generate(int pos, 
		ITEM type,
		unsigned int color);			//Poolから使用分だけもって来る
	void Get(Vector2 pos1, Vector2 pos2, bool full1, bool full2);	//描画処理
	void Get(Vector2 pos, bool full);								//描画処理
	void Draw(double delta);										//描画処理
	void Release(void);												//解放処理

private:
	
	static const int pool_count_ = 20;					//文字貯蔵庫の数

	std::string item_name[static_cast<int>(ITEM::MAX)]	//表示する文字
	{
		"方位磁石を手に入れた！",
		"金属探知機を手に入れた！",
		"磁石を手に入れた！",
		"ろうそくを手に入れた！",
		"アイテムがいっぱいなのであきらめた…"
	};

	int sound_;											//サウンドハンドル
};

