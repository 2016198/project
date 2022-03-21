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
	//�J�����̍��W�̏�����
	mPos = { 0.0f, 300.0f, -500.0f };

	//�J�����̊p�x
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
	//�L�[�{�[�h����ŃJ�����ʒu���ړ����܂��B

	float rad = 0.0f;

	////�O��ړ�
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	//���[���h���W�̑O��(Z+)
	//	//Z�̐�����
	//	//mPos.z += movePow;

	//	//�J�����̑O���m�Fs
	//	rad = AsoUtility::Deg2RadD(0.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	//���[���h���W�̑O��(Z-)
	//	//Z�̕�����
	//	//mPos.z -= movePow;

	//	//�J�����̌���m�F
	//	rad = AsoUtility::Deg2RadD(180.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	////���ړ�
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	//X�̐�����
	//	//mPos.x += movePow;

	//	//�J�����̍��ړ�
	//	rad = AsoUtility::Deg2RadD(-90.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	//Y�̕�����
	//	//mPos.x -= movePow;

	//	//�J�����̉E�ړ�
	//	rad = AsoUtility::Deg2RadD(90.0f);
	//	mPos.x += sinf(mAngle.y + rad) * moveHPow;
	//	mPos.z += cosf(mAngle.y + rad) * moveHPow;
	//}

	//�����ړ�
	//if (CheckHitKey(KEY_INPUT_X))
	//{
	//	//X�̐�����
	//	mPos.y += movePow;
	//}

	//if (CheckHitKey(KEY_INPUT_Z))
	//{
	//	//Y�̕�����
	//	mPos.y -= movePow;
	//}

	//�L�[�{�[�h����ŃJ�����p�x��ύX
	//����]
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//�E��]
		mAngles.y += AsoUtility::Deg2RadD(1.0f);
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//����]
		mAngles.y -= AsoUtility::Deg2RadD(1.0f);
	}

	//���グ��A�����낷�J�����̉�]
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	//���グ��
	//	mAngles.x += AsoUtility::Deg2RadD(1.0f);
	//}

	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	//�����낷
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

		//���ӓ_
		float dirX;
		float dirZ;
		VECTOR dir;
		VECTOR movePow;
		
		//�����_�̈ړ�
		//----------------------------------------
		//�J�����̌����Ă������
		dirX = sinf(mAngles.y);
		dirZ = cosf(mAngles.y);

		//���K��
		dir = VNorm({ dirX, 0.0f, dirZ });

		//��������ړ��ʂ��Z�o
		movePow = VScale(dir, DIS_TARGET_TO_UNIT);

		VECTOR uPos = mUnit->GetPos();
		mTargetPos = VAdd(uPos, movePow);
		//mTargetPos.y = 0.0f;
		//----------------------------------------------

		//�J�����ʒu�̈ړ�
		// -----------------------------------------------
		//�J�����̌����Ă�������̔��Ε���
		float revRad = AsoUtility::Deg2RadF(180.0f);
		dirX = sinf(mAngles.y + revRad);
		dirZ = cosf(mAngles.y + revRad);

		//���K��
		dir = VNorm({ dirX, 0.0f, dirZ });

		//��������ړ��ʂ��Z�o
		movePow = VScale(dir, DIS_TARGET_TO_CAMERA);
		//����
		movePow.y = HEGHT;
		//�����_����J�����̈ړ��ʂ𑫂��΂���
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
