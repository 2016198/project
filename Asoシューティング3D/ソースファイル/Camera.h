#pragma once
#include <vector>
#include <DxLib.h>
#include "Transform.h"
#include "Quaternion.h"

class SceneManager;

class Camera
{

public:

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };

	//���@�ƃJ�����ʒu�Ƃ̑��΍��W(���S�Ǐ])
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0f,25.0f,-80.0f };

	//���@�ƃJ�����ʒu�Ƃ̑��΍��W(�o�l�t��)
	static constexpr VECTOR RELATIVE_CAMERA_SPRING = { 0.0f,50.0f,-40.0f };

	//�J�����ʒu�ƒ����_�Ƃ̑��΍��W
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f,-100.0f,500.0f };

	//�΂˂̋���
	static constexpr float POW_SPRING = 240.0f;

	//�V�F�C�N�F����
	static constexpr float TIME_SHKAE = 2.0f;

	//�V�F�C�N�F��
	static constexpr float WIDTH_SHKAE = 3.0f;

	//�V�F�C�N�F�X�s�[�h
	static constexpr float SPEED_SHKAE = 30.0f;

	//�J�����̏���
	enum class MODE
	{
		NOME,			//�Ȃ�
		FREE,			//���R���[�h
		FIXED_POINT,	//��_���[�h
		FOLLOW,			//�Ǐ]���[�h
		FOLLOW_SPRING,	//�o�l�t���Ǐ]���[�h
		SHAKE			//�J�����V�F�C�N
	};
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFollow(void);
	void SetBeforeDrawFollowSpring(void);
	void SetBeforeShake(void);

	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

	//�J�������[�h�̕ύX
	void ChangeMode(MODE mode);

	//���@�̐ݒ�
	void SetShip(Transform* shipTransform);

private:

	SceneManager* mSceneManager;
	Transform* mShipTransform;

	//�J�������[�h
	MODE mMode;

	// �J�����̈ʒu
	VECTOR mPos;

	// �J�����p�x
	Quaternion mQuaRot;

	// �����_
	VECTOR mTargetPos;

	// �J�����̏����
	VECTOR mCameraUp;

	//���x
	VECTOR mVelocity;

	//�V�F�C�N�p
	float mStepShake;
	VECTOR mDefaultPos;
	VECTOR mShakeDir;

};

