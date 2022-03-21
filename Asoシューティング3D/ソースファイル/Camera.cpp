#include "DxLib.h"
#include "GameCommon.h"
#include "AsoUtility.h"
#include "Transform.h"
#include "Quaternion.h"
#include "SceneManager.h"
#include "Camera.h"

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
}

Camera::~Camera()
{
}

void Camera::Init()
{

}

void Camera::SetDefault(void)
{

	// カメラの初期設定
	mPos = DEFAULT_CAMERA_POS;
	mTargetPos = VAdd(mPos, RELATIVE_TARGET_POS);
	mCameraUp = { 0.0f, 1.0f, 0.0f };

	// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
	// mQuaRotは回転計算用で、
	// あくまで軸となるのは、カメラ座標と注視点とする
	mQuaRot = Quaternion();

}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{

	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(30.0f, 15000.0f);

	switch (mMode)
	{
	case Camera::MODE::FREE:
		SetBeforeDrawFree();
		break;
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	case Camera::MODE::FOLLOW_SPRING:
		SetBeforeDrawFollowSpring();
		break;
	case Camera::MODE::SHAKE:
		SetBeforeShake();
		break;
	}

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		mPos,
		mTargetPos,
		mCameraUp
	);

}

void Camera::SetBeforeDrawFree(void)
{
	//カメラの方向移動と回転(回転移動)

	//移動
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_W)) moveDir = AsoUtility::DIR_F;
	if (CheckHitKey(KEY_INPUT_S)) moveDir = AsoUtility::DIR_B;
	if (CheckHitKey(KEY_INPUT_A)) moveDir = AsoUtility::DIR_L;
	if (CheckHitKey(KEY_INPUT_D)) moveDir = AsoUtility::DIR_R;

	//回転
	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_UP))	   axisDeg.x += -1.0f; 
	if (CheckHitKey(KEY_INPUT_DOWN))   axisDeg.x +=  1.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))   axisDeg.y += -1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT))  axisDeg.y +=  1.0f;

	//回転
	if (!AsoUtility::EqualsVZero(axisDeg))
	{
		VECTOR axisRad;
		axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
		axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
		axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

		//クォタニオン((回転)の更新
		Quaternion axis = Quaternion::Euler(axisRad);
		mQuaRot = mQuaRot.Mult(axis);

		//注視点更新
		VECTOR localPos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
		mTargetPos = VAdd(mPos, localPos);

		//カメラの上方向
		mCameraUp = mQuaRot.GetUp();

	}

	//移動
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		float speed = 30.0f;

		MATRIX mat = mQuaRot.ToMatrix();

		//移動させたい方向(ベクトル)を求めたい
		VECTOR dir = VNorm(VTransform(moveDir, mat));

		//移動量を検出
		VECTOR movePow = VScale(dir, speed);

		//カメラの位置
		mPos = VAdd(mPos, movePow);
		mTargetPos = VAdd(mTargetPos, movePow);
	}
}

void Camera::SetBeforeDrawFixedPoint(void)
{

}

void Camera::SetBeforeDrawFollow(void)
{
	//プレイヤー座標
	VECTOR shipPos = mShipTransform->pos;

	//プレイヤーの向き(回転)
	Quaternion shipRot = mShipTransform->quaRot;
	MATRIX shipMat = mShipTransform->matRot;

	//設定しなきゃいけない値(カメラ位置、注視点、カメラの上方向)
	//mPos = VAdd();
	//mTargetPos = VSub();
	//mCameraUp = VAdd

	//カメラ位置
	mPos = VAdd(shipPos, RELATIVE_CAMERA_FOLLOW);
	// → プレイヤーが正面を向いているときにしか対応できていない
	//		相対座標にプレイヤーの開店を加える必要がある

	//カメラ位置
	//---------------------------------------------------------------
	VECTOR relativeCameraPos;
	//行列計算
	relativeCameraPos = VTransform(RELATIVE_CAMERA_FOLLOW, shipMat);

	//クォータニオン
	relativeCameraPos = shipRot.PosAxis(RELATIVE_CAMERA_FOLLOW);

	mPos = VAdd(shipPos, relativeCameraPos);
	//---------------------------------------------------------------

	//注視点
	//---------------------------------------------------------------
	VECTOR relativeTargetPos;
	//行列計算
	relativeTargetPos = VTransform(RELATIVE_TARGET_POS, shipMat);

	//クォータニオン
	relativeTargetPos = shipRot.PosAxis(RELATIVE_TARGET_POS);

	mTargetPos = VAdd(mPos, relativeTargetPos);
	//---------------------------------------------------------------

	//カメラの上方向
	mCameraUp = VTransform(AsoUtility::DIR_U, shipMat);
	mCameraUp = shipRot.GetUp();
	mCameraUp = shipRot.PosAxis(AsoUtility::DIR_U);
}

void Camera::SetBeforeDrawFollowSpring(void)
{
	//プレイヤー座標
	VECTOR shipPos = mShipTransform->pos;

	//プレイヤーの向き(回転)
	Quaternion shipRot = mShipTransform->quaRot;
	MATRIX shipMat = mShipTransform->matRot;

	//カメラの相対座標
	VECTOR relativeCameraPos = shipRot.PosAxis(RELATIVE_CAMERA_SPRING);

	//バネ定数
	float dampening = 2.0 * sqrtf(POW_SPRING);

	float delta = mSceneManager->GetDeltaTime();

	//理想位置
	VECTOR idealPos = VAdd(shipPos, relativeCameraPos);

	//現在位置と理想位置の差分
	VECTOR diff = VSub(mPos, idealPos);

	//バネの力 = (-バネの強さ × バネの伸び) - (抵抗 × カメラの速度)
	VECTOR force;
	force = VScale(diff, -POW_SPRING);
	force = VSub(force, VScale(mVelocity, dampening));

	//カメラ速度を更新
	mVelocity = VAdd(mVelocity, VScale(force, delta));

	//カメラ位置の更新
	mPos = VAdd(mPos, VScale(mVelocity, delta));

	//注視点
	//---------------------------------------------------------------
	VECTOR relativeTargetPos;
	//行列計算
	relativeTargetPos = VTransform(RELATIVE_TARGET_POS, shipMat);

	//クォータニオン
	relativeTargetPos = shipRot.PosAxis(RELATIVE_TARGET_POS);

	mTargetPos = VAdd(mPos, relativeTargetPos);
	//---------------------------------------------------------------

	//カメラの上方向
	mCameraUp = VTransform(AsoUtility::DIR_U, shipMat);
	mCameraUp = shipRot.GetUp();
	mCameraUp = shipRot.PosAxis(AsoUtility::DIR_U);
}

void Camera::SetBeforeShake(void)
{
	mStepShake -= mSceneManager->GetDeltaTime();
	if (mStepShake < 0.0f)
	{
		//初期位置に戻す
		mPos = mDefaultPos;
		ChangeMode(MODE::FIXED_POINT);
		return;
	}

	//★往復運動
	//往復する幅 × sinf(time × 振動する速さ)
	//mPos = ???

	float pow = WIDTH_SHKAE * sinf(mStepShake * SPEED_SHKAE);
	mPos = VAdd(mPos, VScale(mShakeDir, pow));
}

void Camera::Draw()
{

}

void Camera::DrawDebug(void)
{

}

void Camera::DrawUI(void)
{

	// 操作説明
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "　【操作】", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　旋回：↑↓←→", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　加速：Ｂ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　発弾：Ｎ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　シーン遷移：Ｓｐａｃｅ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　1500m以上離れると", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "　ゲームオーバー", 0xffffff);

}

void Camera::Release(void)
{

}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}

VECTOR Camera::GetDir(void)
{
	return VNorm(VSub(mTargetPos, mPos));
}

void Camera::ChangeMode(MODE mode)//モード切り替の時に初期化する処理
{
	mMode = mode;
	SetDefault();
	switch (mMode)
	{
	case Camera::MODE::FREE:
		break;
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FOLLOW:
		break;
	case Camera::MODE::FOLLOW_SPRING:
		break;
	case Camera::MODE::SHAKE:
		mStepShake = TIME_SHKAE;
		//振動する方向
		mShakeDir = VNorm({ 1.0f, 1.0f, 0.0f });
		mDefaultPos = mPos;
		break;
	}
}

void Camera::SetShip(Transform* shipTransform)
{
	mShipTransform = shipTransform;
}
