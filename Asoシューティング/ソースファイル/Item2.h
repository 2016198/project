//#pragma once
#include "Vector2.h"

//定数定義
#define ITEM_SIZE_X 32         //アイテムのサイズX
#define ITEM_SIZE_Y 32         //アイテムのサイズY
#define PAI 3.1415926535       //円周率

//メンバー変数
class Item2
{
private:
	int image;    //グラフィックハンドル
	int speed;    //アイテムの落下スピード
	bool alive;   //アイテムが出現しているかどうか
	int game;     //ゲームカウンター
	double en;    //回転速度
	Vector2 pos;  //座標成分(左上の座標)


public:  //メンバー関数
	bool Init(void);              //インスタンス生成時の処理
	void UpDate(void);            //インスタンス更新処理
	void Draw(void);              //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
	void SetItem(Vector2 ePos);   //敵の座標をアイテムにセットする	
	bool GetAlive(void);          //アイテムの今の状態(true:出現、false:非出現)
	Vector2 GetPos(void);         //アイテムの座標をあげる
	void DeleteItem(void);        //アイテムを消す
	bool GameInit(void);          //アイテムの初期化処理
};
