//#pragma once
#include "Vector2.h"

//定数の定義
#define SCORE_POINT 100           //敵の得点
#define ITEM_POINT 300            //アイテムの得点
#define BOSS_POINT 500            //ボスの得点
#define SCORE_MAX 9999            //敵の得点の最大値

class Score  //メンバー変数
{
private:
	int posx;                     //X座標
	int posy;                     //Y座標
	int score;                    //スコアの表示
	int highscore;                //ハイスコアの表示
	int font;                     //スコアのフォント幅
	int fonthigh;                 //ハイスコアのフォント幅
	bool alive;                   //true:表示 false:非表示
	int fontCount;                //フォントの表示時間

public:		//メンバー関数
	bool Init(void);              //インスタンスの生成時処理
	void UpDate(void);            //インスタンスの更新処理
	void PointDraw(int type);     //インスタンスの描画処理
	void ScoreDraw(void);         //得点の描画処理
	void SetUp(Vector2 pos);      //敵のところにスコアを表示
	bool GetAlive(void);          //フォントが表示されているかどうかを返す
	void AddScore(int type);      //スコアを加算する
	int GetScore(void);           //スコアを返す
	bool GameInit(void);          //スコアの初期化処理
};
