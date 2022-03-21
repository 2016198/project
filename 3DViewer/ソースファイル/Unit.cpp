#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"
#include "Unit.h"

Unit::Unit(SceneManager* manager)
{
	mSceneManager = manager;
}

void Unit::Init(void)
{
	mModelId = MV1LoadModel("Model/Walking.mv1");
	mPos = { 0.0f,0.0f,0.0f };
	mAngles = { 0.0f,0.0f,0.0f };
	mAnglesLocal = { 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f };

	//モデルの座標を設定
	MV1SetPosition(mModelId, mPos);

	//モデルの角度を設定
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModelId, angles);

	//再生するアニメーションの設定
	mAnimWalk = MV1AttachAnim(mModelId, 1);

	//アニメーションの総再生時間の取得
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModelId, mAnimWalk);
	mStepAnim = 0.0f;

	MV1SetAttachAnimTime(mModelId, mAnimWalk, mStepAnim);
}

void Unit::UpDate(void)
{
	//経過時間を取得
	float deltaTime = mSceneManager->GetDeltaTime();

	float movePow = 5.0f;
	float moveHPow = movePow / 2.0f;

	//新しいアニメーション再生時間をセット
	mStepAnim += (deltaTime * SPEED_ANIM);
	if (mStepAnim > 41.0f)
	{
		mStepAnim = 0.0f;
	}
	MV1SetAttachAnimTime(mModelId, mAnimWalk, mStepAnim);

	bool isHitMove = false;
	float rotRad = 0.0f;
	Camera* camera = mSceneManager->GetCamera();
	VECTOR cameraAngles = camera->GetAnglePos();

	//前後移動
	if (CheckHitKey(KEY_INPUT_W))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(0.0f);
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(180.0f);
	}

	//横移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(-90.0f);
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(90.0f);
	}

	//押している間だけ移動する
	if (isHitMove)
	{
		//キャラクターが向いている方向に移動する
		/*mPos.x += sinf(mAngles.y + rotRad) * moveHPow;
		mPos.z += cosf(mAngles.y + rotRad) * moveHPow;*/

		//カメラが向いている方向に移動する
		mPos.x += sinf(rotRad + cameraAngles.y) * moveHPow;
		mPos.z += cosf(rotRad + cameraAngles.y) * moveHPow;

		//移動方向にキャラクターの角度を即座に変える
		//mAngles.y = rotRad + cameraAngles.y;

		//移動方向にキャラクターの角度を徐々に変える
		float radUnitAnglesY = mAngles.y;
		float radMoveAnglesY = cameraAngles.y + rotRad;
		radMoveAnglesY = AsoUtility::RadIn2PI(radMoveAnglesY);

		//回転量が少ない方の回転方向を取得する(時計回り：1、反時計回り：-1)
		float aroundDir = AsoUtility::DirNearAroundRad(radUnitAnglesY, radMoveAnglesY);

		//クルクル問題
		//→DirNearAroundRad 関数の要件を満たしていない
		
		//ブルブル問題
		//→ゲーム制御においてよくある問題。しきい値、みなし値を設ける。

		float diff = radMoveAnglesY - radUnitAnglesY;
		float absDiff = abs(diff);
		if (absDiff <= SPEED_ROT_RAT)
		{
			mAngles.y += absDiff * aroundDir;
		}
		else
		{
			mAngles.y += (SPEED_ROT_RAT * aroundDir);
		}
		mAngles.y = AsoUtility::RadIn2PI(mAngles.y);
	}

	//モデルの角度を設定
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModelId, angles);

	//モデルの座標を設定
	MV1SetPosition(mModelId, mPos);
}

void Unit::Draw(void)
{
	DrawSphere3D(mPos, 5.0f, 10, 0x8800ff, 0x000000, true);
	//モデルの描画
	MV1DrawModel(mModelId);
}

void Unit::Release(void)
{
	MV1DeleteModel(mModelId);
}

VECTOR Unit::GetPos(void)
{
	return mPos;
}

VECTOR Unit::GetAnglePos(void)
{
	return mAngles;
}
