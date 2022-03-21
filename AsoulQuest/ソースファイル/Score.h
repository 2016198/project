//#pragma once
#include "Vector2.h"
#include "GameCommon.h"

class Score
{
private:
	Vector2 mPos;				     //座標成分
	Vector2 mOffset;                 //オフセット座標成分
	int mLife;                       //スコアの表示時間
	int mType;                       //スコアの種類
	int mFont;                       //スコアをずらす
	unsigned int mColor;             //色のアドレス変数
	const int mPoint[ENEMY_TYPE_MAX + 1] //敵ごとの点数　※一番小さい点数は敵に弾を当てた時のポイント
	{
		20,30,40,50,60,500,10
	};
	int mEnemyLife;                   //敵の生存確認
public:
	bool Init(void);	//インスタンスの生成
	void UpDate(void);	//インスタンスの更新
	void Draw(Vector2 pos);	//インスタンスの描画
	bool Release(void); //インスタンスの開放
	int AddScore(int enemyType, Vector2 targetPos, int enemyLife);//スコアの加算
	bool IsAlive(void);       //スコアが表示されている
};
