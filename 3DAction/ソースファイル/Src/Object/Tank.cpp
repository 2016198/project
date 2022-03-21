#include <string>
#include <EffekseerForDXLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "Common/Collider.h"
#include "Common/SpeechBalloon.h"
#include "Planet.h"
#include "Wheel.h"
#include "BarrelAndBody.h"
#include "Tank.h"

Tank::Tank(SceneManager* manager)
{
	mSceneManager = manager;
	mResourceManager = manager->GetResourceManager();
	mGravityManager = manager->GetGravityManager();
}

void Tank::Init(void)
{

	// ���f���̊�{�ݒ�
	mTransform.SetModel(-1);

	mTransform.pos = { 0.0f, 30.0f, 0.0f };
	mTransform.scl = { 0.5f, 0.5f, 0.5f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = Quaternion();
	mTransform.Update();

	//�^�C���̍쐬

	//��
	MakeWhlle(
		{ -30.5f, 25.5f, 0.0f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f },
		true
	);
	//�E
	MakeWhlle(
		{ 30.5f, 25.5f, 0.0f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f },
		false
	);

	//��ƖC��
	MakeBarrelAndBody(
		{ 0.0f, 50.0f, 0.0f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f }
	);

}

void Tank::Update(void)
{
	//�X�V����
	mTransform.Update();

	//�^�C���̍X�V
	UpdateWhlle();

	//��ƖC��̍X�V
	UpdateBarrelAndBody();
	
	UpdatePlay();
}

void Tank::UpdatePlay(void)
{
	//�ړ�����(mMovePow����鏈��)
	ProcessMove();

	//�d�͂ɂ��ړ��ʌv�Z
	CalcGravityPow();

	//�Փ˔���
	Collision();
}

void Tank::Draw(void)
{

	//�^�C���̕`��
	DrawWhlle();

	//��ƖC��̕`��
	DrawBarrelAndBody();

	// �f�o�b�O�p�`��
	DrawDebug();

}

void Tank::DrawDebug(void)
{
	unsigned int white = 0xffffff;
	unsigned int black = 0x000000;
	unsigned int red = 0xff0000;
	unsigned int green = 0x00ff00;
	unsigned int blue = 0x0000ff;
	unsigned int yellow = 0xffff00;
 	unsigned int purpl = 0x800080;

	VECTOR vector;

	// �L������{���
	//-------------------------------------------------------
	// �L�������W
	vector = mTransform.pos;
	DrawFormatString(20, 60, black, "�^���N���W �F (%0.2f, %0.2f, %0.2f)",
		vector.x, vector.y, vector.z
	);

	//-------------------------------------------------------

	//�Փ˔���p�̐�

	//DrawLine3D(mGravHitDown, mGravHitUp, 0);

}

void Tank::AddCollider(Collider* collider)
{
	mColliders.push_back(collider);
}

void Tank::ClearCollider(void)
{
	mColliders.clear();
}

void Tank::Release(void)
{
	mTransform.Release();
	for (const auto& wheel : mWheels)
	{
		wheel->Release();
	}
	mBarrelAndBody->Release();
}

void Tank::ProcessMove(void)
{
	//�ړ��ʂ��[��
	mMovePow = AsoUtility::VECTOR_ZERO;

	//�ړ�����
	VECTOR dir, dirL, dirR;
	dir = dirL = dirR = AsoUtility::VECTOR_ZERO;

	Quaternion axisY;

	if (CheckHitKey(KEY_INPUT_W))
	{
		dir = mTransform.GetForward();
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		dir = mTransform.GetBack();
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		axisY = Quaternion::AngleAxis(AsoUtility::Deg2RadD(-ROT_DEG),
			AsoUtility::AXIS_Y);
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		axisY = Quaternion::AngleAxis(AsoUtility::Deg2RadD(ROT_DEG),
			AsoUtility::AXIS_Y);
	}

	mTransform.quaRot = Quaternion::Mult(axisY, mTransform.quaRot);


	if (!AsoUtility::EqualsVZero(dir))
	{
		//�ړ�
		mSpeed = SPEED_MOVE;

		//�ړ������E�ړ���
		mMovePow = VScale(dir, mSpeed);
	}

}

void Tank::CalcGravityPow(void)
{
	//�d�͕���
	VECTOR dirGravity = mGravityManager->GetDirGravity();

	//�d�͂̋���
	float gravityPow = mGravityManager->GetPower();

	//�d��
	VECTOR gravity = VScale(dirGravity, gravityPow);
	mGravityPow = VAdd(mGravityPow, gravity);

	float dot = VDot(dirGravity, mGravityPow);
	if (dot >= 0.0f)
	{
		//������
		mGravityPow = gravity;
	}
}

Transform* Tank::GetTransform(void)
{
	return &mTransform;
}

void Tank::Collision(void)
{
	//���ݍ��W���N�_�Ɉړ�����W�����߂�
	mMovedPos = VAdd(mTransform.pos, mMovePow);

	//�Փ�(�d��)
	CollisionGravity();

	//�ړ�
	mTransform.pos = mMovedPos;

}

void Tank::CollisionGravity(void)
{
	//�W�����v�p���[���ړ����W�ɉ��Z
	mMovedPos = VAdd(mMovedPos, mGravityPow);

	//�d��
	float checkPow = 10.0f;
	VECTOR dirUpGravity = mGravityManager->GetDirUpGravity();
	VECTOR dirGravity = mGravityManager->GetDirGravity();
	float gravityPow = mGravityManager->GetPower();

	mGravHitUp = VAdd(mMovedPos, VScale(dirUpGravity, gravityPow));
	mGravHitUp = VAdd(mGravHitUp, VScale(dirUpGravity, checkPow * 2.0f));
	mGravHitDown = VAdd(mMovedPos, VScale(dirGravity, checkPow));

	for (auto c : mColliders)
	{
		//�n�ʂƂ̏Փ�
		auto hit = MV1CollCheck_Line(c->mModelId, -1, mGravHitUp, mGravHitDown);
		if (hit.HitFlag > 0)
		{

			//�Փ˒n�_����A������Ɉړ�
			mMovedPos = VAdd(hit.HitPosition, VScale(dirUpGravity, 2.0f));

		}
	}
}

void Tank::MakeWhlle(VECTOR localPos, VECTOR localAddAxis, bool isLeft)
{
	Wheel* wheel = new Wheel(
		mSceneManager,
		&mTransform,
		localPos, localAddAxis,
		isLeft);

	wheel->Init();

	mWheels.push_back(wheel);
}

void Tank::UpdateWhlle(void)
{
	for (const auto& whlle : mWheels)
	{
		whlle->Update();
	}
}

void Tank::DrawWhlle(void)
{
	for (const auto& whlle : mWheels)
	{
		whlle->Draw();
	}
}

void Tank::MakeBarrelAndBody(VECTOR localPos, VECTOR localAddAxis)
{
	mBarrelAndBody = new BarrelAndBody(
		mSceneManager,
		&mTransform,
		localPos, localAddAxis);

	mBarrelAndBody->Init();
}

void Tank::UpdateBarrelAndBody(void)
{
	mBarrelAndBody->Update();
}

void Tank::DrawBarrelAndBody(void)
{
	mBarrelAndBody->Draw();
}

