//#pragma once
#include "Vector2.h"

//定数定義
#define BLAST_SIZE_X 96       //爆発のサイズX
#define BLAST_SIZE_Y 96       //爆発のサイズY
#define BLAST_COUNT_X 6       //アニメの数X
#define BLAST_COUNT_Y 4       //アニメの数Y

class Blast2
{
private:
	int Image[BLAST_COUNT_X * BLAST_COUNT_Y];       //グラフィックハンドル
	int PosX;                                       //X座標
	int PosY;                                       //Y座標
	bool Alive;                                     //(敵がtrueの時)生きてる証拠だよ
	int No;                                         //ブラストののアニメーション
	Vector2 Pos;                                    //座標成分

public:
	bool Init(void);                 //インスタンス生成時の処理
	void UpDate(void);               //インスタンスの更新処理
	void Setup(Vector2 Pos);         //インスタンスを利用した処理
	void Draw(void);                 //インスタンスの描画処理
	bool Release(void);              //インスタンスの開放処理
	bool GetAlive(void);             //爆発のアニメーション表示
	bool GameInit(void);             //爆発の初期化処理
};