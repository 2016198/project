//#pragma once
#include "Vector2.h"

//定数定義
#define ENEMY_SIZE_X 32       //敵の横サイズ
#define ENEMY_SIZE_Y 32       //敵の縦サイズ

class Enemy2
{
private:							   //メンバー変数	
	int Image;                         //グラフィックハンドル
	//int PosX;                          //X座標
	//int PosY;                          //Y座標
	int Speed;                         //移動量
	int gamecounter;                   //ゲームカウンター
	bool Alive;                        //(敵がtrueの時)生きてる証拠だよ
	bool shotFlag;                     //弾を撃ったかどうか
	Vector2 Pos;                       //座標

public:
	bool Init(void);                         //インスタンスの生成時の処理
	void UpDate(bool bossMode,bool bossHunt);//インスタンスの更新処理
	void Draw(void);                         //インスタンスの描画処理
	bool Release(void);                      //インスタンスの開放処理
	Vector2 GetPos(void);                    //弾の座標を与えます
	bool IsShot(void);                       //敵が撃ったかどうか
	void DeleteEnemy(void);                  //敵を消す
	bool GetAlive(void);                     //敵が生きてる証拠だよ
	bool GameInit(void);                     //敵の初期化処理
};