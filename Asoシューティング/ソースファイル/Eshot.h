//#pragma once
#include "Vector2.h"

//定数定義
#define E_SHOT_SIZE_X 32        //弾の横サイズ
#define E_SHOT_SIZE_Y 32        //弾の縦サイズ

class Eshot
{
private:
	int Image;        //グラフィックハンドル
	bool Alive;       //生きてる証拠だよ
	int speed;        //弾の速さ
	Vector2 pos;      //座標成分
public:			      //メンバー関数
	bool Init(void);              //インスタンス生成時の処理
	void Setup(Vector2 pPos);     //インスタンスを利用する処理
	void UpDate(Vector2 Pos);     //インスタンスの更新処理
	void Draw(void);              //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
	Vector2 GetPos(void);         //座標を与える
	bool GetAlive(void);          //弾を撃ってるか
	void DeleteShot(void);        //弾を打つ
	bool GameInit(void);          //弾の初期化処理
};
