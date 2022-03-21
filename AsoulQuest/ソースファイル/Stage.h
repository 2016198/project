//#pragma once
#include "Vector2.h"
#include "GameCommon.h"

//定数定義
#define CHIP_IMAGE_MAX 81  //まっぷのチップの数

//マップ管理用
enum class MAP_ID
{
	NORMAL,
	MAZE
};

class Stage
{
private:                    //メンバー変数
	int mScreenSizeX;              //画面のXサイズ
	int mScreenSizeY;              //画面のYサイズ
	int mChipImage[CHIP_IMAGE_MAX];         //グラフィックハンドル

	//マップ管理用
	MAP_ID mMapID;							//現在のマップの情報
	int mMapX;								//現在のマップのサイズX
	int mMapY;								//現在のマップのサイズY
	int mMap[MAP_X][MAP_Y];					//現在のマップデータ

public:                     //メンバー関数
	bool Init(int ScreenSizeX, int ScreenSizeY);        //インスタンスの初期化処理
	void UpDate(void);      //インスタンスの更新処理
	void Draw(Vector2 Pos);               //インスタンスの描画処理
	bool Release(void);            //インスタンスの開放処理

	void SetMap(MAP_ID mapID);		//指定されたマップ情報をマップ配列に格納する
	int GetMapChip(Vector2 pos);    //今いるマップの番号を返す
};
