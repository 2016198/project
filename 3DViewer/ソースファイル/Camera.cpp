#include "AsoUtility.h"
#include "Unit.h"
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	//カメラの座標の初期化
	mPos = { 0.0f, 300.0f, -500.0f };

	//カメラの角度
	mAngles = {
		//30.0f * (DX_PI_F / 180.0f),
		static_cast<float>(AsoUtility::Deg2RadD(30.0f)),
		static_cast<float>(AsoUtility::Deg2RadD(0.0f)),
		static_cast<float>(AsoUtility::Deg2RadD(0.0f))
	};
}

void Camera::Updata(void)
{

	float movePow = 5.0f;
	float moveHPow = movePow / 2.0f;
	//キーボード操作でカメラ位置を移動します。

	float rad = 0.0f;

	////前後移動
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	//ワールド座標の前方(Z+)
	//	//Zの正方向
	//	//mPos.z += movePow;

	//	//カメラの前方確認s
	//	rad = AsoUtility::Deg2RadD(0.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	//ワールド座標の前方(Z-)
	//	//Zの負方向
	//	//mPos.z -= movePow;

	//	//カメラの後方確認
	//	rad = AsoUtility::Deg2RadD(180.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	////横移動
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	//Xの正方向
	//	//mPos.x += movePow;

	//	//カメラの左移動
	//	rad = AsoUtility::Deg2RadD(-90.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	//Yの負方向
	//	//mPos.x -= movePow;

	//	//カメラの右移動
	//	rad = AsoUtility::Deg2RadD(90.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	//垂直移動
	//if (CheckHitKey(KEY_INPUT_X))
	//{
	//	//Xの正方向
	//	mPos.y += movePow;
	//}

	//if (CheckHitKey(KEY_INPUT_Z))
	//{
	//	//Yの負方向
	//	mPos.y -= movePow;
	//}

	//キーボード操作でカメラ角度を変更
	//横回転
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//右回転
		mAngles.y += AsoUtility::Deg2RadD(1.0f);
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//左回転
		mAngles.y -= AsoUtility::Deg2RadD(1.0f);
	}

	//見上げる、見下ろすカメラの回転
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	//見上げる
	//	mAngles.x += AsoUtility::Deg2RadD(1.0f);
	//}

	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	//見下ろす
	//	mAngles.x -= AsoUtility::Deg2RadD(1.0f);
	//}
}

void Camera::SetBeforeDraw(void)
{

	if (mUnit == nullptr)
	{
		DxLib::SetCameraPositionAndAngle(
			mPos,
			mAngles.x,
			mAngles.y,
			mAngles.z
		);
	}
	else
	{

		//注意点
		float dirX;
		float dirZ;
		VECTOR dir;
		VECTOR movePow;
		
		//注視点の移動
		//----------------------------------------
		//カメラの向いている方向
		dirX = sinf(mAngles.y);
		dirZ = cosf(mAngles.y);

		//正規化
		dir = VNorm({ dirX, 0.0f, dirZ });

		//方向から移動量を算出
		movePow = VScale(dir, DIS_TARGET_TO_UNIT);

		VECTOR uPos = mUnit->GetPos();
		mTargetPos = VAdd(uPos, movePow);
		//mTargetPos.y = 0.0f;
		//----------------------------------------------

		//カメラ位置の移動
		// -----------------------------------------------
		//カメラの向いている方向の反対方向
		float revRad = AsoUtility::Deg2RadF(180.0f);
		dirX = sinf(mAngles.y + revRad);
		dirZ = cosf(mAngles.y + revRad);

		//正規化
		dir = VNorm({ dirX, 0.0f, dirZ });

		//方向から移動量を算出
		movePow = VScale(dir, DIS_TARGET_TO_CAMERA);
		//高さ
		movePow.y = HEGHT;
		//注視点からカメラの移動量を足せばいい
		mPos = VAdd(mTargetPos, movePow);
		
		

		SetCameraPositionAndTargetAndUpVec(
			mPos,
			mTargetPos,
			{ 0.0f,1.0f,0.0f }
		);
	}
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

void Camera::GetUnit(Unit* unit)
{
	mUnit = unit;
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetAnglePos(void)
{
	return mAngles;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}
