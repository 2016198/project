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

	// �J�����̏����ݒ�
	mPos = DEFAULT_CAMERA_POS;
	mTargetPos = VAdd(mPos, RELATIVE_TARGET_POS);
	mCameraUp = { 0.0f, 1.0f, 0.0f };

	// �J������X���ɌX���Ă��邪�A���̌X������Ԃ��X�������Ƃ���
	// mQuaRot�͉�]�v�Z�p�ŁA
	// �����܂Ŏ��ƂȂ�̂́A�J�������W�ƒ����_�Ƃ���
	mQuaRot = Quaternion();

}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
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

	// �J�����̐ݒ�
	SetCameraPositionAndTargetAndUpVec(
		mPos,
		mTargetPos,
		mCameraUp
	);

}

void Camera::SetBeforeDrawFree(void)
{
	//�J�����̕����ړ��Ɖ�](��]�ړ�)

	//�ړ�
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_W)) moveDir = AsoUtility::DIR_F;
	if (CheckHitKey(KEY_INPUT_S)) moveDir = AsoUtility::DIR_B;
	if (CheckHitKey(KEY_INPUT_A)) moveDir = AsoUtility::DIR_L;
	if (CheckHitKey(KEY_INPUT_D)) moveDir = AsoUtility::DIR_R;

	//��]
	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_UP))	   axisDeg.x += -1.0f; 
	if (CheckHitKey(KEY_INPUT_DOWN))   axisDeg.x +=  1.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))   axisDeg.y += -1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT))  axisDeg.y +=  1.0f;

	//��]
	if (!AsoUtility::EqualsVZero(axisDeg))
	{
		VECTOR axisRad;
		axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
		axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
		axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

		//�N�H�^�j�I��((��])�̍X�V
		Quaternion axis = Quaternion::Euler(axisRad);
		mQuaRot = mQuaRot.Mult(axis);

		//�����_�X�V
		VECTOR localPos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
		mTargetPos = VAdd(mPos, localPos);

		//�J�����̏����
		mCameraUp = mQuaRot.GetUp();

	}

	//�ړ�
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		float speed = 30.0f;

		MATRIX mat = mQuaRot.ToMatrix();

		//�ړ�������������(�x�N�g��)�����߂���
		VECTOR dir = VNorm(VTransform(moveDir, mat));

		//�ړ��ʂ����o
		VECTOR movePow = VScale(dir, speed);

		//�J�����̈ʒu
		mPos = VAdd(mPos, movePow);
		mTargetPos = VAdd(mTargetPos, movePow);
	}
}

void Camera::SetBeforeDrawFixedPoint(void)
{

}

void Camera::SetBeforeDrawFollow(void)
{
	//�v���C���[���W
	VECTOR shipPos = mShipTransform->pos;

	//�v���C���[�̌���(��])
	Quaternion shipRot = mShipTransform->quaRot;
	MATRIX shipMat = mShipTransform->matRot;

	//�ݒ肵�Ȃ��Ⴂ���Ȃ��l(�J�����ʒu�A�����_�A�J�����̏����)
	//mPos = VAdd();
	//mTargetPos = VSub();
	//mCameraUp = VAdd

	//�J�����ʒu
	mPos = VAdd(shipPos, RELATIVE_CAMERA_FOLLOW);
	// �� �v���C���[�����ʂ������Ă���Ƃ��ɂ����Ή��ł��Ă��Ȃ�
	//		���΍��W�Ƀv���C���[�̊J�X��������K�v������

	//�J�����ʒu
	//---------------------------------------------------------------
	VECTOR relativeCameraPos;
	//�s��v�Z
	relativeCameraPos = VTransform(RELATIVE_CAMERA_FOLLOW, shipMat);

	//�N�H�[�^�j�I��
	relativeCameraPos = shipRot.PosAxis(RELATIVE_CAMERA_FOLLOW);

	mPos = VAdd(shipPos, relativeCameraPos);
	//---------------------------------------------------------------

	//�����_
	//---------------------------------------------------------------
	VECTOR relativeTargetPos;
	//�s��v�Z
	relativeTargetPos = VTransform(RELATIVE_TARGET_POS, shipMat);

	//�N�H�[�^�j�I��
	relativeTargetPos = shipRot.PosAxis(RELATIVE_TARGET_POS);

	mTargetPos = VAdd(mPos, relativeTargetPos);
	//---------------------------------------------------------------

	//�J�����̏����
	mCameraUp = VTransform(AsoUtility::DIR_U, shipMat);
	mCameraUp = shipRot.GetUp();
	mCameraUp = shipRot.PosAxis(AsoUtility::DIR_U);
}

void Camera::SetBeforeDrawFollowSpring(void)
{
	//�v���C���[���W
	VECTOR shipPos = mShipTransform->pos;

	//�v���C���[�̌���(��])
	Quaternion shipRot = mShipTransform->quaRot;
	MATRIX shipMat = mShipTransform->matRot;

	//�J�����̑��΍��W
	VECTOR relativeCameraPos = shipRot.PosAxis(RELATIVE_CAMERA_SPRING);

	//�o�l�萔
	float dampening = 2.0 * sqrtf(POW_SPRING);

	float delta = mSceneManager->GetDeltaTime();

	//���z�ʒu
	VECTOR idealPos = VAdd(shipPos, relativeCameraPos);

	//���݈ʒu�Ɨ��z�ʒu�̍���
	VECTOR diff = VSub(mPos, idealPos);

	//�o�l�̗� = (-�o�l�̋��� �~ �o�l�̐L��) - (��R �~ �J�����̑��x)
	VECTOR force;
	force = VScale(diff, -POW_SPRING);
	force = VSub(force, VScale(mVelocity, dampening));

	//�J�������x���X�V
	mVelocity = VAdd(mVelocity, VScale(force, delta));

	//�J�����ʒu�̍X�V
	mPos = VAdd(mPos, VScale(mVelocity, delta));

	//�����_
	//---------------------------------------------------------------
	VECTOR relativeTargetPos;
	//�s��v�Z
	relativeTargetPos = VTransform(RELATIVE_TARGET_POS, shipMat);

	//�N�H�[�^�j�I��
	relativeTargetPos = shipRot.PosAxis(RELATIVE_TARGET_POS);

	mTargetPos = VAdd(mPos, relativeTargetPos);
	//---------------------------------------------------------------

	//�J�����̏����
	mCameraUp = VTransform(AsoUtility::DIR_U, shipMat);
	mCameraUp = shipRot.GetUp();
	mCameraUp = shipRot.PosAxis(AsoUtility::DIR_U);
}

void Camera::SetBeforeShake(void)
{
	mStepShake -= mSceneManager->GetDeltaTime();
	if (mStepShake < 0.0f)
	{
		//�����ʒu�ɖ߂�
		mPos = mDefaultPos;
		ChangeMode(MODE::FIXED_POINT);
		return;
	}

	//�������^��
	//�������镝 �~ sinf(time �~ �U�����鑬��)
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

	// �������
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�y����z", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�@�@�@����F��������", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�@�@�@�����F�a", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�@�@�@���e�F�m", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�V�[���J�ځF�r��������", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@1500m�ȏ㗣����", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�Q�[���I�[�o�[", 0xffffff);

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

void Camera::ChangeMode(MODE mode)//���[�h�؂�ւ̎��ɏ��������鏈��
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
		//�U���������
		mShakeDir = VNorm({ 1.0f, 1.0f, 0.0f });
		mDefaultPos = mPos;
		break;
	}
}

void Camera::SetShip(Transform* shipTransform)
{
	mShipTransform = shipTransform;
}
