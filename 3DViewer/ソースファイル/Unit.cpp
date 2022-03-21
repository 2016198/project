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

	//���f���̍��W��ݒ�
	MV1SetPosition(mModelId, mPos);

	//���f���̊p�x��ݒ�
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModelId, angles);

	//�Đ�����A�j���[�V�����̐ݒ�
	mAnimWalk = MV1AttachAnim(mModelId, 1);

	//�A�j���[�V�����̑��Đ����Ԃ̎擾
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModelId, mAnimWalk);
	mStepAnim = 0.0f;

	MV1SetAttachAnimTime(mModelId, mAnimWalk, mStepAnim);
}

void Unit::UpDate(void)
{
	//�o�ߎ��Ԃ��擾
	float deltaTime = mSceneManager->GetDeltaTime();

	float movePow = 5.0f;
	float moveHPow = movePow / 2.0f;

	//�V�����A�j���[�V�����Đ����Ԃ��Z�b�g
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

	//�O��ړ�
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

	//���ړ�
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

	//�����Ă���Ԃ����ړ�����
	if (isHitMove)
	{
		//�L�����N�^�[�������Ă�������Ɉړ�����
		/*mPos.x += sinf(mAngles.y + rotRad) * moveHPow;
		mPos.z += cosf(mAngles.y + rotRad) * moveHPow;*/

		//�J�����������Ă�������Ɉړ�����
		mPos.x += sinf(rotRad + cameraAngles.y) * moveHPow;
		mPos.z += cosf(rotRad + cameraAngles.y) * moveHPow;

		//�ړ������ɃL�����N�^�[�̊p�x�𑦍��ɕς���
		//mAngles.y = rotRad + cameraAngles.y;

		//�ړ������ɃL�����N�^�[�̊p�x�����X�ɕς���
		float radUnitAnglesY = mAngles.y;
		float radMoveAnglesY = cameraAngles.y + rotRad;
		radMoveAnglesY = AsoUtility::RadIn2PI(radMoveAnglesY);

		//��]�ʂ����Ȃ����̉�]�������擾����(���v���F1�A�����v���F-1)
		float aroundDir = AsoUtility::DirNearAroundRad(radUnitAnglesY, radMoveAnglesY);

		//�N���N�����
		//��DirNearAroundRad �֐��̗v���𖞂����Ă��Ȃ�
		
		//�u���u�����
		//���Q�[������ɂ����Ă悭������B�������l�A�݂Ȃ��l��݂���B

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

	//���f���̊p�x��ݒ�
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModelId, angles);

	//���f���̍��W��ݒ�
	MV1SetPosition(mModelId, mPos);
}

void Unit::Draw(void)
{
	DrawSphere3D(mPos, 5.0f, 10, 0x8800ff, 0x000000, true);
	//���f���̕`��
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
