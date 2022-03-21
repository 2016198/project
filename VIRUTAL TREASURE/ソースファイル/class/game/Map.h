#pragma once
#include <string>
#include <vector>
#include "../Vector2.h"

//マップの情報
static constexpr int MAP_COUNT = 6;								//一列の数
static constexpr int MAP_SIZE = MAP_COUNT * MAP_COUNT;			//マスのサイズ
static constexpr int OFFSET_X = 150;							//隙間X
static constexpr int OFFSET_Y = 70;								//隙間Y
static constexpr int OFFSET_SIZE = 75;							//間隔
static constexpr int POINT_COUNT = 5;							//地図の一列の数
static constexpr int POINT_SIZE = POINT_COUNT * POINT_COUNT;	//地図の数

class Map
{	
public:
	//二人モード
	bool Init(int point1, int point2);	//初期化処理
	void Draw(int point1, int point2);	//描画処理

	//ソロモード
	bool Init(int point);				//初期化処理
	void Draw(int point);				//描画処理

	void Release(void);					//解放処理

	void SetMap(int map, int num);		//マップの更新

	Map();								//コンストラクタ
	~Map();								//デストラクタ

private:
	std::vector<int> map_;				//目的地
	int image_[POINT_SIZE];				//グラフィックハンドル
	unsigned int color_;				//色コード
	std::string fileNameG_[POINT_SIZE];	//ファイルの名前
	Vector2 drawPos_;					//描画座標
};

