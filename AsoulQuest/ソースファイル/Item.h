#pragma once
#include "Vector2.h"
#include "GameCommon.h"

//定数定義
#define ITEM_IMAGE_COUNT 4     //アイテムの種類の数
class GameScene;			   //親のインスタンス

class Item
{
private:
	Vector2 mPos;			//座標成分
	GameScene *mParent;		//親のインスタンス
	int mImage[2];			//グラフィックハンドル
	int mAnimCnt;			//アニメカウント
	bool mAlive;			//出現しているかどうか
	Vector2 mOffset;        //オフセットの座標
	Vector2 mSizeOffset;    //キャラクターのオフセットサイズ
	Vector2 mSize;          //キャラクターの画像のサイズ
public:
	bool Init(GameScene* parent);		//インスタンスの初期化処理
	void UpDate(Vector2 pos);		//インスタンスの更新処理
	void Draw(void);		//インスタンスの描画処理
	bool Release(void);		//インスタンスの開放処理
	void SetItem(Vector2 targetPos); //アイテムのセット
	bool IsAlive(void);		//アイテムが出現してるかどうか
	void Destroy(void); //アイテムが出現してるかどうか
	Vector2 GetSize(void);  //画像のサイズを返す
	Vector2 GetPos(void);   //座標を返す
};
