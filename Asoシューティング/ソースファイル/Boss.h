//#pragma once
#include "Vector2.h"

//定数の定義
#define BOSS_SIZE_X 64
#define BOSS_SIZE_Y 64

class Boss
{
private:							   //メンバー変数
	int life;                          //bossの残機
	int bossLR;                        //左か右か
	int ySpeed;                        //移動量Y
	int Image[3];                      //グラフィックハンドル
	int xSpeed;                        //移動量X
	int gamecounter;                   //ゲームカウンター
	bool Alive;                        //(敵がtrueの時)生きてる証拠だよ
	bool hunt;                         //bossが倒されたかどうか
	int huntTime;                      //倒されてからの時間
	int stayTime;                      //待ち時間
	bool shotFlag;                     //弾を撃ったかどうか
	Vector2 Pos;                       //座標

public:								     //メンバー関数
	bool Init(void);                     //インスタンスの生成時の処理
	void UpDate(void);                   //インスタンスの更新処理
	void Draw(void);                     //インスタンスの描画処理
	bool Release(void);                  //インスタンスの開放処理
	void InBoss(void);                   //Bossの登場
	int IsStay(void);                    //bossが無敵かどうか
	bool IsHit(void);                    //Bossに当たった処理
	void DeleteBoss(void);               //bossを消す
	bool GetAlive(void);                 //bossが生きてる証拠だよ
	bool IsHunt(void);                   //bossが倒されたか
	bool Death(void);                    //ゲームクリア処理
	Vector2 GetPos(void);                //bossの座標を返す
	bool GameInit(void);                 //bossの初期化処理
};
