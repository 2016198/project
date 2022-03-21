#pragma once
#include "Vector2.h"
#include "GameCommon.h"
class GameScene;

//定数定義
#define LIFE_ANIM_COUNT 4 //ライフバーのアニメの数

class LifeBar {
private:
	Vector2 mPos;		  //座標成分
	GameScene* mParent;   //親のインスタンスポインタ変数
	Vector2 mSizeOffset;  //キャラクターのオフセットサイズ
	Vector2 mOffset;      //オフセットの座標
	int mType;            //キャラクターの種類

public:
	bool init(GameScene* parent, int type);     //インスタンスの生成
	void UpDate(Vector2 pos);		  //インスタンスの更新
	void Draw(int life, Vector2 pos); //インスタンスの描画
	bool Release(void);               //インスタンスの開放
};
