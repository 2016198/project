#pragma once
#include <DxLib.h>

class SceneManager;

class Unit
{
public:

	//アニメーションのスピード
	static constexpr float SPEED_ANIM = 40.0f;

	//徐々に回転する量
	static constexpr float SPEED_ROT = 5.0f;
	static constexpr float SPEED_ROT_RAT = SPEED_ROT * (DX_PI_F / 180.0f);

	Unit(SceneManager* manager);
	void Init(void);
	void UpDate(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAnglePos(void);

private:

	SceneManager* mSceneManager;

	//モデルのハンドルID
	int mModelId;

	//アニメーション用のハンドルID
	int mAnimWalk;
	
	//モデルの表示座標
	VECTOR mPos;

	//カメラ角度(rad)
	VECTOR mAngles;
	VECTOR mAnglesLocal;

	//アニメーションの総再生時間
	float mTimeTotalAnimWalk;

	//アニメーションのステップ時間
	float mStepAnim;
};