//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

//親のインスタンス
class GameScene;

class Shot
{
private:
	static constexpr int SHOT_MAX_LIFE = 30;	//弾のライフ最大値
	static constexpr int SHOT_MAX_SPEED = 15;	//弾のスピードの最大値

	GameScene* mParent;
	int mImage;			//弾の画像
	Vector2 mPos;		//弾の座標
	int mMoveSpeed;		//弾の速さ
	int mLife;			//弾のライフ
	
public:
	Shot(GameScene* parent);	//コンストラスタ

	void CreateShot(Vector2 targetPos, DIR targetDir);		//弾の座標と向きターゲットか受け取る
	bool IsAlive(void);										//弾が表示されているかどうか
	void Destroy(void);		  //画像を消す

	bool Init(void);		//インスタンスの生成
	Vector2 UpDate(void);	//インスタンスの更新
	void Draw(void);		//インスタンスの描画
	bool Release(void);		//インスタンスの開放

	~Shot(void);			//デストラスタ
};