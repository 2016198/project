#pragma once
#include <vector>
#include <DxLib.h>
#include "Transform.h"
#include "Quaternion.h"

class SceneManager;

class Camera
{

public:

	// カメラの初期座標
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };

	//自機とカメラ位置との相対座標(完全追従)
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0f,25.0f,-80.0f };

	//自機とカメラ位置との相対座標(バネ付き)
	static constexpr VECTOR RELATIVE_CAMERA_SPRING = { 0.0f,50.0f,-40.0f };

	//カメラ位置と注視点との相対座標
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f,-100.0f,500.0f };

	//ばねの強さ
	static constexpr float POW_SPRING = 240.0f;

	//シェイク：時間
	static constexpr float TIME_SHKAE = 2.0f;

	//シェイク：幅
	static constexpr float WIDTH_SHKAE = 3.0f;

	//シェイク：スピード
	static constexpr float SPEED_SHKAE = 30.0f;

	//カメラの処理
	enum class MODE
	{
		NOME,			//なし
		FREE,			//自由モード
		FIXED_POINT,	//定点モード
		FOLLOW,			//追従モード
		FOLLOW_SPRING,	//バネ付き追従モード
		SHAKE			//カメラシェイク
	};
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFollow(void);
	void SetBeforeDrawFollowSpring(void);
	void SetBeforeShake(void);

	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

	//カメラモードの変更
	void ChangeMode(MODE mode);

	//自機の設定
	void SetShip(Transform* shipTransform);

private:

	SceneManager* mSceneManager;
	Transform* mShipTransform;

	//カメラモード
	MODE mMode;

	// カメラの位置
	VECTOR mPos;

	// カメラ角度
	Quaternion mQuaRot;

	// 注視点
	VECTOR mTargetPos;

	// カメラの上方向
	VECTOR mCameraUp;

	//速度
	VECTOR mVelocity;

	//シェイク用
	float mStepShake;
	VECTOR mDefaultPos;
	VECTOR mShakeDir;

};

