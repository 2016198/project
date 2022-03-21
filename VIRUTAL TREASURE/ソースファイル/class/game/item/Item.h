#pragma once
#include <string>
#include <map>
#include <vector>
#include "../../Vector2.h"

//アイテムの種類
enum class ITEM
{
	COMPASS,		//方位磁石
	DETECTOR,		//金属探知機
	MAGNET,			//磁石
	CANDLE,			//ろうそく
	NONE,			//なし
	MAX
};

enum class CANDLE		//ろうそく使用イベント
{
	COME_HERE,			//こっち来て
	RANDOM_POS,			//どっかへいく
	NONE,				//はずれ
	CHANGE_POS,			//場所交換
	ITEM_GET,			//アイテム入手
	NO_ITEM,			//アイテムがない
	MOVE_PLAS,			//移動量が2倍になる	
	MOVE_MINUS,			//移動量が1になる
	NO_USE,				//未使用状態
};

class Item
{
public:
	bool Init(void);													//初期化処理
	bool Update(double delta, double angle, Vector2 dis);				//更新処理
	void Draw(int num);													//描画処理
	void Release(void);													//解放処理

	Item();						//コンストラクタ
	~Item();					//デストラクタ

	void SetInfo(Vector2 pos, ITEM itemS, ITEM itemU, Vector2 pos2);	//座標と使用されたアイテム情報の入手
	double GetLife(void);												//表示時間の取得
	bool setMode_;														//ワープモード。
	CANDLE candle;														//ろうそくの状態

private:

	struct Info
	{
		Vector2 pos;			//使用した座標
		ITEM useItem;			//使われたアイテム
		ITEM selectItem;		//選択アイテム
		double angle;			//画像の傾き
		double life;			//アイテムの表示時間
		bool search;			//近くに目的地があるか
	};

	Info info_;										//アイテムの情報
	double delta_;									//デルタタイム
	double distance_[2];							//目的地までの距離
	int font_;										//フォントハンドル
	Vector2 movePos_;								//移動する座標
	Vector2 drawPos_;								//描画座標
	Vector2 movePow_;								//移動量

	static constexpr double MOVE = 10.0;			//一回の移動量
							
	std::map<std::string, std::vector<std::string>> fileName_;			//ファイルのディレクトリ
	std::vector<int> image_;											//グラフィックハンドル
	std::vector<int> sound_;											//効果音ハンドル
};