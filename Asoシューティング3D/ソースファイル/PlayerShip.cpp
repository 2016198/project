#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "ParticleGenerator.h"
#include "ResourceManager.h"
#include "SpriteAnimator.h"
#include "SpeechBalloon.h"
#include "PlayerShot.h"
#include "PlayerShip.h"

PlayerShip::PlayerShip(SceneManager* manager)
{
	mSceneManager = manager;
}

void PlayerShip::Init(void)
{
	//モデル制御の基本情報を初期化
	mAddMove = 0.0f;
	mTransform.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));
	float scale = 10.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = AsoUtility::VECTOR_ZERO;
	mPow = 0.0f;

	mTransform.Update();

	//エフェクト
	mParticleGenerator = new ParticleGenerator(
		mSceneManager, mTransform.pos, 15.0f);
	mParticleGenerator->Init();

	//自機の爆発エフェクト
	mExplosion = new SpriteAnimator(
		mSceneManager,
		ResourceManager::SRC::SHIP_EXPLOSION,
		20,
		8.0f);

	//吹き出し
	mSpeechBalloon = new SpeechBalloon(
		mSceneManager, SpeechBalloon::TYPE::SPEECH,
		&mTransform);
	mSpeechBalloon->SetText("追って！");
	mSpeechBalloon->SetTime(9.0f);
	mSpeechBalloon->SetRelativePos({ 15.0f, 25.0f, 0.0f });

	//初期処理
	ChangeState(STATE::RUN);

}

void PlayerShip::Update(void)
{
	switch (mState)
	{
	case PlayerShip::STATE::RUN:
		UpdateRun();
		break;
	case PlayerShip::STATE::DESTROY:
		UpdateDestroy();
		break;
	}

	//モデル制御の更新処理
	mTransform.Update();
}

void PlayerShip::UpdateRun(void)
{
	//回転操作
	ProcessTurn();

	//弾
	ProcessShot();

	//プレイヤーの前方方向
	VECTOR forward = mTransform.GetForward();

	//加速
	if (CheckHitKey(KEY_INPUT_B) && mAddMove == 0.0f)
	{
		mAddMove = 10.0f;
		mPow = 150.0f;
	}
	else
	{
		mAddMove -= mSceneManager->GetDeltaTime() * 3.0f;
		if (mPow < 0.0f)
		{
			mPow = 0.0f;
		}
		else
		{
			mPow -= mSceneManager->GetDeltaTime() * 45.0f;
		}

		if (mAddMove < 0.0f)
		{
			mAddMove = 0.0f;
		}
	}

	//減速
	if (CheckHitKey(KEY_INPUT_G))
	{
		mAddMove = -9.0f;
	}

	//移動
	mTransform.pos = VAdd(mTransform.pos, VScale(forward, SPEED_MOVE + mAddMove));

	//エフェクト制御(位置)
	mParticleGenerator->SetPos(
		VAdd(mTransform.pos, VScale(mTransform.GetForward(),
			30.0f)));

	//エフェクト制御(回転)
	Quaternion rot = mTransform.quaRot;
	Quaternion axis;
	axis = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::AXIS_Y);
	rot = rot.Mult(axis);
	axis = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(90.0f),
		AsoUtility::AXIS_X);
	rot = rot.Mult(axis);
	mParticleGenerator->SetRot(rot);

	mParticleGenerator->Update();
}

void PlayerShip::UpdateDestroy(void)
{
	VECTOR DrawPos = mExplosion->GetPos();
	DrawPos = VAdd(DrawPos, VScale(mTransform.GetForward(), 1.0f));
	mExplosion->SetPos(DrawPos);
	mExplosion->Update();
}

void PlayerShip::Draw(void)
{
	switch (mState)
	{
	case PlayerShip::STATE::RUN:
		MV1DrawModel(mTransform.modelId);
		//パーティクルの描画
		mParticleGenerator->Draw();
		break;
	case PlayerShip::STATE::DESTROY:
		mExplosion->Draw();
		break;
	}

	//デバッグ
	DrawSphere3D(mTransform.pos, COLLISION_RADIUS, 10, 0xffffff, 0xffffff, false);

	//スピード
	DrawBox(10, 10, 40, 160, 0xffffff, true);
	DrawBox(10, 10 + (int)mPow, 40, 160, 0x990099, true);
	DrawBox(9, 9, 41, 161, GetColor(255,125,0), false);
	DrawBox(10, 10, 40, 160, GetColor(255,125,0), false);
	DrawString(0, 170, "ブースト", 0xffffff, true);
}

void PlayerShip::Release(void)
{
	mParticleGenerator->Release();
	delete mParticleGenerator;
	mParticleGenerator = nullptr;

	mExplosion->Release();
	delete mExplosion;
	mExplosion = nullptr;

	mSpeechBalloon->Release();
	delete mSpeechBalloon;
	mSpeechBalloon = nullptr;

	MV1DeleteModel(mTransform.modelId);

	//弾の開放
	for (auto& shot : mShots)
	{
		shot->Release();
		delete shot;
		shot = nullptr;
	}
	mShots.clear();
}

void PlayerShip::ProcessTurn(void)
{
	//右旋回
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		Turn(1.0f, { 0.0f,1.0f,0.0f });
	}

	//左旋回
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		Turn(-1.0f, { 0.0f,1.0f,0.0f });
	}

	//上旋回
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		Turn(1.0f, { 1.0f,0.0f,0.0f });
	}

	//下旋回
	if (CheckHitKey(KEY_INPUT_UP))
	{
		Turn(-1.0f, { 1.0f,0.0f,0.0f });
	}
}

void PlayerShip::Turn(double deg, VECTOR axis)
{
	double rad = AsoUtility::Deg2RadD(deg);
	Quaternion tmpQ = Quaternion::AngleAxis(rad, axis);
	mTransform.quaRot = mTransform.quaRot.Mult(tmpQ);
}

void PlayerShip::ProcessShot(void)
{
	//弾の生成ディレイ
	mDelayShot -= mSceneManager->GetDeltaTime();
	if (mDelayShot <= 0.0f)
	{
		mDelayShot = 0.0f;
	}

	if (CheckHitKey(KEY_INPUT_N) && mDelayShot <= 0.0f)
	{
		mDelayShot = TIME_DELAY_SHOT;

		//自機の弾を生成
		CreateShot(1.0);
		CreateShot(-1.0);
		CreateShot(0.0);
	}
}

void PlayerShip::Destroy(void)
{
	ChangeState(STATE::DESTROY);
}

bool PlayerShip::IsDestroy(void)
{
	return mState == STATE::DESTROY;
}

Transform* PlayerShip::GetTranceform(void)
{
	return &mTransform;
}

SpeechBalloon* PlayerShip::GetSpeechBalloon(void)
{
	return mSpeechBalloon;
}

std::vector<PlayerShot*> PlayerShip::GetShots(void)
{
	return mShots;
}

void PlayerShip::ChangeState(STATE state)
{
	mState = state;
	switch (mState)
	{
	case PlayerShip::STATE::RUN:
		break;
	case PlayerShip::STATE::DESTROY:
		mExplosion->Create(mTransform.pos);
		break;
	}
}

void PlayerShip::CreateShot(double dir)
{
	bool isCreate = false;
	for (auto& shot : mShots)
	{
		if (!shot->IsAlive())
		{
			//インスタンスの使いまわし
			auto forward = mTransform.GetForward();
			if (dir != 0.0)
			{
				double rad = AsoUtility::Deg2RadD(dir * WAY_ANGLE);
				Quaternion qut = Quaternion::AngleAxis(rad, AsoUtility::AXIS_Y);
				mTransform.quaRot = mTransform.quaRot.Mult(qut);
				forward = mTransform.GetForward();
				rad = AsoUtility::Deg2RadD(-dir * WAY_ANGLE);
				qut = Quaternion::AngleAxis(rad, AsoUtility::AXIS_Y);
				mTransform.quaRot = mTransform.quaRot.Mult(qut);
			}

			shot->Create(mTransform.pos, forward);
			isCreate = true;
		}
	}

	if (!isCreate)
	{
		auto forward = mTransform.GetForward();
		if (dir != 0.0)
		{
			double rad = AsoUtility::Deg2RadD(dir * WAY_ANGLE);
			Quaternion qut = Quaternion::AngleAxis(rad, AsoUtility::AXIS_Y);
			mTransform.quaRot = mTransform.quaRot.Mult(qut);
			forward = mTransform.GetForward();
			rad = AsoUtility::Deg2RadD(-dir * WAY_ANGLE);
			qut = Quaternion::AngleAxis(rad, AsoUtility::AXIS_Y);
			mTransform.quaRot = mTransform.quaRot.Mult(qut);
		}
		//使いまわしできなかったら
		PlayerShot* newShot =
			new PlayerShot(mSceneManager, &mTransform);
		newShot->Create(mTransform.pos, forward);
		mShots.push_back(newShot);
	}
}
