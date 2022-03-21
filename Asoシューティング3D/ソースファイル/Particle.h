#pragma once

class SceneManager;

class Particle
{
public:

	Particle(SceneManager* manager, int image);
	void Generate(VECTOR pos, float size, VECTOR dir, float speed, float life);
	void Update(void);
	void Draw(void);
	void Release(void);

	float GetZLen(void);
	void SetZLen(float len);
	VECTOR GetPos(void);

	bool IsAlive(void);

private:

	SceneManager* mSceneManager;

	//グラフィックハンドル
	int mImgLight;

	//座標
	VECTOR mPos;

	//移動方向
	VECTOR mDir;

	//大きさ
	float mSize;

	//移動速度
	float mSpeed;

	//生存時間
	float mLifeTime;

	//Zソート
	float mZLen;

	//角度
	float mAngle;
};

