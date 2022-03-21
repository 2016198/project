#include "AsoUtility.h"
#include "Transform.h"
#include "SpaceDome.h"

SpaceDome::SpaceDome(SceneManager* manager,Transform* shipTransform)
{
	mSceneManager = manager;
	mShipTransform = shipTransform;
}

void SpaceDome::Init(void)
{
	//モデル制御の基本情報を初期化
	mTransform.SetModel(MV1LoadModel("Model/SkyDome/SkyDome.mv1"));
	float scale = 1.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = AsoUtility::VECTOR_ZERO;

	mTransform.Update();

	//Zバッファの書き込み無効
	//MV1SetWriteZBuffer(mTransform.modelId, false);
	MV1SetUseZBuffer(mTransform.modelId, false);

	if (mShipTransform == nullptr)
	{
		ChangeState(STATE::NONE);
	}
	else
	{
		ChangeState(STATE::FOLLOW);
	}
}

void SpaceDome::Update(void)
{
	switch (mState)
	{
	case SpaceDome::STATE::STAY:
		break;
	case SpaceDome::STATE::FOLLOW:
		//自機の位置を同期をとる
		mTransform.pos = mShipTransform->pos;
		break;
	}

	if(mShipTransform == nullptr)
	{ 
		mTransform.pos = AsoUtility::VECTOR_ZERO;
	}
	else
	{
		//時機の位置を同期をとる
		mTransform.pos = mShipTransform->pos;
		//モデル制御の更新処理
		mTransform.Update();
	}
}

void SpaceDome::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void SpaceDome::Release(void)
{
	MV1DeleteModel(mTransform.modelId);
}

void SpaceDome::ChangeState(STATE state)
{
	mState = state;
	switch (mState)
	{
	case SpaceDome::STATE::STAY:
		mTransform.pos = AsoUtility::VECTOR_ZERO;
		break;
	case SpaceDome::STATE::FOLLOW:
		mTransform.pos = mShipTransform->pos;
		break;
	default:
		break;
	}
}
