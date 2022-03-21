//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

//定数定義
#define CHIP_IMAGE_MAX 13  //マップのチップの数

//マップ管理用
enum class MAP_ID
{
	NORMAL,
	FIRE
};

class Stage
{
private:							//メンバー変数
	Vector2 mOffset;				//マップのオフセット座標
	int mChipImage[CHIP_IMAGE_MAX];         //グラフィックハンドル
	MAP_ID mMapID;							//マップの情報
	Vector2 mMapSize;						//マップのサイズ
	int mMap[MAP_Y][MAP_X];					//マップの格納情報

public:
	Stage(void);				//コンストラスタ
	bool Init(void);			//インスタンスの生成
	Vector2 UpDate(void);		//インスタンスの更新
	void Draw(void);			//インスタンスの描画
	bool Release(void);			//インスタンスの開放
	~Stage(void);				//デスコンストラスタ

	void SetMap(MAP_ID mapID);	//マップの生成
	int GetMapChip(Vector2 pos);//マップの情報を返す
};
