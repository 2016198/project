#pragma once
#include <DxLib.h>

class SceneManager;

class TankShot
{
public:

	TankShot(SceneManager* manager);
	void Generate(VECTOR pos, VECTOR forward, unsigned int color);
	void Update(void);
	void Draw(void);

	//生存確認
	bool IsAlive(void);

private:

	//弾の速度
	static constexpr float SPEED = 10.0f;

	//弾の生存
	static constexpr float LIFE = 5.0f;

	SceneManager* mSceneManager;

	//色コード
	unsigned int mColor;

	//生存時間
	float mLife;

	//弾の座標
	VECTOR mPos;

	//移動方向
	VECTOR mMovePow;
};

