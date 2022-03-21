//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

class Lift
{
private:
	static constexpr int LIFT_MAX_SPEED = 2;	//リフトのスピードの最大値
	static constexpr int LIFT_ALIVE_TIME = 600;	//リフトの表示の最大値

	//リフトの状態
	enum class LIST_STYLE
	{
		NO,			//表示されていない
		YES,		//発射されている
		MAX
	};

	int mAnimCount;			//アニメーション変数
	int mImage[static_cast<int>(LIST_STYLE::MAX)];			//グラフィックハンドル
	Vector2 mPos;			//座標
	int mMoveSpeed;			//動く速さ
	Vector2 mSize;			//リフトの大きさ
	bool mAlive;			//リフトの表示されているか

public:
	Lift(void);				//コンストラスタ

	bool IsAlive(void);		//リフトが表示されているか
	Vector2 GetPos(void);	//座標を返す。

	bool Init(void);			//インスタンスの生成
	void UpDate(void);			//インスタンスの更新
	void Draw(void);			//インスタンスの描画
	bool Release(void);			//インスタンスの開放

	~Lift(void);				//デストラスタ
};
