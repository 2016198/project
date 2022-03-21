//#pragma once
#include "Player2.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Shot2.h"
#include "Eshot.h"
#include "Bg2.h"
#include "Blast2.h"
#include "Item2.h"
#include "LifeP.h"
#include "Score.h"
#include "main.h"

//定数の宣伝
#define SHOT_MAX 20     //弾の最大値
#define BLAST_MAX 6     //爆発の最大値
#define SHOT_TIME 2     //弾のステイタイム
#define FONT_MAX 50     //スコア表示の最大値

class GameScene
{
private:
	int gamecounter;              //ゲームが始まってからの時間
	int push;                     //スペースキーを押してからの時間
	int point;                    //得点
	bool getItem;                 //アイテムを手に入れたとき
	int itemCount;                //アイテムの効果継続時間
	int fontType;                 //得点の種類
	Vector2 shotAdd[SHOT_MAX];    //敵の座標 － プレイヤーの座標
	Vector2 shotAdd2[SHOT_MAX];   //敵の座標 － プレイヤーの座標(絶対値)
	Vector2 playerInit;           //プレイヤーの初期化
	Vector2 pPos;                 //プレイヤーの座標
	Vector2 ePos;                 //敵の座標	
	Vector2 bPos;                 //bossの座標
	Vector2 iPos;                 //アイテムの座標
	Vector2 sPos[SHOT_MAX][3];    //自機の弾の座標
	Vector2 SPos[SHOT_MAX];       //敵の弾の座標
	Player2 player2;
	Enemy2 enemy2;
	Boss boss;
	Item2 item2;
	Shot2 shot2[SHOT_MAX][3];
	Blast2 blast2[BLAST_MAX];
	Bg2 bg2;
	LifeP lifeP;
	Score score[FONT_MAX];
	Eshot eshot[SHOT_MAX];

public:
	bool Init(void);              //インスタンスの生成時処理
	void UpDate(void);            //インスタンスの更新処理
	void Draw(void);              //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
	bool GameInit(void);          //ゲームの初期化処理
	int Score(void);              //ゲームのスコアをもらって返す。
	bool GameClear(void);         //ゲームクリアー処理
	bool GameOver(void);          //ゲームオーバーシーンに移る処理
};
