//#pragma once
#include "Vector2.h"

//定数定義
#define PLAYER_SIZE_X 32      //自機の横サイズ
#define PLAYER_SIZE_Y 32      //自機の縦サイズ
#define PLAYER_LIFE 3         //自機の残機数

class Player2
{
private:              //メンバー変数
	//int pos_x;		  //X座標
	//int pos_y;		  //Y座標
	int Image;        //グラフィックハンドル (０:自機、１:ハート)
	int Speed;        //速さ
	bool Alive;       //生きてる証拠だよ
	bool shotFlag;    //プレイヤーが球を発射するとtrueになる変数
	int life;         //プレイヤーの残機
	Vector2 pos;      //プレイヤー座標

public:               //メンバー関数
	bool Init(Vector2 Init);          //インスタンスの生成時の処理
	void Update(void);                //インスタンスの更新処理
	void Draw(void);                  //インスタンスの描画処理 
	void Drawen(void);                //円の描画処理
	bool Release(void);               //インスタンスの開放処理
	bool IsShot(void);                //弾を発射していればtrueを返す
	Vector2 GetPos(void);             //プレイヤーの座標を返す
	void DeletePlayer(void);          //プレイヤーを消す
	bool GetAlive(void);              //プレイヤーが生きてる証拠だよ
	bool Death(void);                 //プレイヤーの残機が0になったとき
	int GetLife(void);                //プレイヤーのライフを返す
	bool GameInit(Vector2 Init);      //プレイヤーの初期化処理
};
