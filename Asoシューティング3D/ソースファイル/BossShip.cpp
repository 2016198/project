#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "PlayerShip.h"
#include "EventShot.h"
#include "Turret.h"
#include "TurretShot.h"
#include "PlayerShip.h"
#include "Transform.h"
#include "BossShip.h"

BossShip::BossShip(SceneManager* manager, PlayerShip* playerShip)
{
	mSceneManager = manager;
	mPlayerShip = playerShip;
	mStepDestroy = TIME_DESTROY;
	mStepBlast = 0.1f;
}

void BossShip::Init(void)
{
	VECTOR pos = { 0.0f, 0.0f, 4000.0f };
	mTransform.SetModel(MV1LoadModel("Model/BossShip/BossShip.mv1"));
	mTransform.scl = { 2.0f, 2.0f, 2.0f };
	mTransform.pos = pos;
	mTransform.quaRot = Quaternion::Euler(
		AsoUtility::Deg2RadF(20.0f),
		AsoUtility::Deg2RadF(210.0f),
		AsoUtility::Deg2RadF(20.0f));
	mTransform.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f));

	mTransform.Update();

	//タレットの作成
	//前方
	MakeTurret(
		{ 4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(-18.0f) });
	MakeTurret(
		{ -4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(18.0f) });

	//横
	MakeTurret(
		{ 4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(90.0f), 0.0f });
	MakeTurret(
		{ -4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(-90.0f), 0.0f });

	//後方
	MakeTurret(
		{ 3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(18.0f) });
	MakeTurret(
		{ -3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(-18.0f) });

	SceneManager::SCENE_ID id = mSceneManager->GetmSceneID();

	switch (id)
	{
	case SceneManager::SCENE_ID::EVENT:
		ChangeState(STATE::EVENT);
		break;
	case SceneManager::SCENE_ID::BATTLE:
		int ret = MV1SetupCollInfo(mTransform.modelId, -1, 1, 1, 1);
		ChangeState(STATE::BATTLE);
		break;
	}
}

void BossShip::Update(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
		//ボスの前方方向に移動する
		mTransform.pos = VAdd(
			mTransform.pos,
			VScale(mTransform.GetForward(), SPEED_MOVE));

		//弾の更新処理
		mEventShot->Update();
		if (!mEventShot->IsAlive())
		{
			mStepEvent -= mSceneManager->GetDeltaTime();
			if (mStepEvent < 0.0f)
			{
				mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
				return;
			}
		}

		//タレットの更新
		UpdateTurret();

		break;
	case BossShip::STATE::BATTLE:
	{
		//ボスの前方方向に移動する
		mTransform.pos = VAdd(mTransform.pos,
			VScale(mTransform.GetForward(), SPEED_MOVE));

		//★旋回移動。旋回し続けるとぐるぐる円周を回る移動になる(方向回転)
		double speed = 0.05 * mSceneManager->GetDeltaTime();
		Quaternion axis = Quaternion::AngleAxis(speed, AsoUtility::AXIS_Y);
		mTransform.quaRot = mTransform.quaRot.Mult(axis);

		//タレットの更新
		UpdateTurret();

		//当たり判定(コライダ)の更新
		MV1RefreshCollInfo(mTransform.modelId);

		//タレットの生存判定
		int alived = 0;
		for (auto turret : mTurrets)
		{
			if (turret->IsAlive())
			{
				alived++;
			}
		}

		if (alived == 0)
		{
			Destroy();
		}
	}
		break;
	case BossShip::STATE::DESTROY:
		mStepDestroy -= mSceneManager->GetDeltaTime();
		for (const auto& blast : mExplosion)
		{
			blast->Update();
		}
		mStepBlast -= mSceneManager->GetDeltaTime();
		if (mStepBlast <= 0.0f)
		{
			mStepBlast = 0.0f;
		}
		if (mStepBlast <= 0.0f)
		{
			VECTOR Bpos = mTransform.pos;
			VECTOR pos;
			pos.y = 200.0f;
			int rad = rand() % 360;
			pos.x = cosf(AsoUtility::Deg2RadF(static_cast<float>(rad))) * 550.0f;
			pos.z = sinf(AsoUtility::Deg2RadF(static_cast<float>(rad))) * 1600.0f;

			VECTOR axisDeg = { 0.0f, 60.0f, static_cast<float>(rand() % 360) };

			//回転

			VECTOR axisRad;
			axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
			axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
			axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

			//クォタニオン((回転)の更新
			Quaternion qut;
			
			Quaternion axis = Quaternion::Euler(axisRad);
			qut = qut.Mult(axis);

			pos = Quaternion::PosAxis(qut, pos);
			pos = VAdd(pos,Bpos);
			bool IsCreate = false;
			for (auto& blast : mExplosion)
			{
				if (blast->IsEnd())
				{
					IsCreate = true;
					blast->Create(pos);
					break;
				}
			}
			if (IsCreate == false)
			{
				SpriteAnimator* newBlast = new SpriteAnimator(
					mSceneManager, ResourceManager::SRC::SHIP_EXPLOSION, 120, 8.0f);
				newBlast->Create(pos);
				mTransform.pos;
				mExplosion.push_back(newBlast);
			}
		}
		break;
	case BossShip::STATE::END:
		// シーン遷移
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::TITLE, true);
		break;
	}

	mTransform.Update();
}

void BossShip::UpdateTurret(void)
{
	for (const auto turret : mTurrets)
	{
		turret->Update();
		//砲台の弾を更新
		auto shots = turret->GetShots();
		for (const auto shot : shots)
		{
			shot->Update();
		}
	}
}

void BossShip::Draw(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
		MV1DrawModel(mTransform.modelId);
		mEventShot->Draw();
		DrawTurret();
		break;
	case BossShip::STATE::BATTLE:
		MV1DrawModel(mTransform.modelId);
		DrawTurret();
		break;
	case BossShip::STATE::DESTROY:
	{
		COLOR_F C_FROM = { 1.0f, 1.0f, 1.0f, 1.0f };
		COLOR_F C_TO = { 1.0f, 0.0f, 0.0f, 0.0f };

		COLOR_F colorF;

		float delta = (TIME_DESTROY - mStepDestroy) / TIME_DESTROY;
		colorF = AsoUtility::Lerp(C_FROM, C_TO, delta);

		//colorF.a = α値

		//モデルで使用されているマテリアルの数を取得
		int num = MV1GetMaterialNum(mTransform.modelId);
		for (int i = 0; i < num; i++)
		{
			//マテリアルのディフーズカラーを変更
			MV1SetMaterialDifColor(mTransform.modelId, i, colorF);
		}
		MV1DrawModel(mTransform.modelId);
		if (colorF.a <= 0.0f)
		{
			ChangeState(STATE::END);
		}
		for (const auto& blast : mExplosion)
		{
			blast->Draw();
		}
	}
		break;
	case BossShip::STATE::END:
		break;
	}

}

void BossShip::DrawTurret(void)
{
	for (const auto turret : mTurrets)
	{
		turret->Draw();
		//砲台の弾を描画
		auto shots = turret->GetShots();
		for (const auto shot : shots)
		{
			shot->Draw();
		}
	}
}

void BossShip::Release(void)
{
	MV1DeleteModel(mTransform.modelId);

	if (mEventShot != nullptr)
	{
		mEventShot->Release();
		delete mEventShot;
		mEventShot = nullptr;
	}

	for (auto& tur : mTurrets)
	{
		tur->Release();
		delete tur;
		tur = nullptr;
	}
	mTurrets.clear();

	for (auto& blast : mExplosion)
	{
		blast->Release();
		delete blast;
		blast = nullptr;
	}
	
}

Transform* BossShip::GetTranceform(void)
{
	return &mTransform;
}

std::vector<Turret*> BossShip::GetTurrets(void)
{
	return mTurrets;
}

void BossShip::Destroy(void)
{
	ChangeState(STATE::DESTROY);
}

bool BossShip::IsAlive(void)
{
	return mState == STATE::BATTLE;
}

void BossShip::ChangeState(STATE state)
{
	mState = state;
	switch (mState)
	{
	case BossShip::STATE::EVENT:
	{
		mStepEvent = TIME_EVENT;
		mEventShot = new EventShot(mSceneManager, &mTransform);

		//ボスからカメラ位置への方向
		VECTOR dir = VNorm(VSub(mSceneManager->GetCamera()->GetPos(), mTransform.pos));
		mEventShot->Create(mTransform.pos, dir);
	}
		break;
	case BossShip::STATE::BATTLE:
		break;
	case BossShip::STATE::DESTROY:
		break;
	case BossShip::STATE::END:
		break;
	}
}

void BossShip::MakeTurret(VECTOR localPos, VECTOR localAddAxis)
{
	Turret* turret = new Turret(
		mSceneManager,
		mPlayerShip->GetTranceform(),
		&mTransform,
		localPos, localAddAxis);

	turret->Init();

	mTurrets.push_back(turret);
}
